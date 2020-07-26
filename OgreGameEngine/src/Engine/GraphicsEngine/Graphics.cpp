#include "Graphics.h"
#include "ShaderSystem/ShaderSystem.h"
#include "OverlaySystem/OverlaySystem.h"

#include "ResourcesManager.h"

Window* Graphics::window = nullptr;
Ogre::Root* Graphics::root = nullptr;
bool Graphics::isRendering = false;

Ogre::SceneManager* Graphics::sceneManager = nullptr;
Ogre::Viewport* Graphics::viewport = nullptr;
Ogre::Camera* Graphics::mainCamera = nullptr;

void Graphics::Init()
{
	CreateRoot();
	CreateGraphicContext();

	OverlaySystem::Init();
	ShaderSystem::Init();

	CreateSceneManager();
	
	ResourcesManager::Init();

	isRendering = true;
}

void Graphics::Release()
{
	ResourcesManager::Release();

	ShaderSystem::Release();
	OverlaySystem::Release();
	
	DestroyGraphicContext();
	DestroyRoot();
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

void Graphics::CreateViewport()
{
	if (!mainCamera) CreateMainCamera();

	viewport = window->getRenderWindow()->addViewport(mainCamera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.4, 0.0, 0.6));
}

void Graphics::CreateMainCamera()
{
	mainCamera = sceneManager->createCamera("Main");
	mainCamera->setAutoAspectRatio(true);
	mainCamera->setNearClipDistance(5);

	Ogre::SceneNode* camNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	camNode->setPosition(0, 0, 150);
	camNode->attachObject(mainCamera);
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
	if (!root->restoreConfig()) root->showConfigDialog(nullptr);
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

void Graphics::CreateSceneManager()
{
	sceneManager = root->createSceneManager();
	sceneManager->addRenderQueueListener(OverlaySystem::getOverlaySystem());
	ShaderSystem::getShaderGenerator()->addSceneManager(sceneManager);
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