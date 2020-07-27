#include "Overlay.h"
#include "OgreImGuiOverlay.h"
#include "Core/InputSystem/InputManager.h"

Overlay::Overlay(const char* name, int zorder) :
	name_(name),
	zorder_(zorder)
{
}

Overlay::~Overlay()
{
}

Ogre::ImGuiOverlay* Overlay::createImGuiOverlay()
{
	Ogre::ImGuiOverlay* imguiOverlay = new Ogre::ImGuiOverlay();
	imguiOverlay->setZOrder(zorder_);
	imguiOverlay->show();

	inputListenerUI_.reset(new OverlayInputListener());
	listenerChain_ = InputListenerChain({ inputListenerUI_.get() });
	InputManager::Instance()->addInputListener(&listenerChain_);

	return imguiOverlay;
}

void Overlay::preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt)
{
	if (!evt.source->getOverlaysEnabled()) return;
	Ogre::ImGuiOverlay::NewFrame();
	ImGui::ShowDemoWindow();
}