#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "SDL.h"
#include "Ogre.h"

class Window
{
private:
	static const uint32_t WINDOW_WIDTH = 1280;
	static const uint32_t WINDOW_HEIGHT = 720;

	Ogre::RenderWindow* render_;
	SDL_Window* native_;

public:
	Window(Ogre::RenderWindow* render = nullptr, SDL_Window* native = nullptr);

	Ogre::RenderWindow* getRenderWindow() { return render_; }
	SDL_Window* getNativeWindow() { return native_; }

	void initWindow(const Ogre::String& name = "Ogre3D", uint32_t w = WINDOW_WIDTH, uint32_t h = WINDOW_HEIGHT);
	void setWindowName(const Ogre::String& name);
	void setWindowGrab(bool grab);
	void destroyWindow();

	void windowMoved(Ogre::RenderWindow* rw) {}
	void windowResized(Ogre::RenderWindow* rw) {}
	bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	void windowClosed(Ogre::RenderWindow* rw) {}
	void windowFocusChange(Ogre::RenderWindow* rw) {}
};

#endif // !__WINDOW_H__
