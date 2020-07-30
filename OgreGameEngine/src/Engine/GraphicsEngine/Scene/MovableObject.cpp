#include "MovableObject.h"
#include "SceneManager.h"
#include "OgreSceneManager.h"

MovableObject::MovableObject(const Vec3& translation, const Quat& rotation) :
	node_(nullptr)
{
	node_ = SceneManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(V3(translation), Q(rotation));
}

MovableObject::MovableObject(MovableObject* parent, const Vec3& translation, const Quat& rotation) :
	node_(nullptr)
{
	node_ = parent->node_->createChildSceneNode(V3(translation), Q(rotation));
}