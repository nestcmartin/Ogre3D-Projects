#ifndef __OVERLAY_MANAGER_H__
#define __OVERLAY_MANAGER_H__

#include "Core/LowLevel/Singleton.h"
#include "OgreRenderTargetListener.h"

#include "Widget.h"
#include "OverlayInputListener.h"
#include "Core/InputSystem/InputListenerChain.h"

enum WidgetType { DEFAULT, FPS_COUNTER };

class OverlayManager : public Singleton<OverlayManager>, public Ogre::RenderTargetListener
{
	friend Singleton<OverlayManager>;

private:
	std::unordered_map<const char*, Widget*> widgets_;

	InputListenerChain listenerChain_;
	std::unique_ptr<OverlayInputListener> inputListenerUI_;

public:
	virtual ~OverlayManager();

	void addWidget(WidgetType type, const char* name, bool opened = true, float x = 0, float y = 0, float w = 500, float h = 300,
		bool title = false, bool scroll = false, bool menu = false, bool move = false, bool resize = false,
		bool collapse = false, bool nav = false, bool background = false, bool front = false);

	void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);

	bool keyPressed(const KeyboardEvent& evt) { return listenerChain_.keyPressed(evt); }
	bool keyReleased(const KeyboardEvent& evt) { return listenerChain_.keyReleased(evt); }
	bool mouseMoved(const MouseMotionEvent& evt) { return listenerChain_.mouseMoved(evt); }
	bool mouseWheelRolled(const MouseWheelEvent& evt) { return listenerChain_.mouseWheelRolled(evt); }
	bool mousePressed(const MouseButtonEvent& evt) { return listenerChain_.mousePressed(evt); }
	bool mouseReleased(const MouseButtonEvent& evt) { return listenerChain_.mouseReleased(evt); }
	bool textInput(const TextInputEvent& evt) { return listenerChain_.textInput(evt); }

private:
	OverlayManager();
};

#endif // !__OVERLAY_MANAGER_H__