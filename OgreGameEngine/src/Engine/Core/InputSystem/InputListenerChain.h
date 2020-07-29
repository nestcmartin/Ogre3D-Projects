#ifndef __INPUT_LISTENER_CHAIN_H__
#define __INPUT_LISTENER_CHAIN_H__

#include "Core/LowLevel/STLHeaders.h"

#include "InputListener.h"

class InputListenerChain : public InputListener
{
protected:
    std::vector<InputListener*> listenerChain_;

public:
    InputListenerChain() {}
    InputListenerChain(std::vector<InputListener*> chain) : listenerChain_(chain) {}

    InputListenerChain& operator=(InputListenerChain o)
    {
        listenerChain_ = o.listenerChain_;
        return *this;
    }

    bool keyPressed(const KeyboardEvent& evt);
    bool keyReleased(const KeyboardEvent& evt);
    bool touchMoved(const TouchFingerEvent& evt);
    bool touchPressed(const TouchFingerEvent& evt);
    bool touchReleased(const TouchFingerEvent& evt);
    bool mouseMoved(const MouseMotionEvent& evt);
    bool mouseWheelRolled(const MouseWheelEvent& evt);
    bool mousePressed(const MouseButtonEvent& evt);
    bool mouseReleased(const MouseButtonEvent& evt);
    bool textInput(const TextInputEvent& evt);
};

#endif // !__INPUT_LISTENER_CHAIN_H__