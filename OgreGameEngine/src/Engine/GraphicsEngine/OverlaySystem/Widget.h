#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include "OgreImGuiOverlay.h"

class Widget
{
protected:
	float x_;
	float y_;
	float w_;
	float h_;

	bool has_titlebar;
	bool has_scrollbar;
	bool has_menu;
	bool has_move;
	bool has_resize;
	bool has_collapse;
	bool has_nav;
	bool has_background;
	bool has_bring_to_front;

	bool* opened_;
	Ogre::String name_;
	ImGuiWindowFlags flags_;

public:
	Widget(const char* name, bool opened = true, float x = 0, float y = 0, float w = 500, float h = 300,
		bool title = false, bool scroll = false, bool menu = false, bool move = false, bool resize = false, 
		bool collapse = false, bool nav = false, bool background = false, bool front = false);
	virtual ~Widget() {}

	float getX() const { return x_; }
	float getY() const { return y_; }
	float getW() const { return w_; }
	float getH() const { return h_; }
	void setX(float x) { x_ = x; }
	void setY(float y) { y_ = y; }
	void setW(float w) { w_ = w; }
	void setH(float h) { h_ = h; }

	virtual void show();
};

class FPSCounterWidget : public Widget
{
protected:
	int corner = 0;
	const float DISTANCE = 10.0f;

public:
	FPSCounterWidget(const char* name, bool opened = true) : Widget(name, opened) {}
	virtual ~FPSCounterWidget() {}
	void show() override;
};

#endif // !__OVERLAY_H__