#include <iostream>

#include "Core.h"
#include "RenderSystem/Renderer.h"
#include "InputSystem/InputManager.h"

void Core::Init()
{
	std::cout << "Initializing all sub systems...\n";
	std::cout << "Initializing the render system...\n";
	Renderer::Init();
	std::cout << "Initializing the input system...\n";
	InputManager::Init();
	std::cout << "All sub systems initialized!\n";
}

void Core::Release()
{
	std::cout << "Releasing all sub systems...\n";
	std::cout << "Releasing the input system...\n";
	InputManager::Release();
	std::cout << "Releasing the input system...\n";
	Renderer::Release();
	std::cout << "All sub systems released!\n";
}