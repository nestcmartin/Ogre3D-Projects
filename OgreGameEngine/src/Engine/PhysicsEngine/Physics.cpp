#include "Physics.h"
#include "PxPhysicsAPI.h"

static physx::PxDefaultErrorCallback defaultErrorCallback;
static physx::PxDefaultAllocator defaultAllocatorCallback;

physx::PxFoundation* Physics::foundation = nullptr;
physx::PxPhysics* Physics::physics = nullptr;

void Physics::Init()
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true, nullptr);
}

void Physics::Release()
{
	if (physics)
	{
		physics->release();
		foundation->release();
	}
}
