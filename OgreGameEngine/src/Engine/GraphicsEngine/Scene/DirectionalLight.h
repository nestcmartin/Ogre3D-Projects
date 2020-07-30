#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const Ogre::String& name, const Vec3& dir, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	DirectionalLight(const Ogre::String& name, const Vec3& dir, MovableObject* parent, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
};

#endif // !__DIRECTIONAL_LIGHT_H__