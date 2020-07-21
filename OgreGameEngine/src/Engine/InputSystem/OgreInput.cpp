#include "OgreInput.h"

InputListenerChain& InputListenerChain::operator=(InputListenerChain o)
{
	listenerChain_ = o.listenerChain_;
	return *this;
}

bool InputListenerChain::keyPressed(const KeyboardEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->keyPressed(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::keyReleased(const KeyboardEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->keyReleased(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::touchMoved(const TouchFingerEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->touchMoved(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::touchPressed(const TouchFingerEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->touchPressed(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::touchReleased(const TouchFingerEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->touchReleased(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::mouseMoved(const MouseMotionEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->mouseMoved(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::mouseWheelRolled(const MouseWheelEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->mouseWheelRolled(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::mousePressed(const MouseButtonEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->mousePressed(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::mouseReleased(const MouseButtonEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->mouseReleased(evt))
			return true;
	}
	return false;
}
bool InputListenerChain::textInput(const TextInputEvent& evt)
{
	for (auto listner : listenerChain_)
	{
		if (listner->textInput(evt))
			return true;
	}
	return false;
}