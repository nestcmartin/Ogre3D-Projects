#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Ogre::String& name, const Vec3& dir, const Vec3& translate, const Quat& rotate) :
	Light(name, translate, rotate)
{
	light_->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
}

DirectionalLight::DirectionalLight(const Ogre::String& name, const Vec3& dir, MovableObject* parent, const Vec3& translate, const Quat& rotate) :
	Light(name, parent, translate, rotate)
{
	light_->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
}
