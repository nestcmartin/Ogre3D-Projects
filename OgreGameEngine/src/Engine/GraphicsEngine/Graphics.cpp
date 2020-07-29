#include "Graphics.h"
#include "Scene/SceneManager.h"
#include "ShaderSystem/ShaderSystem.h"
#include "OverlaySystem/OverlaySystem.h"
#include "Bites/OgreBitesConfigDialog.h"

#include "ResourcesManager.h"


float Graphics::FPS = 60.0f;
float Graphics::fpsTimer = 0;
int Graphics::frames = 0;

Window* Graphics::window = nullptr;
Ogre::Root* Graphics::root = nullptr;
bool Graphics::isRendering = false;


void Graphics::Init()
{
	CreateRoot();
	CreateGraphicContext();

	OverlaySystem::Init();
	ShaderSystem::Init();
	ResourcesManager::Init();

	isRendering = true;
}

void Graphics::Release()
{
	SceneManager::Instance()->clearScene();

	ResourcesManager::Release();
	ShaderSystem::Release();
	OverlaySystem::Release();
	
	DestroyGraphicContext();
	DestroyRoot();
}

void Graphics::Update(float deltaTime)
{
	CountFPS(deltaTime / 1000.0f);
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

void Graphics::CreateRoot()
{
	root = OGRE_NEW Ogre::Root();
	if (!root->restoreConfig()) 
		root->showConfigDialog(OgreBites::getNativeConfigDialog());
	root->initialise(false);
}

void Graphics::DestroyRoot()
{
	if (root)
	{
		OGRE_DELETE root;
		root = nullptr;
	}
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

void Graphics::CountFPS(float dt)
{
	frames++;
	fpsTimer += dt;
	if (fpsTimer > 1.0f)
	{
		FPS = frames;
		frames = 0;
		fpsTimer = 0.0f;
	}
}
