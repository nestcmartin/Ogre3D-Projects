#ifndef __SDL_INPUT_MAPPER_H__
#define __SDL_INPUT_MAPPER_H__

#include "SDL.h"
#include "OgreInput.h"

Event convert(const SDL_Event& in)
{
	Event out;
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


#endif // !__SDL_INPUT_MAPPER_H__
