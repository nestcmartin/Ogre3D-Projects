#ifndef __MESH_H__
#define __MESH_H__

#include "MovableObject.h"

enum ShaderParam : size_t { SP_SHININESS = 1, SP_DIFFUSE, SP_SPECULAR };
enum AnimationBlendMode { AVERAGE, CUMULATIVE };

class Model : public MovableObject
{
protected:
	Ogre::Entity* entity_;

public:
	Model(const Ogre::String& name, const Ogre::String& mesh);
	Model(const Ogre::String& name, const Ogre::String& mesh, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);
	Model(const Ogre::String& name, const Ogre::String& mesh, MovableObject* parent, const Ogre::Vector3& translate = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);

	Ogre::MovableObject* getOgreObject() override { return entity_; }

	void setMaterialName(const Ogre::String& name) { entity_->setMaterialName(name); }
	void setCustomProperty(size_t i, size_t param, float r, float g, float b, float a) { entity_->getSubEntity(i)->setCustomParameter(param, Ogre::Vector4(r, g, b, a)); }

	void setCastShadows(bool shadows) { entity_->setCastShadows(shadows); }

	void detachAllObjectsFromBone() { entity_->detachAllObjectsFromBone(); }
	void attachObjectToBone(MovableObject* obj, const Ogre::String& bone) { entity_->attachObjectToBone(bone, obj->getOgreObject()); }
	void setAnimationBlendMode(AnimationBlendMode mode) { entity_->getSkeleton()->setBlendMode(static_cast<Ogre::SkeletonAnimationBlendMode>(mode)); }
	Ogre::AnimationState* getAnimationState(const Ogre::String& name) { return entity_->getAnimationState(name); }
};

#endif // !__MESH_H__
