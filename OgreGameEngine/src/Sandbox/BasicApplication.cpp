#include "BasicApplication.h"

#include "Core/Clock.h"
#include "Core/InputSystem/InputManager.h"
#include "GraphicsEngine/Graphics.h"
#include "GraphicsEngine/Scene/Light.h"
#include "GraphicsEngine/Scene/Model.h"
#include "GraphicsEngine/Scene/Plane.h"
#include "GraphicsEngine/Scene/Camera.h"
#include "GraphicsEngine/Scene/SceneManager.h"
#include "GraphicsEngine/OverlaySystem/OverlayManager.h"

BasicApplication::BasicApplication() :
	Application("Basic Application"),
	sinbad_(nullptr),
	camera_(nullptr),
	fps_(nullptr)
{
	createFPSScene();
	OverlayManager::Instance()->addWidget(WidgetType::FPS_COUNTER, "FPS", true);
}

BasicApplication::~BasicApplication()
{
	clearScene();
}

void BasicApplication::run()
{
	float dt = clock_->getDeltaTime();

	while (Graphics::IsRendering())
	{
		clock_->startTimer();

		pollEvents();
		if (sinbad_) sinbad_->update(dt);
		if (fps_) fps_->update(dt);
		Graphics::Update(dt);

		clock_->endTimer();

		dt = clock_->getDeltaTime();
	}
}

bool BasicApplication::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == InputKey::ESCAPE)
	{
		Graphics::StopRendering();
		return true;
	}
	return false;
}

void BasicApplication::createBasicScene()
{
	SceneManager::Instance()->setAmbientLighting(0.5, 0.5, 0.5);
	
	camera_ = new Camera("MainCamera");
	camera_->setViewportColor(0.4, 0.0, 0.6);
	camera_->setPosition(Ogre::Vector3(0, 47, 222));
	
	Model* ogreHead1 = new Model("OgreHead1", "ogrehead.mesh", Ogre::Vector3(0, 0, 0));
	Model* ogreHead2 = new Model("OgreHead2", "ogrehead.mesh", ogreHead1, Ogre::Vector3(84, 48, 0));
	ogreHead1->translate(0, -10, 0);
	Model* ogreHead3 = new Model("OgreHead3", "ogrehead.mesh", Ogre::Vector3(0, 104, 0));
	ogreHead3->setScale(2, 1.2, 1);
	Model* ogreHead4 = new Model("OgreHead4", "ogrehead.mesh", Ogre::Vector3(-84, 48, 0));
	ogreHead4->roll(-90);

	ogreHead1->setMaterialName("Examples/CelShading");
	ogreHead1->setCustomProperty(0, SP_SHININESS, 35, 0, 0, 0);
	ogreHead1->setCustomProperty(0, SP_DIFFUSE, 0.9, 0, 0, 1);
	ogreHead1->setCustomProperty(0, SP_SPECULAR, 1, 0.6, 0.6, 1);
	ogreHead1->setCustomProperty(1, SP_SHININESS, 10, 0, 0, 0);
	ogreHead1->setCustomProperty(1, SP_DIFFUSE, 0, 0.5, 0, 1);
	ogreHead1->setCustomProperty(1, SP_SPECULAR, 0.3, 0.5, 0.3, 1);
	ogreHead1->setCustomProperty(2, SP_SHININESS, 25, 0, 0, 0);
	ogreHead1->setCustomProperty(2, SP_DIFFUSE, 1, 1, 0, 1);
	ogreHead1->setCustomProperty(2, SP_SPECULAR, 1, 1, 0.7, 1);
	ogreHead1->setCustomProperty(3, SP_SHININESS, 20, 0, 0, 0);
	ogreHead1->setCustomProperty(3, SP_DIFFUSE, 1, 1, 0.7, 1);
	ogreHead1->setCustomProperty(3, SP_SPECULAR, 1, 1, 1, 1);

	Light* light = new Light("MainLight", LightType::POINT, Ogre::Vector3(20, 80, 50));
}

