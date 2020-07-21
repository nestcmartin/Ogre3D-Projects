#include "SDL_syswm.h"

#include "OgreFileSystemLayer.h"
#include "OgreOverlaySystem.h"
#include "OgrePlugin.h"
#include "OgreRoot.h"
#include "OgreRTShaderSystem.h"

#include "ApplicationContext.h"
#include "OgreSGTechniqueResolverListener.h"

#include "InputSystem/SDLInputMapper.h"

ApplicationContext::ApplicationContext(const Ogre::String& appName) :
    root_(nullptr),
    firstRun_(true),
    appName_(appName),
    fileSystemLayer_(new Ogre::FileSystemLayer(appName)),
    overlaySystem_(nullptr),
    shaderGenerator_(nullptr),
    materialManagerListener_(nullptr)
{
}

ApplicationContext::~ApplicationContext()
{
    delete fileSystemLayer_;
}


// APP ---------------------------------------------------------------------------------------
void ApplicationContext::initApp()
{
    createRoot();
    if (oneTimeConfig()) setup();
}

void ApplicationContext::createRoot()
{
    Ogre::String pluginsPath = fileSystemLayer_->getConfigFilePath("plugins.cfg");
    root_ = OGRE_NEW Ogre::Root(pluginsPath, fileSystemLayer_->getWritablePath("ogre.cfg"), fileSystemLayer_->getWritablePath("ogre.log"));
    overlaySystem_ = OGRE_NEW Ogre::OverlaySystem();
}

bool ApplicationContext::oneTimeConfig()
{
    if (!root_->restoreConfig()) return root_->showConfigDialog(nullptr);
    return true;
}

void ApplicationContext::setup()
{
    root_->initialise(false);
    createWindow(appName_, 0, 0);

    locateResources();
    initialiseRTShaderSystem();
    loadResources();

    root_->addFrameListener(this);
}

void ApplicationContext::closeApp()
{
    shutdown();
    if (root_)
    {
        OGRE_DELETE root_;
        root_ = nullptr;
    }
}

void ApplicationContext::shutdown()
{
    destroyRTShaderSystem();

    for (auto it = windows_.rbegin(); it != windows_.rend(); ++it)
    {
        _destroyWindow(*it);
    }
    windows_.clear();

    if (overlaySystem_)
    {
        OGRE_DELETE overlaySystem_;
    }

    inputListeners_.clear();

    if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool ApplicationContext::frameStarted(const Ogre::FrameEvent& evt)
{
    pollEvents();
    return true;
}



// FILE SYSTEM -------------------------------------------------------------------------------

void ApplicationContext::locateResources()
{
    Ogre::ConfigFile cf;
    Ogre::String resourcesPath = fileSystemLayer_->getConfigFilePath("resources.cfg");
    cf.load(resourcesPath);

    Ogre::String sec, type, arch;
    Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();

    // Go through all specified resource groups
    Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
    for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
    {
        sec = seci->first;
        const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
        Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

        // Go through all resource paths
        for (i = settings.begin(); i != settings.end(); i++)
        {
            type = i->first;
            arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
            rgm.addResourceLocation(arch, type, sec);
        }
    }

    sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    const Ogre::ResourceGroupManager::LocationList genLocs = rgm.getResourceLocationList(sec);
    OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

    arch = genLocs.front().archive->getName();
    arch = Ogre::StringUtil::replaceAll(arch, "Media/../../Tests/Media", "");
    arch = Ogre::StringUtil::replaceAll(arch, "media/../../Tests/Media", "");
    type = genLocs.front().archive->getType();

    bool hasCgPlugin = false;
    const Ogre::Root::PluginInstanceList& plugins = getRoot()->getInstalledPlugins();
    for (size_t i = 0; i < plugins.size(); i++)
    {
        if (plugins[i]->getName() == "Cg Program Manager")
        {
            hasCgPlugin = true;
            break;
        }
    }

    bool use_HLSL_Cg_shared = hasCgPlugin || Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl");

    // Add locations for supported shader languages
    if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
        rgm.addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
    }
    else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
        rgm.addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

        if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
        {
            rgm.addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
        }
        if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
        {
            rgm.addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
        }
    }
    else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
    }

    if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("spirv"))
    {
        rgm.addResourceLocation(arch + "/materials/programs/SPIRV", type, sec);
    }

    if (hasCgPlugin)
        rgm.addResourceLocation(arch + "/materials/programs/Cg", type, sec);
    if (use_HLSL_Cg_shared)
        rgm.addResourceLocation(arch + "/materials/programs/HLSL_Cg", type, sec);

}

