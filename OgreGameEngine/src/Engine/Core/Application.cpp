#include "Core.h"
#include "Window.h"
#include "Resources.h"
#include "Application.h"
#include "InputSystem/InputManager.h"

Application::Application(const Ogre::String& name) :
	window_(new Window())
{
	Resources::Init(name);
	Core::Init();

	window_->initWindow(name, 1280, 720);

    InputManager::Init();

	Resources::Locate();
	Resources::InitShaderSystem();
	Resources::Load();

    Core::Root()->addFrameListener(this);
}

Application::~Application()
{
	Resources::ReleaseShaderSystem();

    window_->destroyWindow();
    window_ = nullptr;

    InputManager::Release();

	Core::Release();
	Resources::Release();
}

bool Application::frameStarted(const Ogre::FrameEvent& evt)
{
	pollEvents();
	return true;
}

void Application::run()
{
    Core::Root()->startRendering();
}

void Application::pollEvents()
{
    if (!window_) return;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Core::Root()->queueEndRendering();
            break;

        case SDL_WINDOWEVENT:
        {
            if (event.window.event != SDL_WINDOWEVENT_RESIZED) continue;
            if (event.window.windowID != SDL_GetWindowID(window_->getNativeWindow())) continue;
            Ogre::RenderWindow* win = window_->getRenderWindow();
            win->windowMovedOrResized();
            window_->windowResized(win);
        }
            break;

        default:
            InputManager::ProcessInputEvent(event);
            break;
        }
    }
}