void BasicApplication::createAdvancedScene()
{
	SceneManager::Instance()->setAmbientLighting(0, 0, 0);
	SceneManager::Instance()->enableShadows(ShadowType::CPU_ADDITIVE);

	camera_ = new Camera("Main Camera", Ogre::Vector3(200, 300, 400));
	camera_->setViewportColor(0, 0, 0);
	camera_->lookAt(Ogre::Vector3::ZERO, TransformSpace::WORLD);

	Model* ninja = new Model("Ninja", "ninja.mesh", Ogre::Vector3::ZERO);
	ninja->setCastShadows(true);

	Plane* ground = new Plane("Floor", "floor", Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z, 1500, 1500, 20, 20, 5, 5);
	ground->setMaterialName("Examples/Rockwall");
	ground->setCastShadows(false);

	Light* spotLight = new Light("SpotLight", LightType::SPOT, Ogre::Vector3(200, 200, 0));
	spotLight->setDiffuseColour(0, 0, 1.0);
	spotLight->setSpecularColour(0, 0, 1.0);
	spotLight->setSpotlightRange(35, 50);
	spotLight->setDirection(-1, -1, 0);

	Light* directionalLight = new Light("DirectionalLight", LightType::DIRECTIONAL, Ogre::Vector3(200, 200, 0));
	directionalLight->setDiffuseColour(0.4, 0, 0);
	directionalLight->setSpecularColour(0.4, 0, 0);
	directionalLight->setDirection(0, -1, 1);

	Light* pointLight = new Light("PointLight", LightType::POINT, Ogre::Vector3(0, 150, 250));
	pointLight->setDiffuseColour(0.3, 0.3, 0.3);
	pointLight->setSpecularColour(0.3, 0.3, 0.3);
}

void BasicApplication::createInputScene()
{
	SceneManager::Instance()->setAmbientLighting(0.3, 0.3, 0.3);
	SceneManager::Instance()->enableShadows(ShadowType::GPU_ADDITIVE);
	SceneManager::Instance()->enableFog(FogType::LINEAR, 1, 1, 0.8, 0, 15, 100);

	Light* light = new Light("MainLight", LightType::POINT, Ogre::Vector3(-10, 40, 20));
	light->setSpecularColour(1, 1, 1);

	camera_ = new Camera("Main Camera", Ogre::Vector3::ZERO);
	camera_->setViewportColor(1, 1, 0.8);

	Plane* floor = new Plane("Floor", "floor", Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z, 100, 100, 10, 10, 10, 10);
	floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);

	sinbad_ = new ThirdPersonCharacterController(camera_);
}

void BasicApplication::createFPSScene()
{
	SceneManager::Instance()->setAmbientLighting(0.3, 0.3, 0.3);
	SceneManager::Instance()->enableShadows(ShadowType::GPU_ADDITIVE);
	SceneManager::Instance()->enableFog(FogType::LINEAR, 1, 1, 0.8, 0, 15, 100);

	Light* light = new Light("MainLight", LightType::POINT, Ogre::Vector3(-10, 40, 20));
	light->setSpecularColour(1, 1, 1);

	camera_ = new Camera("Main Camera", Ogre::Vector3::ZERO);
	camera_->setViewportColor(1, 1, 0.8);

	Plane* floor = new Plane("Floor", "floor", Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z, 100, 100, 10, 10, 10, 10);
	floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);

	fps_ = new FirstPersonCharacterController(camera_);
}

void BasicApplication::clearScene()
{
	SceneManager::Instance()->clearScene();

	if (fps_)
	{
		delete fps_;
		fps_ = nullptr;
	}

	if (sinbad_)
	{
		delete sinbad_;
		sinbad_ = nullptr;
	}

	if (camera_)
	{
		delete camera_;
		camera_ = nullptr;
	}
}
