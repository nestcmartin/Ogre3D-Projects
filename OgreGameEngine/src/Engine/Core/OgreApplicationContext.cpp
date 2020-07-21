#include "OgreFileSystemLayer.h"
#include "OgreOverlaySystem.h"
#include "OgrePlugin.h"
#include "OgreRoot.h"
#include "OgreRTShaderSystem.h"

#include "OgreApplicationContext.h"
#include "OgreSGTechniqueResolverListener.h"
#include "OgreInput.h"

OgreApplicationContext::OgreApplicationContext(const Ogre::String& appName) :
	root_(nullptr),
	firstRun_(true),
	appName_(appName),
	fileSystemLayer_(new Ogre::FileSystemLayer(appName)),
	overlaySystem_(nullptr),
	shaderGenerator_(nullptr),
	materialManagerListener_(nullptr)
{
}

OgreApplicationContext::~OgreApplicationContext()
{
	delete fileSystemLayer_;
}

void OgreApplicationContext::initApp()
{
	createRoot();
	if (oneTimeConfig()) setup();
}

void OgreApplicationContext::closeApp()
{
    shutdown();
    if (root_)
    {
        OGRE_DELETE root_;
        root_ = nullptr;
    }
}

bool OgreApplicationContext::frameStarted(const Ogre::FrameEvent& evt)
{
    pollEvents();
    return true;
}

bool OgreApplicationContext::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    for (auto it = inputListeners_.begin(); it != inputListeners_.end(); ++it) 
    {
        it->second->frameRendered(evt);
    }
    return true;
}

void OgreApplicationContext::addInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.insert(std::make_pair(0, lis));
}

void OgreApplicationContext::addInputListener(InputListener* lis)
{
    OgreAssert(!windows_.empty(), "create a window first");
    addInputListener(windows_[0].native, lis);
}

void OgreApplicationContext::removeInputListener(SDL_Window* win, InputListener* lis)
{
    inputListeners_.erase(std::make_pair(0, lis));
}

void OgreApplicationContext::removeInputListener(InputListener* lis)
{
    OgreAssert(!windows_.empty(), "called after all windows were deleted");
    removeInputListener(windows_[0].native, lis);
}

void OgreApplicationContext::setWindowGrab(bool grab)
{
    OgreAssert(!windows_.empty(), "create a window first");
    setWindowGrab(windows_[0].native, grab);
}

void OgreApplicationContext::_fireInputEvent(const Event& event, uint32_t windowID) const
{
    Event scaled = event;
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

void OgreApplicationContext::createRoot()
{
	Ogre::String pluginsPath = fileSystemLayer_->getConfigFilePath("plugins.cfg");
	root_ = OGRE_NEW Ogre::Root(pluginsPath, fileSystemLayer_->getWritablePath("ogre.cfg"), fileSystemLayer_->getWritablePath("ogre.log"));
	overlaySystem_ = OGRE_NEW Ogre::OverlaySystem();
}

bool OgreApplicationContext::oneTimeConfig()
{
	if (!root_->restoreConfig()) return root_->showConfigDialog(nullptr);
	return true;
}

void OgreApplicationContext::setup()
{
	root_->initialise(false);
	createWindow(appName_, 0, 0, Ogre::NameValuePairList());

	locateResources();
	initialiseRTShaderSystem();
	loadResources();

	root_->addFrameListener(this);
}

void OgreApplicationContext::shutdown()
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
}

Window OgreApplicationContext::createWindow(const Ogre::String& name, uint32_t w, uint32_t h, Ogre::NameValuePairList miscParams)
{
	Window window = { NULL, NULL };

	if (!windows_.empty()) miscParams["currentGLContext"] = "true";
	Ogre::RenderWindowDescription d = root_->getRenderSystem()->getRenderWindowDescription();
	miscParams.insert(d.miscParams.begin(), d.miscParams.end());
	d.miscParams = miscParams;
	if (w > 0) d.width = w;
	if (h > 0) d.height = h;
	d.name = name;

	window.render = root_->createRenderWindow(d);
	windows_.push_back(window);

	return window;
}

void OgreApplicationContext::destroyWindow(const Ogre::String& name)
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

void OgreApplicationContext::_destroyWindow(const Window& win)
{
    root_->destroyRenderTarget(win.render);
}

void OgreApplicationContext::locateResources()
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

void OgreApplicationContext::loadResources()
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool OgreApplicationContext::initialiseRTShaderSystem()
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

void OgreApplicationContext::destroyRTShaderSystem()
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

void OgreApplicationContext::pollEvents()
{
}
