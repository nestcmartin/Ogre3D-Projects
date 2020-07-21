#include "TestApplication.h"
#include "OgreShaderGenerator.h"

#include "InputSystem/InputManager.h"
#include "RenderSystem/Renderer.h"
#include "RenderSystem/Window.h"

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

void TestApplication::setup()
{
    // do not forget to call the base first
    Application::setup();

    // register for input events
    InputManager::AddInputListener(this);

    // get a pointer to the already created root
    Ogre::Root* root = Renderer::GetRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    Renderer::GetWindow()->getRenderWindow()->addViewport(cam);

    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}

