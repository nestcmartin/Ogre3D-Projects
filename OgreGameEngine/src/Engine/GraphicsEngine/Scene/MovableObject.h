#ifndef __MOVABLE_OBJECT_H__
#define __MOVABLE_OBJECT_H__

#include "Transform.h"

class MovableObject
{
protected:
	Transform* transform_;

public:
	MovableObject(const char* name, Transform* t) : transform_(t) {}
	virtual ~MovableObject() {}

	virtual void attach() = 0;

	Transform* transform() { return transform_; }
};

#endif // !__MOVABLE_OBJECT_H__