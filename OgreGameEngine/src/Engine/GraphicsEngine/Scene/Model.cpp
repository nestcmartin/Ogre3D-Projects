#include "Model.h"
#include "SceneManager.h"

Model::Model(const Ogre::String& name, const Ogre::String& mesh, const Vec3& translate, const Quat& rotate) :
	MovableObject(translate, rotate), entity_(nullptr)
{
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}

Model::Model(const Ogre::String& name, const Ogre::String& mesh, MovableObject* parent, const Vec3& translate, const Quat& rotate) :
	MovableObject(parent, translate, rotate), entity_(nullptr)
{
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}

Model::Model(const Ogre::String& name, const Ogre::String& mesh, const Vec3& normal, const Vec3& up, float width, float height, int xseg, int yseg, float utile, float vtile)
{
	if (!Ogre::MeshManager::getSingleton().getByName(mesh))
	{
		Ogre::Plane plane(V3(normal), 0);
		Ogre::MeshManager::getSingleton().createPlane(mesh, Ogre::RGN_DEFAULT, plane, width, height, xseg, yseg, true, 1, utile, vtile, V3(up));
	}
	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}