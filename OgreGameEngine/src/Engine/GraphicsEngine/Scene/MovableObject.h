#ifndef __MOVABLE_OBJECT_H__
#define __MOVABLE_OBJECT_H__

#include "OgreSceneNode.h"
#include "Core/LowLevel/Vec3.h"
#include "Core/LowLevel/Quat.h"

enum TransformSpace { LOCAL = 0, PARENT = 1, WORLD = 2 };

class MovableObject
{
protected:
	Ogre::SceneNode* node_;

public:
	MovableObject(const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	MovableObject(MovableObject* parent, const Vec3& translate = Vec3::ZERO, const Quat& rotate = Quat::IDENTITY);
	virtual ~MovableObject() {}

	const Vec3& getPosition() const { return node_->getPosition(); }
	const Quat& getRotation() const { return node_->getOrientation(); }
	const Vec3& getScale() const { return node_->getScale(); }
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
	void setFixedYawAxis(bool useFixed, const Vec3& fixedAxis = Vec3::UNIT_Y) { node_->setFixedYawAxis(useFixed, V3(fixedAxis)); }
	void setDirection(float x, float y, float z, TransformSpace ts = TransformSpace::LOCAL) { node_->setDirection(x, y, z, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void setDirection(const Vec3& dir, TransformSpace ts = TransformSpace::LOCAL) { node_->setDirection(V3(dir), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void lookAt(const Vec3& target, TransformSpace ts = TransformSpace::LOCAL) { node_->lookAt(V3(target), static_cast<Ogre::Node::TransformSpace>(ts)); }

	void setVisible(bool visibility) { node_->setVisible(visibility); }
	void showDebug(bool enabled) { node_->setDebugDisplayEnabled(enabled); }
	void showBoundingBox(bool enabled) { node_->showBoundingBox(enabled); }

	Ogre::SceneNode* getParent() { return node_->getParentSceneNode(); }
	const Ogre::Node::ChildNodeMap& getChildren() { return node_->getChildren(); }
	void addChild(MovableObject* child) { node_->addChild(child->node_); }
};

#endif // !__MOVABLE_OBJECT_H__