#include "OgreTechnique.h"
#include "OgreRTShaderSystem.h"
#include "OgreSGTechniqueResolverListener.h"

OgreSGTechniqueResolverListener::OgreSGTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* shaderGenerator) :
	shaderGenerator_(shaderGenerator)
{
}

Ogre::Technique* OgreSGTechniqueResolverListener::handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend)
{
    if (!shaderGenerator_->hasRenderState(schemeName)) return nullptr;

    // Create shader generated technique for this material.
    bool techniqueCreated = shaderGenerator_->createShaderBasedTechnique(*originalMaterial, Ogre::MaterialManager::DEFAULT_SCHEME_NAME, schemeName);
    if (!techniqueCreated) return nullptr;

    // Force creating the shaders for the generated technique.
    shaderGenerator_->validateMaterial(schemeName, originalMaterial->getName(), originalMaterial->getGroup());

    // Grab the generated technique.
    Ogre::Material::Techniques::const_iterator it;
    for (it = originalMaterial->getTechniques().begin(); it != originalMaterial->getTechniques().end(); ++it)
    {
        Ogre::Technique* curTech = *it;
        if (curTech->getSchemeName() == schemeName) return curTech;
    }

    return nullptr;
}

bool OgreSGTechniqueResolverListener::afterIlluminationPassesCreated(Ogre::Technique* tech)
{
    if (shaderGenerator_->hasRenderState(tech->getSchemeName()))
    {
        Ogre::Material* mat = tech->getParent();
        shaderGenerator_->validateMaterialIlluminationPasses(tech->getSchemeName(), mat->getName(), mat->getGroup());
        return true;
    }
    return false;
}

bool OgreSGTechniqueResolverListener::beforeIlluminationPassesCleared(Ogre::Technique* tech)
{
    if (shaderGenerator_->hasRenderState(tech->getSchemeName()))
    {
        Ogre::Material* mat = tech->getParent();
        shaderGenerator_->invalidateMaterialIlluminationPasses(tech->getSchemeName(), mat->getName(), mat->getGroup());
        return true;
    }
    return false;
}
