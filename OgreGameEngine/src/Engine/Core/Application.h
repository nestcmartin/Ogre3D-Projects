#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "OgreImGuiOverlay.h"
#include "OgreRenderTargetListener.h"

#include "InputSystem/InputListenerChain.h"
#include "GraphicsEngine/OverlaySystem/UIListener.h"

class Clock;

class Application : public InputListener, public Ogre::RenderTargetListener
{
protected:
	Clock* clock_;
	const char* name_;

	InputListenerChain listenerChain_;
	std::unique_ptr<UIListener> uiListener_;

public:
	explicit Application(const char* name);
	virtual ~Application();

	virtual void run();
	
	void pollEvents();

	void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
	bool keyPressed(const KeyboardEvent& evt) { return listenerChain_.keyPressed(evt); }
	bool keyReleased(const KeyboardEvent& evt) { return listenerChain_.keyReleased(evt); }
	bool mouseMoved(const MouseMotionEvent& evt) { return listenerChain_.mouseMoved(evt); }
	bool mouseWheelRolled(const MouseWheelEvent& evt) { return listenerChain_.mouseWheelRolled(evt); }
	bool mousePressed(const MouseButtonEvent& evt) { return listenerChain_.mousePressed(evt); }
	bool mouseReleased(const MouseButtonEvent& evt) { return listenerChain_.mouseReleased(evt); }
	bool textInput(const TextInputEvent& evt) { return listenerChain_.textInput(evt); }
};

#endif // !__APPLICATION_H__