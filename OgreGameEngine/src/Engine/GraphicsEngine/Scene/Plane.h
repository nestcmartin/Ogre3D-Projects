#ifndef __PLANE_H__
#define __PLANE_H__

#include "MovableObject.h"

class Plane : public MovableObject
{
private:
	Ogre::Entity* entity_;

public:
	Plane(const Ogre::String& name, const Ogre::String& mesh, const Ogre::Vector3& normal, const Ogre::Vector3& up, float width, float height, int xseg, int yseg, float utile, float vtile);
	virtual ~Plane();

	Ogre::MovableObject* getOgreObject() override { return entity_; }

	void setMaterialName(const Ogre::String& name) { entity_->setMaterialName(name); }
	void setCastShadows(bool shadows) { entity_->setCastShadows(shadows); }
};

#endif // !__PLANE_H__