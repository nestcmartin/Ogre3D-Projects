#include "BasicApplication.h"

#include "Core/InputSystem/InputManager.h"

#include "GraphicsEngine/Graphics.h"
#include "GraphicsEngine/Scene/Camera.h"
#include "GraphicsEngine/Scene/SceneManager.h"
#include "GraphicsEngine/OverlaySystem/OverlayManager.h"

BasicApplication::BasicApplication() :
	Application("Basic Application"),
	advancedScene_(false),
	currentShadowType_(0)
{
	createBasicScene();
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
	//		SceneManager::Instance()->createBasicScene();
	//		advancedScene_ = false;
	//		currentShadowType_ = 0;
	//	}
	//	else
	//	{
	//		SceneManager::Instance()->createAdvancedScene();
	//		advancedScene_ = true;
	//	}
	//}
	//else if (evt.keysym.sym == InputKey::RETURN)
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

	// Basic Tutorial 1 -----------------------------------------------------------------------
	SceneManager::Instance()->setAmbientLighting(0.5, 0.5, 0.5);
	SceneManager::Instance()->addLight("MainLight", 20, 80, 50);
	
	cam_ = new Camera();
	cam_->setBackgroundColor(0.4, 0.0, 0.6);
	SceneManager::Instance()->addRenderObject("OgreHead", "ogrehead.mesh");

	cam_->transform()->setPosition(Vec3(0, 47, 222));
	
	SceneManager::Instance()->addRenderObject("OgreHead2", "ogrehead.mesh", 84, 48, 0, SceneManager::Instance()->getSceneNode("Entity_OgreHead"));
	SceneManager::Instance()->getSceneNode("Entity_OgreHead")->translate(0, -10, 0);

	SceneManager::Instance()->addRenderObject("OgreHead3", "ogrehead.mesh", 0, 104, 0);
	SceneManager::Instance()->getSceneNode("Entity_OgreHead3")->setScale(2, 1.2, 1);

	SceneManager::Instance()->addRenderObject("OgreHead4", "ogrehead.mesh", -84, 48, 0);
	SceneManager::Instance()->getSceneNode("Entity_OgreHead4")->roll(Ogre::Degree(-90));

	// Cel Shading ----------------------------------------------------------------------------
	enum ShaderParam { SP_SHININESS = 1, SP_DIFFUSE, SP_SPECULAR };

	Ogre::Entity* ent = SceneManager::Instance()->getRenderObject("OgreHead");
	ent->setMaterialName("Examples/CelShading");

	Ogre::SubEntity* sub;
	sub = ent->getSubEntity(0);    // eyes
	sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(35, 0, 0, 0));
	sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(0.9, 0, 0, 1));
	sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 0.6, 0.6, 1));
	sub = ent->getSubEntity(1);    // skin
	sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(10, 0, 0, 0));
	sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(0, 0.5, 0, 1));
	sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(0.3, 0.5, 0.3, 1));
	sub = ent->getSubEntity(2);    // earring
	sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(25, 0, 0, 0));
	sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(1, 1, 0, 1));
	sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 1, 0.7, 1));
	sub = ent->getSubEntity(3);    // teeth
	sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(20, 0, 0, 0));
	sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(1, 1, 0.7, 1));
	sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 1, 1, 1));
}
