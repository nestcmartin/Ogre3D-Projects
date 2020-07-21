#include "SDL_syswm.h"
#include "SDLInputMapper.h"
#include "OgreApplicationContextSDL.h"


OgreApplicationContextSDL::OgreApplicationContextSDL(const Ogre::String& appName) :
    OgreApplicationContext(appName)
{
}

void OgreApplicationContextSDL::addInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.insert(std::make_pair(SDL_GetWindowID(win), lis));
}

void OgreApplicationContextSDL::removeInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.erase(std::make_pair(SDL_GetWindowID(win), lis));
}

Window OgreApplicationContextSDL::createWindow(const Ogre::String& name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams)
{
    Window window = { NULL, NULL };

    if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

    Ogre::RenderWindowDescription d = root_->getRenderSystem()->getRenderWindowDescription();
    miscParams.insert(d.miscParams.begin(), d.miscParams.end());
    d.miscParams = miscParams;
    if (w > 0) d.width = w;
    if (h > 0) d.height = h;
    d.name = name;

    int flags = d.useFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    window.native = SDL_CreateWindow(d.name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, d.width, d.height, flags);

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window.native, &wmInfo);
    d.miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

    if (!windows_.empty()) d.miscParams["currentGLContext"] = "true";    

    window.render = root_->createRenderWindow(d);
    windows_.push_back(window);

    return window;
}

void OgreApplicationContextSDL::setWindowGrab(SDL_Window* win, bool _grab)
{
    SDL_bool grab = SDL_bool(_grab);
    SDL_SetWindowGrab(win, grab);
    SDL_ShowCursor(!grab);
}

void OgreApplicationContextSDL::shutdown()
{
    OgreApplicationContext::shutdown();
    if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void OgreApplicationContextSDL::pollEvents()
{
    if (windows_.empty()) return;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            root_->queueEndRendering();
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event != SDL_WINDOWEVENT_RESIZED) continue;
            for (auto it = windows_.begin(); it != windows_.end(); ++it)
            {
                if (event.window.windowID != SDL_GetWindowID(it->native)) continue;

                Ogre::RenderWindow* win = it->render;
                win->windowMovedOrResized();
                windowResized(win);
            }
            break;

        default:
            _fireInputEvent(convert(event), event.window.windowID);
            break;
        }
    }
}

void OgreApplicationContextSDL::_destroyWindow(const Window& win)
{
    OgreApplicationContext::_destroyWindow(win);
    if (win.native) SDL_DestroyWindow(win.native);
}