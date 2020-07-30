#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "OgreLight.h"
#include "MovableObject.h"

enum LightType { POINT, DIRECTIONAL, SPOT };

class Light : public MovableObject
{
protected:
	LightType type_;
	Ogre::Light* light_;

public:
	Light(const Ogre::String& name, LightType type, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	Light(const Ogre::String& name, LightType type, MovableObject* parent, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);

	void setDiffuseColour(float r, float g, float b) { light_->setDiffuseColour(r, g, b); }
	void setSpecularColour(float r, float g, float b) { light_->setSpecularColour(r, g, b); }

	void setPower(float power) { light_->setPowerScale(power); }

	void setSpotlightRange(float inner, float outer, float falloff = 1.0f);

};

#endif // !__LIGHT_H__
