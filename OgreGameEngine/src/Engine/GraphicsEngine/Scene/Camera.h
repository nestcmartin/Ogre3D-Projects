#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "OgreCamera.h"
#include "OgreViewport.h"
#include "MovableObject.h"

class Camera : public MovableObject
{
protected:
	Ogre::Camera* camera_;
	Ogre::Viewport* viewport_;

public:
	Camera(const Ogre::String& name, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	Camera(const Ogre::String& name, MovableObject* parent, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	virtual ~Camera() {}

	void setViewportColor(float r, float g, float b) { viewport_->setBackgroundColour(Ogre::ColourValue(r, g, b)); }
	void setAutoAspectRatio(bool autoar) { camera_->setAutoAspectRatio(autoar); }
	void setAspectRatio(float ar) { camera_->setAspectRatio(ar); }
	float getAspectRatio() const { return camera_->getAspectRatio(); }

	void setNearClipDistance(float val) { camera_->setNearClipDistance(val); }
	void setFarClipDistance(float val) { camera_->setFarClipDistance(val); }
};

#endif // !__CAMERA_H__