#include "Core.h"
#include "Clock.h"
#include "Application.h"
#include "InputManager.h"

Application::Application(const char* name) :
    name_(name)
{
    Core::StartUp();
    Graphics::GetWindow()->setWindowName(name_);
    InputManager::Instance()->addInputListener(this);
}

Application::~Application()
{
    Core::ShutDown();
}

void Application::run()
{
    Clock realTime;
    float rdt = realTime.getDeltaTime();

    while (Graphics::IsRendering())
    {
        realTime.startTimer();
        
        pollEvents();
        Graphics::Update();

        realTime.endTimer();

        rdt = realTime.getDeltaTime();
        std::cout << rdt / 1000.0f << "\n";
    }
}

void Application::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Graphics::StopRendering();
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) Graphics::ResizeWindow();
            break;

        default:
            InputManager::Instance()->processInputEvent(event);
            break;
        }
    }
}