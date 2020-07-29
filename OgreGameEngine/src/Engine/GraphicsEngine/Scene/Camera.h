#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "MovableObject.h"

namespace Ogre { 
	class Camera;
	class Viewport;
	class SceneNode;
}

class Camera : public MovableObject
{
protected:
	Ogre::Camera* camera_;
	Ogre::Viewport* viewport_;

public:
	Camera();
	Camera(const char* name, Transform* t);
	virtual ~Camera() {}

	void attach() override { transform_->attach(camera_); }

	void setBackgroundColor(float r, float g, float b);
	void setNearClipDistance(float val);
	void setFarClipDistance(float val);
};

#endif // !__CAMERA_H__
