#include "Transform.h"
#include "SceneManager.h"
#include "OgreSceneManager.h"

Transform::Transform(const Vec3& pos, const Quat& rot) :
	name_(nullptr),
	node_(nullptr)
{
	node_ = SceneManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	setPosition(pos);
	setRotation(rot);
}

Transform::Transform(const char* name, const Vec3& pos, const Quat& rot) :
	name_(name),
	node_(nullptr)
{
	node_ = SceneManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(name);
	setPosition(pos);
	setRotation(rot);
}

Transform* Transform::addChild(const char* name, const Vec3& pos, const Quat& rot)
{
	Transform* child = new Transform(name, node_->createChildSceneNode(name));
	child->translate(pos);
	child->rotate(rot);
	return child;
}
