#include "OverlayManager.h"
#include "OgreImGuiOverlay.h"
#include "OgreOverlayManager.h"

#include "GraphicsEngine/Graphics.h"
#include "Core/InputSystem/InputManager.h"

OverlayManager::OverlayManager()
{
	Ogre::ImGuiOverlay* imguiOverlay = new Ogre::ImGuiOverlay();
	imguiOverlay->setZOrder(300);
	imguiOverlay->show();

	Ogre::OverlayManager::getSingleton().addOverlay(imguiOverlay);
	Graphics::GetWindow()->getRenderWindow()->addListener(this);

	inputListenerUI_.reset(new OverlayInputListener());
	listenerChain_ = InputListenerChain({ inputListenerUI_.get() });
	InputManager::Instance()->addInputListener(&listenerChain_);
}

OverlayManager::~OverlayManager()
{
}

void OverlayManager::addWidget(WidgetType type, const char* name, bool opened,
	float x, float y, float w, float h,
	bool title, bool scroll, bool menu,
	bool move, bool resize, bool collapse,
	bool nav, bool background, bool front)
{
	switch (type)
	{
	case DEFAULT:
	{
		Widget* widget = new Widget(name, true, x, y, w, h,
			title, scroll, menu, move, resize, collapse, nav, background, front);
		widgets_[name] = widget;
	}
		break;
	
	case FPS_COUNTER:
	{
		FPSCounterWidget* widget = new FPSCounterWidget(name, opened);
		widgets_[name] = widget;
	}
		break;

	default:
		break;
	}
}

void OverlayManager::preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt)
{
	if (!evt.source->getOverlaysEnabled()) return;
	Ogre::ImGuiOverlay::NewFrame();
	
    for (auto& widget : widgets_)
	{
		widget.second->show();
	}
}