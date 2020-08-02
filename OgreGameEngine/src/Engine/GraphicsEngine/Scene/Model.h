#ifndef __MESH_H__
#define __MESH_H__

#include "OgreEntity.h"
#include "MovableObject.h"

enum ShaderParam : size_t { SP_SHININESS = 1, SP_DIFFUSE, SP_SPECULAR };

class Model : public MovableObject
{
protected:
	Ogre::Entity* entity_;

public:
	Model(const Ogre::String& name, const Ogre::String& mesh, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	Model(const Ogre::String& name, const Ogre::String& mesh, MovableObject* parent, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	Model(const Ogre::String& name, const Ogre::String& mesh, const Vec3& normal, const Vec3& up, float width, float height, int xseg, int yseg, float utile, float vtile);

	void setMaterialName(const Ogre::String& name) { entity_->setMaterialName(name); }
	void setCustomProperty(size_t i, size_t param, float r, float g, float b, float a) { entity_->getSubEntity(i)->setCustomParameter(param, Ogre::Vector4(r, g, b, a)); }

	void setCastShadows(bool shadows) { entity_->setCastShadows(shadows); }
};

#endif // !__MESH_H__
