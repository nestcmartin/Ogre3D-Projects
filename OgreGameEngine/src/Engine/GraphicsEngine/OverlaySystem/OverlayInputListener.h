#ifndef __OVERLAY_INPUT_LISTENER_H__
#define __OVERLAY_INPUT_LISTENER_H__

#include "Core/InputSystem/InputListener.h"

class OverlayInputListener : public InputListener
{
public:
	OverlayInputListener();

	bool keyPressed(const KeyboardEvent& evt);
	bool keyReleased(const KeyboardEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	bool mouseWheelRolled(const MouseWheelEvent& evt);
	bool mousePressed(const MouseButtonEvent& evt);
	bool mouseReleased(const MouseButtonEvent& evt);
	bool textInput(const TextInputEvent& evt);

private:
	bool keyEvent(const KeyboardEvent& arg);
};

#endif // !__OVERLAY_INPUT_LISTENER_H__

