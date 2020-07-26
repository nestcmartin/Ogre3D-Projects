#ifndef __UI_LISTENER_H__
#define __UI_LISTENER_H__

#include "Core/InputSystem/InputListener.h"

class UIListener : public InputListener
{
public:
	UIListener();

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

#endif // !__UI_LISTENER_H__

