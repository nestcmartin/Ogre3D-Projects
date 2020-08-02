#include "Trail.h"
#include "SceneManager.h"
#include "OgreSceneManager.h"

Trail::Trail(int chains, int maxElems, float length, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(translate, rotate)
{
    Ogre::NameValuePairList params;
    Ogre::MovableObject* trail = SceneManager::Instance()->getSceneManager()->createMovableObject("RibbonTrail", &params);
    trail_ = static_cast<Ogre::RibbonTrail*>(trail);
    trail_->setNumberOfChains(chains);
    trail_->setMaxChainElements(maxElems);
    trail_->setTrailLength(length);
    trail_->setVisible(false);

    node_->attachObject(trail_);
}

Trail::Trail(int chains, int maxElems, float length, MovableObject* parent, const Ogre::Vector3& translate, const Ogre::Quaternion& rotate) :
	MovableObject(parent, translate, rotate)
{
    Ogre::NameValuePairList params;
    Ogre::MovableObject* trail = SceneManager::Instance()->getSceneManager()->createMovableObject("RibbonTrail", &params);
    trail_ = static_cast<Ogre::RibbonTrail*>(trail);
    trail_->setNumberOfChains(chains);
    trail_->setMaxChainElements(maxElems);
    trail_->setTrailLength(length);
    trail_->setVisible(false);

    node_->attachObject(trail_);
}

void Trail::setInitialColour(float r, float g, float b)
{
    for (size_t i = 0; i < trail_->getNumberOfChains(); i++)
    {
        trail_->setInitialColour(i, r, g, b);
    }
}

void Trail::setColourChange(float r, float g, float b, float a)
{
    for (size_t i = 0; i < trail_->getNumberOfChains(); i++)
    {
        trail_->setColourChange(i, r, g, b, a);
    }
}

void Trail::setInitialWidth(float w)
{
    for (size_t i = 0; i < trail_->getNumberOfChains(); i++)
    {
        trail_->setInitialWidth(i, w);
    }
}

void Trail::setWidthChange(float w)
{
    for (size_t i = 0; i < trail_->getNumberOfChains(); i++)
    {
        trail_->setWidthChange(i, w);
    }
}
