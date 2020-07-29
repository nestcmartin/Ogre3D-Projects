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

void SceneManager::createBasicScene()
{
	
}

void SceneManager::createAdvancedScene()
{
	//clearScene();

	//// Basic Tutorial 2 -----------------------------------------------------------------------
	//Ogre::Camera* myCam = addCamera("MainCamera", 200, 300, 400);
	//getSceneNode("Camera_MainCamera")->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);

	//Ogre::Viewport* vp = myCam->getViewport();
	//myCam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	//Ogre::Entity* ninjaEntity = addRenderObject("Ninja", "ninja.mesh");
	//ninjaEntity->setCastShadows(true);

	//if (!Ogre::MeshManager::getSingleton().getByName("ground"))
	//{
	//	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	//	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::RGN_DEFAULT,
	//		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	//}

	//Ogre::Entity* groundEntity = addRenderObject("Ground", "ground");
	//groundEntity->setCastShadows(false);
	//groundEntity->setMaterialName("Examples/Rockwall");

	//setAmbientLighting(0, 0, 0);
	//enableShadows(CPU_MODULATIVE);

	//Ogre::Light* spotLight = addLight("SpotLight", 200, 200, 0);
	//spotLight->setDiffuseColour(0, 0, 1.0);
	//spotLight->setSpecularColour(0, 0, 1.0);
	//spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	//spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
	//getSceneNode("Light_SpotLight")->setDirection(-1, -1, 0);

	//Ogre::Light* directionalLight = addLight("DirectionalLight", 200, 200, 0);
	//directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	//directionalLight->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0));
	//directionalLight->setSpecularColour(Ogre::ColourValue(0.4, 0, 0));
	//getSceneNode("Light_DirectionalLight")->setDirection(0, -1, 1);

	//Ogre::Light* pointLight = addLight("PointLight", 0, 150, 250);
	//pointLight->setType(Ogre::Light::LT_POINT);
	//pointLight->setDiffuseColour(0.3, 0.3, 0.3);
	//pointLight->setSpecularColour(0.3, 0.3, 0.3);
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

Ogre::SceneNode* SceneManager::addSceneNode(const char* name, Ogre::SceneNode* parent)
{
	if (sceneManager_->hasSceneNode(name)) return getSceneNode(name);

	Ogre::SceneNode* node = nullptr;
	if (!parent) node = sceneManager_->getRootSceneNode()->createChildSceneNode(name);
	else node = parent->createChildSceneNode(name);

	return node;
}

Ogre::SceneNode* SceneManager::getSceneNode(const char* name)
{
	if (name == "") return sceneManager_->getRootSceneNode();
	return sceneManager_->getSceneNode(name);
}

Ogre::Camera* SceneManager::getCamera(const char* name)
{
	return sceneManager_->getCamera(name);
}

Ogre::Light* SceneManager::addLight(const char* name, float x, float y, float z, Ogre::SceneNode* parent)
{
	if (sceneManager_->hasLight(name)) return getLight(name);

	Ogre::Light* light = sceneManager_->createLight(name);

	Ogre::String lightNodeName = "Light_";
	lightNodeName += name;
	Ogre::SceneNode* lightNode = addSceneNode(lightNodeName.c_str(), parent);
	lightNode->setPosition(x, y, z);
	lightNode->attachObject(light);

	return light;
}

Ogre::Light* SceneManager::getLight(const char* name)
{
	return sceneManager_->getLight(name);
}

Ogre::Entity* SceneManager::addRenderObject(const char* name, const char* mesh, float x, float y, float z, Ogre::SceneNode* parent)
{
	if (sceneManager_->hasEntity(name)) return getRenderObject(name);

	Ogre::Entity* entity = sceneManager_->createEntity(name, mesh);

	Ogre::String entityNodeName = "Entity_";
	entityNodeName += name;
	Ogre::SceneNode* entityNode = addSceneNode(entityNodeName.c_str(), parent);
	entityNode->setPosition(x, y, z);
	entityNode->attachObject(entity);

	return entity;
}

Ogre::Entity* SceneManager::getRenderObject(const char* name)
{
	return sceneManager_->getEntity(name);
}
