#include "SceneManager.h"
#include "GraphicsEngine/Graphics.h"
#include "Camera.h"

SceneManager::SceneManager()
{
	sceneManager_ = Graphics::GetRoot()->createSceneManager();
}

SceneManager::~SceneManager()
{
}

void SceneManager::setAmbientLighting(float r, float g, float b)
{
	sceneManager_->setAmbientLight(Ogre::ColourValue(r, g, b));
}

void SceneManager::enableFog(FogType type, float r, float g, float b, float density, float linearStart, float linearEnd)
{
	sceneManager_->setFog(static_cast<Ogre::FogMode>(type), Ogre::ColourValue(r, g, b), density, linearStart, linearEnd);
}

void SceneManager::disableFog()
{
	sceneManager_->setFog(Ogre::FogMode::FOG_NONE);
}

void SceneManager::enableShadows(ShadowType type, float r, float g, float b, float maxDistance)
{
	sceneManager_->setShadowTechnique(static_cast<Ogre::ShadowTechnique>(type));
	sceneManager_->setShadowColour(Ogre::ColourValue(r, g, b));
	sceneManager_->setShadowTextureSize(1024);
	sceneManager_->setShadowTextureCount(1);
	sceneManager_->setShadowDirLightTextureOffset(0);
	sceneManager_->setShadowFarDistance(maxDistance);
	sceneManager_->setShadowCameraSetup(Ogre::FocusedShadowCameraSetup::create());
}

void SceneManager::disableShadows()
{
	sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_NONE);
}

void SceneManager::clearScene()
{
	sceneManager_->destroyAllCameras();
	sceneManager_->clearScene();
}
