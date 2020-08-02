#include "Model.h"
#include "SceneManager.h"

Model::Model(const Ogre::String& name, const Ogre::String& mesh) :
	MovableObject(), entity_(nullptr)
{
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
}

Model::Model(const Ogre::String& name, const Ogre::String& mesh, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(translate, rotate), entity_(nullptr)
{
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}

Model::Model(const Ogre::String& name, const Ogre::String& mesh, MovableObject* parent, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(parent, translate, rotate), entity_(nullptr)
{
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}