#include "ShaderSystem.h"

Ogre::RTShader::ShaderGenerator* ShaderSystem::shaderGenerator = nullptr;
TechniqueResolverListener* ShaderSystem::materialManagerListener = nullptr;

void ShaderSystem::Init()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		if (!materialManagerListener)
		{
			materialManagerListener = new TechniqueResolverListener(shaderGenerator);
		}
	}
}

void ShaderSystem::Release()
{
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (materialManagerListener)
	{
		Ogre::MaterialManager::getSingleton().removeListener(materialManagerListener);
		delete materialManagerListener;
		materialManagerListener = nullptr;
	}

	// Destroy RTShader system.
	if (shaderGenerator)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		shaderGenerator = nullptr;
	}
}
