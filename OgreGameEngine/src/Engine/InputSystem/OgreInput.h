#ifndef __OGRE_INPUT_H__
#define __OGRE_INPUT_H__

#include <vector>

namespace Ogre {
	struct FrameEvent;
}

enum ButtonType
{
	BUTTON_LEFT = 1,
	BUTTON_MIDDLE,
	BUTTON_RIGHT,
};

enum EventType
{
	KEYDOWN = 1, KEYUP,
	MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSEWHEEL, MOUSEMOTION,
	FINGERDOWN, FINGERUP, FINGERMOTION,
	TEXTINPUT,
};

typedef int Keycode;

struct Keysym
{
	Keycode sym;
	unsigned short mod;
};

struct KeyboardEvent
{
	int type;
	Keysym keysym;
	unsigned char repeat;
};

struct MouseMotionEvent
{
	int type;
	int x, y;
	int xrel, yrel;
	int windowID;
};

struct MouseButtonEvent
{
	int type;
	int x, y;
	unsigned char button;
	unsigned char clicks;
};

struct MouseWheelEvent
{
	int type;
	int y;
};

struct TouchFingerEvent
{
	int type;
	int fingerId;
	float x, y;
	float dx, dy;
};

struct TextInputEvent
{
	int type;
	const char* chars;
};

union Event
{
	int type;
	KeyboardEvent key;
	MouseButtonEvent button;
	MouseWheelEvent wheel;
	MouseMotionEvent motion;
	TouchFingerEvent tfinger;
	TextInputEvent text;
};

// SDL
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

/**
* the return values of the callbacks are ignored by ApplicationContext
* however they can be used to control event propagation in a hierarchy.
* The convention is to return true if the event was handled and false if it should be further propagated.
*/
struct InputListener 
{
	virtual ~InputListener() {}
	virtual void frameRendered(const Ogre::FrameEvent& evt) { }
	virtual bool keyPressed(const KeyboardEvent& evt) { return false; }
	virtual bool keyReleased(const KeyboardEvent& evt) { return false; }
	virtual bool touchMoved(const TouchFingerEvent& evt) { return false; }
	virtual bool touchPressed(const TouchFingerEvent& evt) { return false; }
	virtual bool touchReleased(const TouchFingerEvent& evt) { return false; }
	virtual bool mouseMoved(const MouseMotionEvent& evt) { return false; }
	virtual bool mouseWheelRolled(const MouseWheelEvent& evt) { return false; }
	virtual bool mousePressed(const MouseButtonEvent& evt) { return false; }
	virtual bool mouseReleased(const MouseButtonEvent& evt) { return false; }
	virtual bool textInput(const TextInputEvent& evt) { return false; }
};

/**
 * Chain of multiple InputListeners that acts as a single InputListener
 * input events are propagated front to back until a listener returns true
 */
class InputListenerChain : public InputListener
{
protected:
	std::vector<InputListener*> listenerChain_;

public:
	InputListenerChain() {}
	InputListenerChain(std::vector<InputListener*> chain) : listenerChain_(chain) {}

	InputListenerChain& operator=(InputListenerChain o);

	bool keyPressed(const KeyboardEvent& evt);
	bool keyReleased(const KeyboardEvent& evt);
	bool touchMoved(const TouchFingerEvent& evt);
	bool touchPressed(const TouchFingerEvent& evt);
	bool touchReleased(const TouchFingerEvent& evt);
	bool mouseMoved(const MouseMotionEvent& evt);
	bool mouseWheelRolled(const MouseWheelEvent& evt);
	bool mousePressed(const MouseButtonEvent& evt);
	bool mouseReleased(const MouseButtonEvent& evt);
	bool textInput(const TextInputEvent& evt);
};

#endif // !__OGRE_INPUT_H__
