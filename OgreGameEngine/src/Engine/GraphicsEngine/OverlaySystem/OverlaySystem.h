#ifndef __OVERLAY_MANAGER_H__
#define __OVERLAY_MANAGER_H__

#include "OgreOverlaySystem.h"
#include "OgreImGuiOverlay.h"
#include "OgreRenderTargetListener.h"

#include "Core/InputSystem/InputListenerUI.h"
#include "Core/InputSystem/InputListenerChain.h"

class OverlaySystem : public Ogre::RenderTargetListener
{
private:
	Ogre::OverlaySystem* overlaySystem;

	InputListenerChain listenerChain;
	std::unique_ptr<InputListenerUI> inputListenerUI;

public:
	OverlaySystem();
	~OverlaySystem() {}

	void Init();
	void Release();

	Ogre::OverlaySystem* getOverlaySystem() { return overlaySystem; }

	void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
	
	//bool keyPressed(const KeyboardEvent& evt) { return listenerChain.keyPressed(evt); }
	//bool keyReleased(const KeyboardEvent& evt) { return listenerChain.keyReleased(evt); }
	//bool mouseMoved(const MouseMotionEvent& evt) { return listenerChain.mouseMoved(evt); }
	//bool mouseWheelRolled(const MouseWheelEvent& evt) { return listenerChain.mouseWheelRolled(evt); }
	//bool mousePressed(const MouseButtonEvent& evt) { return listenerChain.mousePressed(evt); }
	//bool mouseReleased(const MouseButtonEvent& evt) { return listenerChain.mouseReleased(evt); }
	//bool textInput(const TextInputEvent& evt) { return listenerChain.textInput(evt); }
};

#endif // !__OVERLAY_MANAGER_H__
