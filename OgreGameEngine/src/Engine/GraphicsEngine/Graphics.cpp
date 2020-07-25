#include "Graphics.h"
#include "ShaderSystem.h"
#include "ResourcesManager.h"

Window* Graphics::window = nullptr;
Ogre::Root* Graphics::root = nullptr;
bool Graphics::isRendering = false;
Ogre::OverlaySystem* Graphics::overlaySystem = nullptr;

void Graphics::Init()
{
	root = OGRE_NEW Ogre::Root();
	overlaySystem = OGRE_NEW Ogre::OverlaySystem();

	if (!root->restoreConfig()) root->showConfigDialog(nullptr);
	root->initialise(false);

	CreateGraphicContext();

	ShaderSystem::Init();
	ResourcesManager::Init();

	isRendering = true;
}

void Graphics::Release()
{
	ResourcesManager::Release();
	ShaderSystem::Release();

	DestroyGraphicContext();

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

void Graphics::Update(float deltaTime)
{
	root->renderOneFrame(deltaTime);
}

void Graphics::StopRendering()
{
	isRendering = false;
	root->queueEndRendering();
}

void Graphics::ResizeWindow()
{
	Ogre::RenderWindow* win = window->getRenderWindow();
	win->windowMovedOrResized();
	window->windowResized(win);
}

void Graphics::CreateGraphicContext()
{
	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	window = new Window();
	window->initWindow();
}

void Graphics::DestroyGraphicContext()
{
	if (window)
	{
		window->destroyWindow();
		window = nullptr;
	}

	if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
