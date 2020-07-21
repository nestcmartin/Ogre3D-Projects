#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <list>
#include "SDL.h"

class InputListener;
union InputEvent;

class InputManager
{
private:
	static std::list<InputListener*> inputListeners;

public:
	static void Init();
	static void AddInputListener(InputListener* lis);
	static void RemoveInputListener(InputListener* lis);
	static void ProcessInputEvent(const SDL_Event& event);
	static InputEvent ConvertImputEvent(const SDL_Event& in);
	static void Release();
};

#endif // !__INPUT_MANAGER_H__