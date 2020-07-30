#include "Light.h"
#include "SceneManager.h"
#include "OgreSceneManager.h"

Light::Light(const Ogre::String& name, LightType type, const Vec3& translate, const Quat& rotate) :
	MovableObject(translate, rotate), light_(nullptr), type_(type)
{
	light_ = SceneManager::Instance()->getSceneManager()->createLight(name);
	light_->setType(static_cast<Ogre::Light::LightTypes>(type));
	node_->attachObject(light_);
}

Light::Light(const Ogre::String& name, LightType type, MovableObject* parent, const Vec3& translate, const Quat& rotate) :
	MovableObject(parent, translate, rotate), light_(nullptr), type_(type)

{
	light_ = SceneManager::Instance()->getSceneManager()->createLight(name);
	light_->setType(static_cast<Ogre::Light::LightTypes>(type));
	node_->attachObject(light_);
}

void Light::setSpotlightRange(float innerAngle, float outerAngle, float falloff)
{
	if (type_ != LightType::SPOT) return;
	light_->setSpotlightRange(Ogre::Radian(Ogre::Degree(innerAngle)), Ogre::Radian(Ogre::Degree(outerAngle)), falloff);
}