void ApplicationContext::loadResources()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}



// SHADER SYSTEM -----------------------------------------------------------------------------

bool ApplicationContext::initialiseRTShaderSystem()
{
    if (Ogre::RTShader::ShaderGenerator::initialize())
    {
        shaderGenerator_ = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        if (!materialManagerListener_)
        {
            materialManagerListener_ = new OgreSGTechniqueResolverListener(shaderGenerator_);
        }
    }

    return true;
}

void ApplicationContext::destroyRTShaderSystem()
{
    // Restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

    // Unregister the material manager listener.
    if (materialManagerListener_)
    {
        Ogre::MaterialManager::getSingleton().removeListener(materialManagerListener_);
        delete materialManagerListener_;
        materialManagerListener_ = nullptr;
    }

    // Destroy RTShader system.
    if (shaderGenerator_)
    {
        Ogre::RTShader::ShaderGenerator::destroy();
        shaderGenerator_ = nullptr;
    }
}



// WINDOW ------------------------------------------------------------------------------------

OgreWindow ApplicationContext::createWindow(const Ogre::String& name, uint32_t w, uint32_t h)
{
    OgreWindow window = { NULL, NULL };

    if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

    Ogre::NameValuePairList miscParams = Ogre::NameValuePairList();
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

void ApplicationContext::destroyWindow(const Ogre::String& name)
{
    for (auto it = windows_.begin(); it != windows_.end(); ++it)
    {
        if (it->render->getName() != name) continue;
        _destroyWindow(*it);
        windows_.erase(it);
        return;
    }

    OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, "No window named '" + name + "'");
}

void ApplicationContext::_destroyWindow(const OgreWindow& win)
{
    root_->destroyRenderTarget(win.render);
    if (win.native) SDL_DestroyWindow(win.native);
}

void ApplicationContext::setWindowGrab(bool grab)
{
    OgreAssert(!windows_.empty(), "create a window first");
    _setWindowGrab(windows_[0].native, grab);
}

void ApplicationContext::_setWindowGrab(SDL_Window* win, bool _grab)
{
    SDL_bool grab = SDL_bool(_grab);
    SDL_SetWindowGrab(win, grab);
    SDL_ShowCursor(!grab);
}



// INPUT ------------------------------------------------------------------------------------ 
void ApplicationContext::addInputListener(InputListener* lis)
{
    OgreAssert(!windows_.empty(), "create a window first");
    _addInputListener(windows_[0].native, lis);
}

void ApplicationContext::_addInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.insert(std::make_pair(SDL_GetWindowID(win), lis));
}

void ApplicationContext::removeInputListener(InputListener* lis)
{
    OgreAssert(!windows_.empty(), "called after all windows were deleted");
    _removeInputListener(windows_[0].native, lis);
}

void ApplicationContext::_removeInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.erase(std::make_pair(SDL_GetWindowID(win), lis));
}

void ApplicationContext::pollEvents()
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

void ApplicationContext::_fireInputEvent(const InputEvent& event, uint32_t windowID) const
{
    InputEvent scaled = event;
    for (auto it = inputListeners_.begin(); it != inputListeners_.end(); ++it)
    {
        if (it->first != windowID) continue;

        InputListener& l = *it->second;
        switch (event.type)
        {
        case KEYDOWN:
            l.keyPressed(event.key);
            break;
        case KEYUP:
            l.keyReleased(event.key);
            break;
        case MOUSEBUTTONDOWN:
            l.mousePressed(event.button);
            break;
        case MOUSEBUTTONUP:
            l.mouseReleased(event.button);
            break;
        case MOUSEWHEEL:
            l.mouseWheelRolled(event.wheel);
            break;
        case MOUSEMOTION:
            l.mouseMoved(scaled.motion);
            break;
        case FINGERDOWN:
            l.touchMoved(event.tfinger);
            l.touchPressed(event.tfinger);
            break;
        case FINGERUP:
            l.touchReleased(event.tfinger);
            break;
        case FINGERMOTION:
            l.touchMoved(event.tfinger);
            break;
        case TEXTINPUT:
            l.textInput(event.text);
            break;
        }
    }
}