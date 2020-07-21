#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Window.h"

#include "OgreOverlaySystem.h"

class Renderer
{
private:
	static Window* window;
	static Ogre::Root* root;
	static bool isRendering;

	static Ogre::OverlaySystem* overlaySystem;

public:
	static void Init(const Ogre::String& name);
	static void Present();
	static void Release();
	
	static void Start();
	static void Stop();

	static void ProcessWindowEvent(const SDL_Event& event);

	static Window* GetWindow() { return window; }
	static Ogre::Root* GetRoot() { return root; }
	static bool IsRendering() { return isRendering; }
};

#endif // !__RENDERER_H__
