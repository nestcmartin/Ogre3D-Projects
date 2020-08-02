#ifndef __TRAIL_H__
#define __TRAIL_H__

#include "MovableObject.h"

class Trail : public MovableObject
{
private:
	Ogre::RibbonTrail* trail_;

public:
	Trail(int chains, int maxElems, float length, const Ogre::Vector3& translate = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);
	Trail(int chains, int maxElems, float length, MovableObject* parent, const Ogre::Vector3& translate = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY);

	Ogre::MovableObject* getOgreObject() override { return trail_; }

	void setMaterialName(const Ogre::String& name) { trail_->setMaterialName(name); }
	void setInitialColour(size_t chain, float r, float g, float b) { trail_->setInitialColour(chain, r, g, b); }
	void setColourChange(size_t chain, float r, float g, float b, float a) { trail_->setColourChange(chain, r, g, b, a); }
	void setInitialWidth(size_t chain, float w) { trail_->setInitialWidth(chain, w); }
	void setWidthChange(size_t chain, float w) { trail_->setWidthChange(chain, w); }

	void setInitialColour(float r, float g, float b);
	void setColourChange(float r, float g, float b, float a);
	void setInitialWidth(float w);
	void setWidthChange(float w);

	void track(MovableObject* obj) { trail_->addNode(obj->getOgreObject()->getParentNode()); }
	void untrack(MovableObject* obj) { trail_->removeNode(obj->getOgreObject()->getParentNode()); }
};

#endif // !__TRAIL_H__