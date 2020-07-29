#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "OgreSceneNode.h"
#include "Core/LowLevel/Vec3.h"
#include "Core/LowLevel/Quat.h"

enum TransformSpace { LOCAL = 0, PARENT = 1, WORLD = 2 };

class Transform
{
private:
	const char* name_;
	Ogre::SceneNode* node_;

	Transform(const char* name, Ogre::SceneNode* node) : name_(name), node_(node) {}

public:
	Transform(const Vec3& pos = Vec3::ZERO, const Quat& rot = Quat::IDENTITY);
	Transform(const char* name, const Vec3& pos = Vec3::ZERO, const Quat& rot = Quat::IDENTITY);
	inline Transform(const Transform& t) : name_(t.name_), node_(t.node_) {}
	inline Transform& operator=(const Transform& t)
	{
		name_ = t.name_;
		node_ = t.node_;
		return *this;
	}

	Transform* addChild(const char* name, const Vec3& pos = Vec3::ZERO, const Quat& rot = Quat::IDENTITY);

	const Vec3& position() const { return node_->getPosition(); }
	const Quat& rotation() const { return node_->getOrientation(); }
	const Vec3& scale() const { return node_->getScale(); }

	void setPosition(const Vec3& p) { node_->setPosition(V3(p)); }
	void setPosition(float x, float y, float z) { node_->setPosition(x, y, z); }
	void setRotation(const Quat& q) { node_->setOrientation(Q(q)); }
	void setRotation(float w, float x, float y, float z) { node_->setOrientation(w, x, y, z); }
	void setScale(const Vec3& scale) { node_->setScale(V3(scale)); }
	void setScale(float x, float y, float z) { node_->setScale(x, y, z); }

	void translate(const Vec3& d, TransformSpace ts = TransformSpace::PARENT) { node_->translate(V3(d), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void translate(float x, float y, float z, TransformSpace ts = TransformSpace::PARENT) { node_->translate(x, y, z, static_cast<Ogre::Node::TransformSpace>(ts)); }

	void rotate(const Quat& rot, TransformSpace ts = TransformSpace::LOCAL) { node_->rotate(Q(rot), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void rotate(const Vec3& axis, float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->rotate(V3(axis), Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void yaw(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->yaw(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void pitch(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->pitch(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void roll(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->roll(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }

	void setDirection(const Vec3& dir, TransformSpace ts = TransformSpace::LOCAL) { node_->setDirection(V3(dir), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void lookAt(const Vec3& target, TransformSpace ts = TransformSpace::LOCAL) { node_->lookAt(V3(target), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void setAutoTracking(bool enabled, Transform* t = nullptr, const Vec3& localDirectionVector = Vec3::NEGATIVE_UNIT_Z, const Vec3& offset = Vec3::ZERO) { node_->setAutoTracking(enabled, t->node_, V3(localDirectionVector), V3(offset)); }
	
	void setVisible(bool visibility) { node_->setVisible(visibility); }
	void showDebug(bool enabled) { node_->setDebugDisplayEnabled(enabled); }
	void showBoundingBox(bool enabled) { node_->showBoundingBox(enabled); }

	void attach(Ogre::MovableObject* o) { node_->attachObject(o); }
};

#endif // !__TRANSFORM_H__