#include <SDL.h>

#include "InputEvent.h"
#include "InputListener.h"
#include "InputManager.h"

InputManager::~InputManager()
{
	inputListeners_.clear();
}

void InputManager::addInputListener(InputListener* lis)
{
	inputListeners_.push_back(lis);
}

void InputManager::removeInputListener(InputListener* lis)
{
	inputListeners_.remove(lis);
}

void InputManager::processInputEvent(const SDL_Event& event)
{
	InputEvent evt = convertImputEvent(event);

	for (auto it = inputListeners_.begin(); it != inputListeners_.end(); ++it)
	{
		InputListener* l = (*it);
		switch (evt.type)
		{
		case KEYDOWN:
			l->keyPressed(evt.key);
			break;
		case KEYUP:
			l->keyReleased(evt.key);
			break;
		case MOUSEBUTTONDOWN:
			l->mousePressed(evt.button);
			break;
		case MOUSEBUTTONUP:
			l->mouseReleased(evt.button);
			break;
		case MOUSEWHEEL:
			l->mouseWheelRolled(evt.wheel);
			break;
		case MOUSEMOTION:
			l->mouseMoved(evt.motion);
			break;
		case FINGERDOWN:
			l->touchMoved(evt.tfinger);
			l->touchPressed(evt.tfinger);
			break;
		case FINGERUP:
			l->touchReleased(evt.tfinger);
			break;
		case FINGERMOTION:
			l->touchMoved(evt.tfinger);
			break;
		case TEXTINPUT:
			l->textInput(evt.text);
			break;
		}
	}
}

InputEvent InputManager::convertImputEvent(const SDL_Event& in)
{
	InputEvent out;
	out.type = 0;

	switch (in.type)
	{
	case SDL_KEYDOWN:
		out.type = KEYDOWN;
	case SDL_KEYUP:
		if (!out.type)
			out.type = KEYUP;
		out.key.repeat = in.key.repeat;
		out.key.keysym.sym = in.key.keysym.sym;
		out.key.keysym.mod = in.key.keysym.mod;
		break;
	case SDL_MOUSEBUTTONUP:
		out.type = MOUSEBUTTONUP;
	case SDL_MOUSEBUTTONDOWN:
		if (!out.type)
			out.type = MOUSEBUTTONDOWN;
		out.button.x = in.button.x;
		out.button.y = in.button.y;
		out.button.button = in.button.button;
		out.button.clicks = in.button.clicks;
		break;
	case SDL_MOUSEWHEEL:
		out.type = MOUSEWHEEL;
		out.wheel.y = in.wheel.y;
		break;
	case SDL_MOUSEMOTION:
		out.type = MOUSEMOTION;
		out.motion.x = in.motion.x;
		out.motion.y = in.motion.y;
		out.motion.xrel = in.motion.xrel;
		out.motion.yrel = in.motion.yrel;
		out.motion.windowID = in.motion.windowID;
		break;
	case SDL_FINGERDOWN:
		out.type = FINGERDOWN;
	case SDL_FINGERUP:
		if (!out.type)
			out.type = FINGERUP;
	case SDL_FINGERMOTION:
		if (!out.type)
			out.type = FINGERMOTION;
		out.tfinger.x = in.tfinger.x;
		out.tfinger.y = in.tfinger.y;
		out.tfinger.dx = in.tfinger.dx;
		out.tfinger.dy = in.tfinger.dy;
		out.tfinger.fingerId = in.tfinger.fingerId;
		break;
	case SDL_TEXTINPUT:
		out.type = TEXTINPUT;
		out.text.chars = in.text.text;
		break;
	}

	return out;
}

InputManager::InputManager()
{
	inputListeners_ = std::list<InputListener*>();
	inputListeners_.clear();
}
