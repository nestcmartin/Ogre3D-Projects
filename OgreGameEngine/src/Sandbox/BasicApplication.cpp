
#include "OgreTerrainMaterialGeneratorA.h"

#include "BasicApplication.h"
#include "Core/InputSystem/InputManager.h"

#include "GraphicsEngine/Graphics.h"
#include "GraphicsEngine/Scene/Light.h"
#include "GraphicsEngine/Scene/Model.h"
#include "GraphicsEngine/Scene/Camera.h"
#include "GraphicsEngine/Scene/SceneManager.h"
#include "GraphicsEngine/OverlaySystem/OverlayManager.h"

BasicApplication::BasicApplication() :
	Application("Basic Application"),
	advancedScene_(true),
	currentShadowType_(0)
{
	createInputScene();
	OverlayManager::Instance()->addWidget(WidgetType::FPS_COUNTER, "FPS", true);
}

bool BasicApplication::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == InputKey::ESCAPE)
	{
		Graphics::StopRendering();
	}
	//else if (evt.keysym.sym == InputKey::SPACE)
	//{
	//	if (advancedScene_)
	//	{
	//		SceneManager::Instance()->disableShadows();
	//		createBasicScene();
	//		advancedScene_ = false;
	//		currentShadowType_ = 0;
	//	}
	//	else
	//	{
	//		createAdvancedScene();
	//		advancedScene_ = true;
	//	}
	//}
	//else if (evt.keysym.sym == InputKey::ENTER)
	//{
	//	if (advancedScene_)
	//	{
	//		currentShadowType_++;
	//		if (currentShadowType_ >= ShadowType::_shadowTypeCount) currentShadowType_ = 0;
	//		SceneManager::Instance()->enableShadows(ShadowType(currentShadowType_));
	//	}
	//}
	return true;
}

void BasicApplication::createBasicScene()
{
	SceneManager::Instance()->clearScene();
	SceneManager::Instance()->setAmbientLighting(0.5, 0.5, 0.5);
	
	Camera* camera = new Camera("MainCamera");
	camera->setViewportColor(0.4, 0.0, 0.6);
	camera->setPosition(Vec3(0, 47, 222));
	
	Model* ogreHead1 = new Model("OgreHead1", "ogrehead.mesh");
	Model* ogreHead2 = new Model("OgreHead2", "ogrehead.mesh", ogreHead1, Vec3(84, 48, 0));
	ogreHead1->translate(0, -10, 0);
	Model* ogreHead3 = new Model("OgreHead3", "ogrehead.mesh", Vec3(0, 104, 0));
	ogreHead3->setScale(2, 1.2, 1);
	Model* ogreHead4 = new Model("OgreHead4", "ogrehead.mesh", Vec3(-84, 48, 0));
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

	Light* light = new Light("MainLight", LightType::POINT, Vec3(20, 80, 50));
}

void BasicApplication::createAdvancedScene()
{
	SceneManager::Instance()->clearScene();
	SceneManager::Instance()->setAmbientLighting(0, 0, 0);
	SceneManager::Instance()->enableShadows(CPU_MODULATIVE);

	Camera* camera = new Camera("Main Camera", Vec3(200, 300, 400));
	camera->setViewportColor(0, 0, 0);
	camera->lookAt(Vec3::ZERO, TransformSpace::WORLD);

	Model* ninja = new Model("Ninja", "ninja.mesh");
	ninja->setCastShadows(true);

	Model* ground = new Model("Ground", "ground", Ogre::Vector3::UNIT_Y, Ogre::Vector3::UNIT_Z, 1500, 1500, 20, 20, 5, 5);
	ground->setMaterialName("Examples/Rockwall");
	ground->setCastShadows(false);

	Light* spotLight = new Light("SpotLight", LightType::SPOT, Vec3(200, 200, 0));
	spotLight->setDiffuseColour(0, 0, 1.0);
	spotLight->setSpecularColour(0, 0, 1.0);
	spotLight->setSpotlightRange(35, 50);
	spotLight->setDirection(-1, -1, 0);

	Light* directionalLight = new Light("DirectionalLight", LightType::DIRECTIONAL, Vec3(200, 200, 0));
	directionalLight->setDiffuseColour(0.4, 0, 0);
	directionalLight->setSpecularColour(0.4, 0, 0);
	directionalLight->setDirection(0, -1, 1);

	Light* pointLight = new Light("PointLight", LightType::POINT, Vec3(0, 150, 250));
	pointLight->setDiffuseColour(0.3, 0.3, 0.3);
	pointLight->setSpecularColour(0.3, 0.3, 0.3);
}

void BasicApplication::createInputScene()
{
	SceneManager::Instance()->clearScene();
	SceneManager::Instance()->setAmbientLighting(0.5, 0.5, 0.5);
}
