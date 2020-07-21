#ifndef __INPUT_LISTENER_H__
#define __INPUT_LISTENER_H__

struct KeyboardEvent;
struct TouchFingerEvent;
struct TouchFingerEvent;
struct MouseMotionEvent;
struct MouseWheelEvent;
struct MouseButtonEvent;
struct TextInputEvent;

struct InputListener
{
	virtual ~InputListener() {}

	virtual bool keyPressed(const KeyboardEvent& evt) { return false; }
	virtual bool keyReleased(const KeyboardEvent& evt) { return false; }
	virtual bool touchMoved(const TouchFingerEvent& evt) { return false; }
	virtual bool touchPressed(const TouchFingerEvent& evt) { return false; }
	virtual bool touchReleased(const TouchFingerEvent& evt) { return false; }
	virtual bool mouseMoved(const MouseMotionEvent& evt) { return false; }
	virtual bool mouseWheelRolled(const MouseWheelEvent& evt) { return false; }
	virtual bool mousePressed(const MouseButtonEvent& evt) { return false; }
	virtual bool mouseReleased(const MouseButtonEvent& evt) { return false; }
	virtual bool textInput(const TextInputEvent& evt) { return false; }
};

#endif // !__INPUT_LISTENER_H__
