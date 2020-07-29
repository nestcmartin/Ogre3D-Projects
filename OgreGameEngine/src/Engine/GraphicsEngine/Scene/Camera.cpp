#include "Camera.h"
#include "SceneManager.h"
#include "GraphicsEngine/Graphics.h"

Camera::Camera() :
	MovableObject("MainCameraNode", new Transform(Vec3(0, 0, 140)))
{
	transform_->lookAt(Ogre::Vector3(0, 0, -1), TransformSpace::PARENT);
	camera_ = SceneManager::Instance()->getSceneManager()->createCamera("MainCamera");
	camera_->setAutoAspectRatio(true);

	if (!viewport_) viewport_ = Graphics::GetWindow()->getRenderWindow()->addViewport(camera_);
	else viewport_->setCamera(camera_);

	attach();
}

Camera::Camera(const char* name, Transform* t) :
	MovableObject(name, t)
{
}

void Camera::setBackgroundColor(float r, float g, float b)
{
	viewport_->setBackgroundColour(Ogre::ColourValue(r, g, b));
}

void Camera::setNearClipDistance(float val)
{
	camera_->setNearClipDistance(val);
}

void Camera::setFarClipDistance(float val)
{
	camera_->setFarClipDistance(val);
}
