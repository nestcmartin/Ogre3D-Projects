#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Window.h"
#include "OgreOverlaySystem.h"

class Renderer
{
private:
	static Window* window;
	static Ogre::Root* root;
	static Ogre::OverlaySystem* overlaySystem;

public:
	static void Init();
	static void Release();
	
	static void Start();
	static void Stop();

	static void ProcessWindowEvent(const SDL_Event& event);
	static void AddFrameListener(Ogre::FrameListener* lis);

	static Window* GetWindow() { return window; }
	static Ogre::Root* GetRoot() { return root; }
};

#endif // !__RENDERER_H__
