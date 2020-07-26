#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "Core/Singleton.h"

union SDL_Event;
union InputEvent;
class InputListener;

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;

protected:
	std::list<InputListener*> inputListeners_;

public:
	virtual ~InputManager();

	virtual void addInputListener(InputListener* lis);
	virtual void removeInputListener(InputListener* lis);

	void processInputEvent(const SDL_Event& event);

protected:
	InputEvent convertImputEvent(const SDL_Event& in);

private:
	InputManager();
};

enum InputKey
{
	DELETE = int('\177'),
	RETURN = int('\r'),
	ESCAPE = int('\033'),
	SPACE = int(' '),
	F1 = (1 << 30) | 0x3A,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	PRINTSCREEN,
	SCROLLLOCK,
	PAUSE,
	INSERT,
	HOME,
	PAGEUP,
	END = (1 << 30) | 0x4D,
	PAGEDOWN,
	RIGHT,
	LEFT,
	DOWN,
	UP,
	NUMLOCKCLEAR,
	KP_DIVIDE,
	KP_MULTIPLY,
	KP_MINUS,
	KP_PLUS,
	KP_ENTER,
	KP_1,
	KP_2,
	KP_3,
	KP_4,
	KP_5,
	KP_6,
	KP_7,
	KP_8,
	KP_9,
	KP_0,
	KP_PERIOD,
	LSHIFT = (1 << 30) | 0xE1,
	ALT = 0x0100 | 0x0200,
	CTRL = 0x0040 | 0x0080,
	GUI = 0x0400 | 0x0800,
	SHIFT = 0x0001 | 0x0002,
	NUM = 0x1000,
};

#endif // !__INPUT_MANAGER_H__