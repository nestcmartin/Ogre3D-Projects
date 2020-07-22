#include <iostream>
#include "Physics.h"

physx::PxFoundation* Physics::foundation = nullptr;
physx::PxPhysics* Physics::physics = nullptr;

void Physics::Init()
{
	static physx::PxDefaultErrorCallback defaultErrorCallback;
	static physx::PxDefaultAllocator defaultAllocatorCallback;

	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
	if (!foundation) std::cerr << "PxCreateFoundation failed!\n";

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true, nullptr);
	if (!physics) std::cerr << "PxCreatePhysics failed!\n";

}

void Physics::Release()
{
	if (physics)
	{
		physics->release();
		foundation->release();
	}
}
