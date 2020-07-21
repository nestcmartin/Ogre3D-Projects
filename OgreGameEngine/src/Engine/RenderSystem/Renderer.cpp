#include "Renderer.h"
#include "ShaderSystem.h"
#include "ResourcesManager.h"

Window* Renderer::window = nullptr;
Ogre::Root* Renderer::root = nullptr;
bool Renderer::isRendering = true;
Ogre::OverlaySystem* Renderer::overlaySystem = nullptr;

void Renderer::Init(const Ogre::String& name)
{
	root = OGRE_NEW Ogre::Root();
	overlaySystem = OGRE_NEW Ogre::OverlaySystem();

	if (!root->restoreConfig()) root->showConfigDialog(nullptr);
	root->initialise(false);

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	window = new Window();
	window->initWindow(name, 1280, 720);

	ShaderSystem::Init();
	ResourcesManager::Init(name);
}

void Renderer::Present()
{
	root->renderOneFrame();
}

void Renderer::Release()
{
	ResourcesManager::Release();
	ShaderSystem::Release();

	if (window)
	{
		window->destroyWindow();
		window = nullptr;
	}

	if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);

	if (overlaySystem)
	{
		OGRE_DELETE overlaySystem;
		overlaySystem = nullptr;
	}

	if (root)
	{
		OGRE_DELETE root;
		root = nullptr;
	}
}

void Renderer::Start()
{
	root->startRendering();
}

void Renderer::Stop()
{
	isRendering = false;
	root->queueEndRendering();
}

void Renderer::ProcessWindowEvent(const SDL_Event& event)
{
	if (event.window.event != SDL_WINDOWEVENT_RESIZED) return;
	if (event.window.windowID != SDL_GetWindowID(window->getNativeWindow())) return;
	Ogre::RenderWindow* win = window->getRenderWindow();
	win->windowMovedOrResized();
	window->windowResized(win);
}