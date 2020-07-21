#include "Core.h"
#include "Application.h"
#include "RenderSystem/Renderer.h"
#include "InputSystem/InputManager.h"

Application::Application(const Ogre::String& name)
{
	Core::Init();
    Renderer::AddFrameListener(this);
}

Application::~Application()
{
	Core::Release();
}

bool Application::frameStarted(const Ogre::FrameEvent& evt)
{
	pollEvents();
	return true;
}

void Application::run()
{
    Renderer::Start();
}

void Application::pollEvents()
{
    if (!Renderer::GetWindow()) return;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Renderer::Stop();
            break;

        case SDL_WINDOWEVENT:
            Renderer::ProcessWindowEvent(event);
            break;

        default:
            InputManager::ProcessInputEvent(event);
            break;
        }
    }
}
