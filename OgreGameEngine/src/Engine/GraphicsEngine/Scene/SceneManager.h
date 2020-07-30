#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// TODO:
// class Vec2, Vec3, Quat
// class Transform
// class Camera
// class Light
// class RenderObject

namespace Ogre {
	class SceneManager;
	class SceneNode;
	class Camera;
	class Light;
	class Entity;
}

#include "Core/LowLevel/Singleton.h"

enum ShadowType { 
	CPU_MODULATIVE,	CPU_ADDITIVE,
	GPU_MODULATIVE, GPU_ADDITIVE,
	LITE_MODULATIVE, LITE_ADDITIVE,
	_shadowTypeCount
};

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;

private:
	Ogre::SceneManager* sceneManager_;

public:
	virtual ~SceneManager();

	void createBasicScene();
	void createAdvancedScene();
	void setAmbientLighting(float r, float g, float b);

	void enableShadows(ShadowType type = CPU_ADDITIVE);
	void disableShadows();
	void clearScene();

	Ogre::SceneNode* addSceneNode(const char* name, Ogre::SceneNode* parent = nullptr);
	Ogre::SceneNode* getSceneNode(const char* name = "");

	Ogre::Light* addLight(const char* name, float x = 0, float y = 0, float z = 0, Ogre::SceneNode* parent = nullptr);
	Ogre::Light* getLight(const char* name);

	Ogre::SceneManager* getSceneManager() { return sceneManager_; }

private:
	SceneManager();
};

#endif // !__SCENE_MANAGER_H__
