#ifndef __INPUT_LISTENER_CHAIN_H__
#define __INPUT_LISTENER_CHAIN_H__

#include <vector>

#include "InputListener.h"

enum
{
	OIS_DELETE = int('\177'),
	OIS_RETURN = int('\r'),
	OIS_ESCAPE = int('\033'),
	OIS_SPACE = int(' '),
	OIS_F1 = (1 << 30) | 0x3A,
	OIS_F2,
	OIS_F3,
	OIS_F4,
	OIS_F5,
	OIS_F6,
	OIS_F7,
	OIS_F8,
	OIS_F9,
	OIS_F10,
	OIS_F11,
	OIS_F12,
	OIS_PRINTSCREEN,
	OIS_SCROLLLOCK,
	OIS_PAUSE,
	OIS_INSERT,
	OIS_HOME,
	OIS_PAGEUP,
	OIS_END = (1 << 30) | 0x4D,
	OIS_PAGEDOWN,
	OIS_RIGHT,
	OIS_LEFT,
	OIS_DOWN,
	OIS_UP,
	OIS_NUMLOCKCLEAR,
	OIS_KP_DIVIDE,
	OIS_KP_MULTIPLY,
	OIS_KP_MINUS,
	OIS_KP_PLUS,
	OIS_KP_ENTER,
	OIS_KP_1,
	OIS_KP_2,
	OIS_KP_3,
	OIS_KP_4,
	OIS_KP_5,
	OIS_KP_6,
	OIS_KP_7,
	OIS_KP_8,
	OIS_KP_9,
	OIS_KP_0,
	OIS_KP_PERIOD,
	OIS_LSHIFT = (1 << 30) | 0xE1,
	OIS_ALT = 0x0100 | 0x0200,
	OIS_CTRL = 0x0040 | 0x0080,
	OIS_GUI = 0x0400 | 0x0800,
	OIS_SHIFT = 0x0001 | 0x0002,
	OIS_NUM = 0x1000,
};

class InputListenerChain : public InputListener
{
protected:
	std::vector<InputListener*> listenerChain_;

public:
	InputListenerChain() {}
	InputListenerChain(std::vector<InputListener*> chain) : listenerChain_(chain) {}

	InputListenerChain& operator=(InputListenerChain o);

	bool keyPressed(const KeyboardEvent& evt) override;
	bool keyReleased(const KeyboardEvent& evt) override;
	bool touchMoved(const TouchFingerEvent& evt) override;
	bool touchPressed(const TouchFingerEvent& evt) override;
	bool touchReleased(const TouchFingerEvent& evt) override;
	bool mouseMoved(const MouseMotionEvent& evt) override;
	bool mouseWheelRolled(const MouseWheelEvent& evt) override;
	bool mousePressed(const MouseButtonEvent& evt) override;
	bool mouseReleased(const MouseButtonEvent& evt) override;
	bool textInput(const TextInputEvent& evt) override;
};


#endif // !__INPUT_LISTENER_CHAIN_H__