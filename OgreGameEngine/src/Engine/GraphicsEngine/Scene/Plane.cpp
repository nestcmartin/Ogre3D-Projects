#include "Plane.h"
#include "SceneManager.h"

Plane::Plane(const Ogre::String& name, const Ogre::String& mesh, const Ogre::Vector3& normal, const Ogre::Vector3& up, float width, float height, int xseg, int yseg, float utile, float vtile) :
	MovableObject(Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY)
{
	Ogre::Plane plane(normal, 0);

	if (Ogre::MeshManager::getSingleton().getByName(mesh))
	{
		Ogre::MeshManager::getSingleton().remove(entity_->getMesh()->getName(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::MeshManager::getSingleton().createPlane(mesh, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, width, height, xseg, yseg, true, 1, utile, vtile, up);

	entity_ = SceneManager::Instance()->getSceneManager()->createEntity(name, mesh);
	node_->attachObject(entity_);
}

Plane::~Plane()
{
	Ogre::MeshManager::getSingleton().remove(entity_->getMesh()->getName(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
}