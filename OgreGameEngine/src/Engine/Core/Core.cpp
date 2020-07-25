#include "Core.h"

void Core::StartUp()
{
    Graphics::Init();
    Physics::Init();
}

void Core::ShutDown()
{
    Physics::Release();
    Graphics::Release();
}
