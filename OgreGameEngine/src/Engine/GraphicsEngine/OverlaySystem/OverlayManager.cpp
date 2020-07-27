#include "Overlay.h"
#include "OverlayManager.h"
#include "OgreImGuiOverlay.h"
#include "OgreOverlayManager.h"
#include "GraphicsEngine/Graphics.h"

OverlayManager::OverlayManager()
{
	overlays_ = std::unordered_map<const char*, Overlay*>();
	overlays_.clear();
}

OverlayManager::~OverlayManager()
{
	overlays_.clear();
}

void OverlayManager::addOverlay(const char* name, int zorder)
{
	Overlay* overlay = new Overlay(name, zorder);
	Ogre::ImGuiOverlay* imguiOverlay = overlay->createImGuiOverlay();
	Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);
	Graphics::GetWindow()->getRenderWindow()->addListener(overlay);
	overlays_[name] = overlay;
}
