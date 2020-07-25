#ifndef __INPUT_EVENT_H__
#define __INPUT_EVENT_H__

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

union InputEvent
{
	int type;
	KeyboardEvent key;
	MouseButtonEvent button;
	MouseWheelEvent wheel;
	MouseMotionEvent motion;
	TouchFingerEvent tfinger;
	TextInputEvent text;
};


#endif // !__INPUT_EVENT_H__