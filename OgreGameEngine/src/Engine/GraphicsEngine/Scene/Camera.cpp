#include "Camera.h"
#include "SceneManager.h"
#include "GraphicsEngine/Graphics.h"

Camera::Camera(const Ogre::String& name, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(translate, rotate)
{
	camera_ = SceneManager::Instance()->getSceneManager()->createCamera(name);

	if (Graphics::GetWindow()->getRenderWindow()->getNumViewports() == 0)
	{
		viewport_ = Graphics::GetWindow()->getRenderWindow()->addViewport(camera_);
	}
	else
	{
		viewport_ = Graphics::GetWindow()->getRenderWindow()->getViewport(0);
		viewport_->setCamera(camera_);
	}

	node_->attachObject(camera_);

	lookAt(Ogre::Vector3::NEGATIVE_UNIT_Z, TransformSpace::PARENT);
	setAutoAspectRatio(true);
	setNearClipDistance(5);
}

Camera::Camera(const Ogre::String& name, MovableObject* parent, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(parent, translate, rotate)
{
	camera_ = SceneManager::Instance()->getSceneManager()->createCamera(name);

	if (Graphics::GetWindow()->getRenderWindow()->getNumViewports() == 0)
	{
		viewport_ = Graphics::GetWindow()->getRenderWindow()->addViewport(camera_);
	}
	else
	{
		viewport_ = Graphics::GetWindow()->getRenderWindow()->getViewport(0);
		viewport_->setCamera(camera_);
	}

	node_->attachObject(camera_);

	lookAt(Ogre::Vector3::NEGATIVE_UNIT_Z, TransformSpace::PARENT);
	setAutoAspectRatio(true);
	setNearClipDistance(5);
}