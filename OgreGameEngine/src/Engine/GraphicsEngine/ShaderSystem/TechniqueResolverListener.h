#ifndef __TECHNIQUE_RESOLVER_LISTENER_H__
#define __TECHNIQUE_RESOLVER_LISTENER_H__

#include "OgreMaterialManager.h"

class TechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:
	explicit TechniqueResolverListener(Ogre::RTShader::ShaderGenerator* shaderGenerator);
    Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName,
        Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend);

    bool afterIlluminationPassesCreated(Ogre::Technique* tech);
    bool beforeIlluminationPassesCleared(Ogre::Technique* tech);

protected:
    Ogre::RTShader::ShaderGenerator* shaderGenerator_;
};

#endif // !__TECHNIQUE_RESOLVER_LISTENER_H__