#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Window.h"

#include "OgreOverlaySystem.h"

class Graphics
{
private:
	static Window* window;
	static Ogre::Root* root;
	static bool isRendering;

	static Ogre::OverlaySystem* overlaySystem;

public:
	static void Init();
	static void Release();

	static void Update();
	static void ResizeWindow();
	static void StopRendering();

	static Window* GetWindow() { return window; }
	static Ogre::Root* GetRoot() { return root; }
	static bool IsRendering() { return isRendering; }

protected:
	static void CreateGraphicContext();
	static void DestroyGraphicContext();
};

#endif // !__GRAPHICS_H__
