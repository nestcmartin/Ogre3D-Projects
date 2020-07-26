#include "OverlaySystem.h"
#include "OgreOverlayManager.h"
#include "GraphicsEngine/Graphics.h"

OverlaySystem::OverlaySystem() :
	overlaySystem(nullptr)
{
	overlaySystem = OGRE_NEW Ogre::OverlaySystem();
}

void OverlaySystem::Init()
{
	Ogre::ImGuiOverlay* imguiOverlay = OGRE_NEW Ogre::ImGuiOverlay();
	imguiOverlay->setZOrder(300);
	imguiOverlay->show();
	Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);
	
	inputListenerUI.reset(new InputListenerUI());
	listenerChain = InputListenerChain({ inputListenerUI.get() });
}

void OverlaySystem::Release()
{
	if (overlaySystem)
	{
		OGRE_DELETE overlaySystem;
		overlaySystem = nullptr;
	}
}

void OverlaySystem::preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt)
{
	if (!evt.source->getOverlaysEnabled()) return;

	Ogre::ImGuiOverlay::NewFrame();
	ImGui::ShowDemoWindow();
}
