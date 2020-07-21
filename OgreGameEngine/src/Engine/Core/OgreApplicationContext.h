#ifndef __OGRE_APPLICATION_CONTEXT_H__
#define __OGRE_APPLICATION_CONTEXT_H__

// Includes -------------------------------------------------------------------
#include <vector>

#include "Ogre.h"
//-----------------------------------------------------------------------------


// Forward Declarations -------------------------------------------------------
extern "C" struct SDL_Window;

namespace Ogre {
    class FileSystemLayer;
    class OverlaySystem;

    namespace RTShader {
        class ShaderGenerator;
    }
}

class OgreSGTechniqueResolverListener;
class InputListener;
union Event;
//-----------------------------------------------------------------------------


// Structs --------------------------------------------------------------------
struct Window
{
    Ogre::RenderWindow* render;
    SDL_Window* native;
};
//-----------------------------------------------------------------------------


class OgreApplicationContext : public Ogre::FrameListener
{
public:
	explicit OgreApplicationContext(const Ogre::String& appName = "Ogre3D App");
	virtual ~OgreApplicationContext();

	Ogre::Root* getRoot() const { return root_; }
    Ogre::FileSystemLayer& getFileSystemLayer() { return *fileSystemLayer_; }
    Ogre::OverlaySystem* getOverlaySystem() const { return overlaySystem_; }
	Ogre::RenderWindow* getRenderWindow() const { return windows_.empty() ? nullptr : windows_[0].render; }

	void initApp();
	void closeApp();

    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
    virtual void windowMoved(Ogre::RenderWindow* rw) {}
    virtual void windowResized(Ogre::RenderWindow* rw) {}
    virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
    virtual void windowClosed(Ogre::RenderWindow* rw) {}
    virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

    virtual void addInputListener(SDL_Window* win, InputListener* lis);
    void addInputListener(InputListener* lis);
    virtual void removeInputListener(SDL_Window* win, InputListener* lis);
    void removeInputListener(InputListener* lis);
    virtual void setWindowGrab(SDL_Window* win, bool grab = true) {}
    void setWindowGrab(bool grab = true);
    void _fireInputEvent(const Event& event, uint32_t windowID) const;

    virtual void createRoot();
    virtual bool oneTimeConfig();
    virtual void setup();
    virtual void shutdown();

    virtual Window createWindow(const Ogre::String& name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams);
    void destroyWindow(const Ogre::String& name);
    virtual void locateResources();
    virtual void loadResources();

    bool initialiseRTShaderSystem();
    void destroyRTShaderSystem();

    virtual void pollEvents();

protected:
    virtual void _destroyWindow(const Window& win);

    bool firstRun_;
    Ogre::Root* root_;
    Ogre::String appName_;
    Ogre::FileSystemLayer* fileSystemLayer_;
    Ogre::OverlaySystem* overlaySystem_;
    Ogre::RTShader::ShaderGenerator* shaderGenerator_;
    OgreSGTechniqueResolverListener* materialManagerListener_;

    std::vector<Window> windows_;
    std::set<std::pair<uint32_t, InputListener*>> inputListeners_;
};

#endif // !__OGRE_APPLICATION_CONTEXT_H__
