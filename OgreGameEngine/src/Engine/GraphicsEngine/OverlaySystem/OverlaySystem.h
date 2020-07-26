#ifndef __OVERLAY_MANAGER_H__
#define __OVERLAY_MANAGER_H__

#include "OgreOverlaySystem.h"

class OverlaySystem
{
private:
	static Ogre::OverlaySystem* overlaySystem;

public:
	static void Init();
	static void Release();

	static Ogre::OverlaySystem* getOverlaySystem() { return overlaySystem; }
};

#endif // !__OVERLAY_MANAGER_H__
