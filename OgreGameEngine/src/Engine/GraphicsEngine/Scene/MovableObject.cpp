#include "MovableObject.h"
#include "SceneManager.h"
#include "OgreSceneManager.h"

MovableObject::MovableObject(const Ogre::Vector3& translation, const Ogre::Quaternion& rotation) :
	node_(nullptr)
{
	node_ = SceneManager::Instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(translation, rotation);
}

MovableObject::MovableObject(MovableObject* parent, const Ogre::Vector3& translation, const Ogre::Quaternion& rotation) :
	node_(nullptr)
{
	node_ = parent->node_->createChildSceneNode(translation, rotation);
}