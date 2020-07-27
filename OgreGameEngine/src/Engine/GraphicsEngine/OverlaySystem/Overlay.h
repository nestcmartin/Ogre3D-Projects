#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include "OgreRenderTargetListener.h"
#include "OverlayInputListener.h"
#include "Core/InputSystem/InputListenerChain.h"

namespace Ogre { class ImGuiOverlay; }

class Overlay : public Ogre::RenderTargetListener
{
private:
	int zorder_;
	Ogre::String name_;

	InputListenerChain listenerChain_;
	std::unique_ptr<OverlayInputListener> inputListenerUI_;

public:
	Overlay(const char* name, int zorder = 300);
	~Overlay();

	Ogre::ImGuiOverlay* createImGuiOverlay();

	void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);

	bool keyPressed(const KeyboardEvent& evt) { return listenerChain_.keyPressed(evt); }
	bool keyReleased(const KeyboardEvent& evt) { return listenerChain_.keyReleased(evt); }
	bool mouseMoved(const MouseMotionEvent& evt) { return listenerChain_.mouseMoved(evt); }
	bool mouseWheelRolled(const MouseWheelEvent& evt) { return listenerChain_.mouseWheelRolled(evt); }
	bool mousePressed(const MouseButtonEvent& evt) { return listenerChain_.mousePressed(evt); }
	bool mouseReleased(const MouseButtonEvent& evt) { return listenerChain_.mouseReleased(evt); }
	bool textInput(const TextInputEvent& evt) { return listenerChain_.textInput(evt); }
};

#endif // !__OVERLAY_H__
