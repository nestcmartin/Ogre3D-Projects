#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "OgreFileSystemLayer.h"

class ResourcesManager
{
private:
	static Ogre::FileSystemLayer* FSLayer;

public:
	static void Init();
	static void Release();

	static Ogre::FileSystemLayer* FileSystemLayer() { return FSLayer; }

private:
	static void Locate();
	static void Load();
};

#endif // !__RESOURCES_H__