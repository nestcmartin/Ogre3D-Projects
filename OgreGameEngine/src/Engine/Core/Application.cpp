#include <iostream>

#include "Timer.h"
#include "Application.h"

#include "RenderSystem/Renderer.h"
#include "InputSystem/InputManager.h"

Application::Application(const std::string& name) :
    frame_(0),
    deltaTime_(0.0f),
    name_(name)
{
    initSubSystems();
}

Application::~Application()
{
    releaseSubSystems();
}

void Application::run()
{
    while (Renderer::IsRendering())
    {
        Timer timer = Timer(&deltaTime_);

        pollEvents();
        Renderer::Present();
    }
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

void Application::initSubSystems()
{
    std::cout << "Initializing all sub systems...\n";
    std::cout << "Initializing the render system...\n";
    Renderer::Init(name_);
    std::cout << "Initializing the input system...\n";
    InputManager::Init();
    std::cout << "All sub systems initialized!\n";
}

void Application::releaseSubSystems()
{
    std::cout << "Releasing all sub systems...\n";
    std::cout << "Releasing the input system...\n";
    InputManager::Release();
    std::cout << "Releasing the render system...\n";
    Renderer::Release();
    std::cout << "All sub systems released!\n";
}
