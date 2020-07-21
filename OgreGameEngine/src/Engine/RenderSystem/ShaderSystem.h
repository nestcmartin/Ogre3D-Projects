#ifndef __SHADER_SYSTEM_H__
#define __SHADER_SYSTEM_H__

#include "OgreShaderGenerator.h"
#include "TechniqueResolverListener.h";

class ShaderSystem
{
private:
	static Ogre::RTShader::ShaderGenerator* shaderGenerator;
	static TechniqueResolverListener* materialManagerListener;

public:
	static void Init();
	static void Release();
};

#endif // !__SHADER_SYSTEM_H__
