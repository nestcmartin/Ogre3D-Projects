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

void SceneManager::enableShadows(ShadowType type)
{
	switch (type)
	{
	case CPU_MODULATIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
		break;
	case CPU_ADDITIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
		break;
	case GPU_MODULATIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);
		break;
	case GPU_ADDITIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE);
		break;
	case LITE_MODULATIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
		break;
	case LITE_ADDITIVE:
		sceneManager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
		break;
	}
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
