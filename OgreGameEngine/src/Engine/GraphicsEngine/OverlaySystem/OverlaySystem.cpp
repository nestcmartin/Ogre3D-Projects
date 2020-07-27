#include "OverlaySystem.h"
#include "OgreOverlayManager.h"

#include "GraphicsEngine/Graphics.h"

Ogre::OverlaySystem* OverlaySystem::overlaySystem = nullptr;

void OverlaySystem::Init()
{
	overlaySystem = OGRE_NEW Ogre::OverlaySystem();
}

void OverlaySystem::Release()
{
	if (overlaySystem)
	{
		OGRE_DELETE overlaySystem;
		overlaySystem = nullptr;
	}
}