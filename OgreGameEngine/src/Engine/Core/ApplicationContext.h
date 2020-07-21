#ifndef __APPLICATION_CONTEXT_H__
#define __APPLICATION_CONTEXT_H__

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
union InputEvent;
//-----------------------------------------------------------------------------


// Structs --------------------------------------------------------------------
struct OgreWindow
{
    Ogre::RenderWindow* render;
    SDL_Window* native;
};
//-----------------------------------------------------------------------------

class ApplicationContext : public Ogre::FrameListener
{
protected:
    bool firstRun_;
    Ogre::Root* root_;
    Ogre::String appName_;
    Ogre::FileSystemLayer* fileSystemLayer_;
    Ogre::OverlaySystem* overlaySystem_;
    Ogre::RTShader::ShaderGenerator* shaderGenerator_;
    OgreSGTechniqueResolverListener* materialManagerListener_;

    std::vector<OgreWindow> windows_;
    std::set<std::pair<uint32_t, InputListener*>> inputListeners_;

public:
    explicit ApplicationContext(const Ogre::String& appName = "Ogre3D App");
    virtual ~ApplicationContext();

    Ogre::Root* getRoot() const { return root_; }
    Ogre::FileSystemLayer& getFileSystemLayer() { return *fileSystemLayer_; }
    Ogre::OverlaySystem* getOverlaySystem() const { return overlaySystem_; }
    Ogre::RenderWindow* getRenderWindow() const { return windows_.empty() ? nullptr : windows_[0].render; }

    bool frameStarted(const Ogre::FrameEvent& evt) override;
    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override { return true; }
    bool frameEnded(const Ogre::FrameEvent& evt) override { return true; }

    virtual void initApp();
    virtual void closeApp();
    void createRoot();
    bool oneTimeConfig();
    virtual void setup();
    virtual void shutdown();

    void locateResources();
    void loadResources();

    bool initialiseRTShaderSystem();
    void destroyRTShaderSystem();

    OgreWindow createWindow(const Ogre::String& name, uint32_t w, uint32_t h);
    void destroyWindow(const Ogre::String& name);
    void setWindowGrab(bool _grab);
    void windowMoved(Ogre::RenderWindow* rw) {}
    void windowResized(Ogre::RenderWindow* rw) {}
    bool windowClosing(Ogre::RenderWindow* rw) { return true; }
    void windowClosed(Ogre::RenderWindow* rw) {}
    void windowFocusChange(Ogre::RenderWindow* rw) {}

    void addInputListener(InputListener* lis);
    void removeInputListener(InputListener* lis);
    void pollEvents();

private:
    void _destroyWindow(const OgreWindow& win);
    void _setWindowGrab(SDL_Window* win, bool _grab);

    void _addInputListener(SDL_Window* win, InputListener* lis);
    void _removeInputListener(SDL_Window* win, InputListener* lis);
    void _fireInputEvent(const InputEvent& event, uint32_t windowID) const;
};

#endif // !__APPLICATION_CONTEXT_H__