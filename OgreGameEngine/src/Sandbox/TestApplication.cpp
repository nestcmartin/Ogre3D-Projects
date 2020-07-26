#include "TestApplication.h"
#include "GraphicsEngine/Graphics.h"
#include "Core/InputSystem/InputManager.h"

//enum ShaderParam { SP_SHININESS = 1, SP_DIFFUSE, SP_SPECULAR };

TestApplication::TestApplication() : 
    Application("Ogre3D Test")
{
    Graphics::CreateViewport();

    Ogre::SceneManager* scnMgr = Graphics::getSceneManager();

    Ogre::Light* light = scnMgr->createLight();
    Ogre::SceneNode* mLightPivot = scnMgr->getRootSceneNode()->createChildSceneNode();
    mLightPivot->createChildSceneNode(Ogre::Vector3(20, 40, 50))->attachObject(light);



    //Ogre::Entity* ent = scnMgr->createEntity("Head", "ogrehead.mesh");
    //ent->setMaterialName("Examples/CelShading");
    //scnMgr->getRootSceneNode()->attachObject(ent);
    //Ogre::SubEntity* sub;
    //sub = ent->getSubEntity(0);    // eyes
    //sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(35, 0, 0, 0));
    //sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(0.9, 1, 0.3, 1));
    //sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 0.6, 0.6, 1));
    //sub = ent->getSubEntity(1);    // skin
    //sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(10, 0, 0, 0));
    //sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(0, 0.5, 0, 1));
    //sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(0.3, 0.5, 0.3, 1));
    //sub = ent->getSubEntity(2);    // earring
    //sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(25, 0, 0, 0));
    //sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(1, 1, 0, 1));
    //sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 1, 0.7, 1));
    //sub = ent->getSubEntity(3);    // teeth
    //sub->setCustomParameter(SP_SHININESS, Ogre::Vector4(20, 0, 0, 0));
    //sub->setCustomParameter(SP_DIFFUSE, Ogre::Vector4(1, 1, 0.7, 1));
    //sub->setCustomParameter(SP_SPECULAR, Ogre::Vector4(1, 1, 1, 1));
}

bool TestApplication::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == InputKey::ESCAPE)
    {
        Graphics::StopRendering();
    }
    return true;
}