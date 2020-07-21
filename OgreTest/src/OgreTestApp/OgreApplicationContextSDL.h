#ifndef __OGRE_APPLICATION_CONTEXT_SDL_H__
#define __OGRE_APPLICATION_CONTEXT_SDL_H__

#include "OgreApplicationContext.h"

class OgreApplicationContextSDL : public OgreApplicationContext
{
public:
    explicit OgreApplicationContextSDL(const Ogre::String& appName = "Ogre3D App SDL");

    virtual Window createWindow(const Ogre::String& name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams);
    void setWindowGrab(SDL_Window* win, bool _grab);
    
    void addInputListener(SDL_Window* win, InputListener* lis);
    void removeInputListener(SDL_Window* win, InputListener* lis);

    void shutdown();
    void pollEvents();

    using OgreApplicationContext::setWindowGrab;
    using OgreApplicationContext::addInputListener;
    using OgreApplicationContext::removeInputListener;

protected:
    void _destroyWindow(const Window& win);
};

#endif // !__OGRE_APPLICATION_CONTEXT_SDL_H__