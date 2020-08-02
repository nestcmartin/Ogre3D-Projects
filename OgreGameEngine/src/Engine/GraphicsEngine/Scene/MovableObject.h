#ifndef __MOVABLE_OBJECT_H__
#define __MOVABLE_OBJECT_H__

#include "Ogre.h"

enum TransformSpace { LOCAL = 0, PARENT = 1, WORLD = 2 };

class MovableObject
{
protected:
	Ogre::SceneNode* node_;

public:
	MovableObject() : node_(nullptr) {}
	MovableObject(const Ogre::Vector3& translate, const Ogre::Quaternion& rotate);
	MovableObject(MovableObject* parent, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate);
	virtual ~MovableObject() {}

	virtual Ogre::MovableObject* getOgreObject() { return nullptr; }

	const Ogre::Vector3& getPosition() const { return node_->getPosition(); }
	const Ogre::Quaternion& getRotation() const { return node_->getOrientation(); }
	const Ogre::Vector3& getScale() const { return node_->getScale(); }
	void setPosition(const Ogre::Vector3& p) { node_->setPosition(p); }
	void setPosition(float x, float y, float z) { node_->setPosition(x, y, z); }
	void setRotation(const Ogre::Quaternion& q) { node_->setOrientation(q); }
	void setRotation(float w, float x, float y, float z) { node_->setOrientation(w, x, y, z); }
	void setScale(const Ogre::Vector3& scale) { node_->setScale(scale); }
	void setScale(float x, float y, float z) { node_->setScale(x, y, z); }

	const Ogre::Vector3& getDerivedPosition() const { return node_->_getDerivedPosition(); }
	const Ogre::Quaternion& getDerivedOrientation() const { return node_->_getDerivedOrientation(); }
	const Ogre::Vector3& getDerivedScale() const { return node_->_getDerivedScale(); }

	void translate(const Ogre::Vector3& d, TransformSpace ts = TransformSpace::PARENT) { node_->translate(d, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void translate(float x, float y, float z, TransformSpace ts = TransformSpace::PARENT) { node_->translate(x, y, z, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void rotate(const Ogre::Quaternion& rot, TransformSpace ts = TransformSpace::LOCAL) { node_->rotate(rot, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void rotate(const Ogre::Vector3& axis, float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->rotate(axis, Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void yaw(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->yaw(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void pitch(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->pitch(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void roll(float degrees, TransformSpace ts = TransformSpace::LOCAL) { node_->roll(Ogre::Radian(Ogre::Degree(degrees)), static_cast<Ogre::Node::TransformSpace>(ts)); }
	void setFixedYawAxis(bool useFixed, const Ogre::Vector3& fixedAxis = Ogre::Vector3::UNIT_Y) { node_->setFixedYawAxis(useFixed, fixedAxis); }
	void setDirection(float x, float y, float z, TransformSpace ts = TransformSpace::LOCAL) { node_->setDirection(x, y, z, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void setDirection(const Ogre::Vector3& dir, TransformSpace ts = TransformSpace::LOCAL) { node_->setDirection(dir, static_cast<Ogre::Node::TransformSpace>(ts)); }
	void lookAt(const Ogre::Vector3& target, TransformSpace ts = TransformSpace::LOCAL) { node_->lookAt(target, static_cast<Ogre::Node::TransformSpace>(ts)); }

	float distance(MovableObject* obj) { return getDerivedPosition().distance(obj->getDerivedPosition()); }

	void setVisible(bool visibility) { node_->setVisible(visibility); }
	void showDebug(bool enabled) { node_->setDebugDisplayEnabled(enabled); }
	void showBoundingBox(bool enabled) { node_->showBoundingBox(enabled); }

	Ogre::SceneNode* getParent() { return node_->getParentSceneNode(); }
	const Ogre::Node::ChildNodeMap& getChildren() { return node_->getChildren(); }
	void addChild(MovableObject* child) { node_->addChild(child->node_); }
};

#endif // !__MOVABLE_OBJECT_H__