#include "OverlaySystem.h"
#include "OgreOverlayManager.h"

#include "OgreSceneManager.h"
#include "GraphicsEngine/Scene/SceneManager.h"

Ogre::OverlaySystem* OverlaySystem::overlaySystem = nullptr;

void OverlaySystem::Init()
{
	overlaySystem = OGRE_NEW Ogre::OverlaySystem();
	SceneManager::Instance()->getSceneManager()->addRenderQueueListener(overlaySystem);
}

void OverlaySystem::Release()
{
	if (overlaySystem)
	{
		OGRE_DELETE overlaySystem;
		overlaySystem = nullptr;
	}
}