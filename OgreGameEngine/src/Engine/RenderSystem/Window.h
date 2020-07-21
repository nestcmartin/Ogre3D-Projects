#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "SDL.h"
#include "Ogre.h"

class Window
{
private:
	Ogre::RenderWindow* render_;
	SDL_Window* native_;

public:
	Window(Ogre::RenderWindow* render = nullptr, SDL_Window* native = nullptr);

	Ogre::RenderWindow* getRenderWindow() { return render_; }
	SDL_Window* getNativeWindow() { return native_; }

	void initWindow(const Ogre::String& name, uint32_t w, uint32_t h);
	void setWindowGrab(bool grab);
	void destroyWindow();

	void windowMoved(Ogre::RenderWindow* rw) {}
	void windowResized(Ogre::RenderWindow* rw) {}
	bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	void windowClosed(Ogre::RenderWindow* rw) {}
	void windowFocusChange(Ogre::RenderWindow* rw) {}
};

#endif // !__WINDOW_H__
