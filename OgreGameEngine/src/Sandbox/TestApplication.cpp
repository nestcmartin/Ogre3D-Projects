#include "TestApplication.h"
#include "OgreShaderGenerator.h"

#include "InputSystem/InputManager.h"
#include "RenderSystem/Renderer.h"
#include "RenderSystem/Window.h"
#include "Physics.h"

TestApplication::TestApplication() : 
    Application("Ogre3D_Test")
{
}

bool TestApplication::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == InputKey::ESCAPE)
    {
        Renderer::Stop();
    }
    return true;
}

//void TestApplication::setup()
//{
//    // do not forget to call the base first
//    Application::setup();
//
//    // register for input events
//    InputManager::AddInputListener(this);
//
//    // get a pointer to the already created root
//    Ogre::Root* root = Renderer::GetRoot();
//    Ogre::SceneManager* scnMgr = root->createSceneManager();
//
//    // register our scene with the RTSS
//    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
//    shadergen->addSceneManager(scnMgr);
//
//    // without light we would just get a black screen    
//    Ogre::Light* light = scnMgr->createLight("MainLight");
//    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//    lightNode->setPosition(0, 10, 15);
//    lightNode->attachObject(light);
//
//    // also need to tell where we are
//    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
//    camNode->setPosition(0, 0, 15);
//    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
//
//    // create the camera
//    Ogre::Camera* cam = scnMgr->createCamera("myCam");
//    cam->setNearClipDistance(5); // specific to this sample
//    cam->setAutoAspectRatio(true);
//    camNode->attachObject(cam);
//
//    // and tell it to render into the main window
//    Renderer::GetWindow()->getRenderWindow()->addViewport(cam);
//
//    // finally something to render
//    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
//    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
//    node->attachObject(ent);
//
//    Physics::Init();
//}

enum ShaderParam { SP_SHININESS = 1, SP_DIFFUSE, SP_SPECULAR };

void TestApplication::setup()
{
    // do not forget to call the base first
    Application::setup();
    
    Physics::Init();

    // register for input events
    InputManager::AddInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = Renderer::GetRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 150);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    Ogre::Viewport* mViewport = Renderer::GetWindow()->getRenderWindow()->addViewport(cam);

    // attach the light to a pivot node
    Ogre::SceneNode* mLightPivot = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create a basic point light with an offset
    Ogre::Light* light = scnMgr->createLight();
    mLightPivot->createChildSceneNode(Ogre::Vector3(20, 40, 50))->attachObject(light);

    // create our model, give it the shader material, and place it at the origin
    Ogre::Entity* ent = scnMgr->createEntity("Head", "ogrehead.mesh");
    ent->setMaterialName("Examples/CelShading");
    scnMgr->getRootSceneNode()->attachObject(ent);

    /* We set the same material for all parts of the head, but use custom shader parameters to set the
    colours for each part. See Examples-Advanced.material for how these are bound to GPU parameters. */

    Ogre::SubEntity* sub;

    sub = ent->getSubEntity(0);    // eyes
    sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(35, 0, 0, 0));
    sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(1, 0.3, 0.3, 1));
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

void TestApplication::shutdown()
{
    Physics::Release();

    Application::shutdown();
}

