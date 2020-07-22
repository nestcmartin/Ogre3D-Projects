#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "PxPhysicsAPI.h"

class Physics
{
private:
	static physx::PxFoundation* foundation;
	static physx::PxPhysics* physics;

public:
	static void Init();
	static void Release();
};

#endif // !__PHYSICS_H__
