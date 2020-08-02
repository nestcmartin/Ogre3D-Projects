#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// TODO:
// class Vec2, Ogre::Vector3, Ogre::Quaternion
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

enum ShadowType : int { 
	CPU_ADDITIVE = 17, CPU_MODULATIVE = 18,
	GPU_ADDITIVE = 33, GPU_MODULATIVE = 34,
	LITE_ADDITIVE = 37, LITE_MODULATIVE = 38,
	_shadowTypeCount = 6
};

enum FogType { QUAD = 1, QUAD2 = 2, LINEAR = 3 };

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;

private:
	Ogre::SceneManager* sceneManager_;

public:
	virtual ~SceneManager();

	void setAmbientLighting(float r, float g, float b);
	void enableShadows(ShadowType type = CPU_ADDITIVE, float r = 0.5f, float g = 0.5f, float b = 0.5f, float maxDistance = 0);
	void enableFog(FogType type, float r, float g, float b, float density = 0.001f, float linearStart = 0.0f, float linearEnd = 1.0f);
	void disableShadows();
	void disableFog();
	void clearScene();

	Ogre::SceneManager* getSceneManager() { return sceneManager_; }

private:
	SceneManager();
};

#endif // !__SCENE_MANAGER_H__
