#include "Core.h"
#include "Clock.h"
#include "Application.h"
#include "InputSystem/InputManager.h"

Application::Application(const char* name) :
    name_(name), 
    clock_(nullptr)
{
    clock_ = new Clock();

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
    float dt = clock_->getDeltaTime();

    while (Graphics::IsRendering())
    {
        clock_->startTimer();
        
        pollEvents();
        Graphics::Update(dt);
        Physics::Update(dt);

        clock_->endTimer();

        dt = clock_->getDeltaTime();
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
