#ifndef __RESOURCES_H__
#define __RESOURCES_H__

namespace Ogre
{
	class FileSystemLayer;
	namespace RTShader
	{
		class ShaderGenerator;
	}
}

class OgreSGTechniqueResolverListener;

class Resources
{
private:
	static Ogre::FileSystemLayer* FSLayer;
	static Ogre::RTShader::ShaderGenerator* ShaderGenerator;
	static OgreSGTechniqueResolverListener* MaterialManagerListener;

public:
	static void Init(const Ogre::String& name);
	static void Locate();
	static void Load();
	static void InitShaderSystem();
	static void ReleaseShaderSystem();
	static void Release();

	static Ogre::FileSystemLayer* FileSystemLayer() { return FSLayer; }
};

#endif // !__RESOURCES_H__

