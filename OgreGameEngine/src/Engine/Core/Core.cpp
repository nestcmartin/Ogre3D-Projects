#include "OgreRoot.h"

#include "SDL.h"

#include "Core.h"

Ogre::Root* Core::root = nullptr;

void Core::Init()
{
	root = OGRE_NEW Ogre::Root();
	if (!root->restoreConfig()) root->showConfigDialog(nullptr);
	root->initialise(false);

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);
}

void Core::Release()
{
	if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_QuitSubSystem(SDL_INIT_VIDEO);

	if (root)
	{
		OGRE_DELETE root;
		root = nullptr;
	}
}