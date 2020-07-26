#ifndef __INPUT_LISTENER_UI_H__
#define __INPUT_LISTENER_UI_H__

#include "InputListener.h"

class InputListenerUI : public InputListener
{
public:
	InputListenerUI();

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

#endif // !__INPUT_LISTENER_UI_H__

