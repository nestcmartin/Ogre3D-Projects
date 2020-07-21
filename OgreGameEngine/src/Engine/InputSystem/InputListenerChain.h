#ifndef __INPUT_LISTENER_CHAIN_H__
#define __INPUT_LISTENER_CHAIN_H__

#include <vector>

#include "InputListener.h"


class InputListenerChain : public InputListener
{
protected:
	std::vector<InputListener*> listenerChain_;

public:
	InputListenerChain() {}
	InputListenerChain(std::vector<InputListener*> chain) : listenerChain_(chain) {}

	InputListenerChain& operator=(InputListenerChain o);

	bool keyPressed(const KeyboardEvent& evt) override;
	bool keyReleased(const KeyboardEvent& evt) override;
	bool touchMoved(const TouchFingerEvent& evt) override;
	bool touchPressed(const TouchFingerEvent& evt) override;
	bool touchReleased(const TouchFingerEvent& evt) override;
	bool mouseMoved(const MouseMotionEvent& evt) override;
	bool mouseWheelRolled(const MouseWheelEvent& evt) override;
	bool mousePressed(const MouseButtonEvent& evt) override;
	bool mouseReleased(const MouseButtonEvent& evt) override;
	bool textInput(const TextInputEvent& evt) override;
};


#endif // !__INPUT_LISTENER_CHAIN_H__