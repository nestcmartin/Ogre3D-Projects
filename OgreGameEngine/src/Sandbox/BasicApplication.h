#ifndef __BASIC_APPLICATION_H__
#define __BASIC_APPLICATION_H__

#include "OgreTerrain.h"
#include "Core/Application.h"
#include "Core/LowLevel/Vec3.h"

class BasicApplication : public Application
{
private:
	bool advancedScene_;
	int currentShadowType_;

	Vec3 terrainPos_;
	Ogre::TerrainGlobalOptions terrainOptions_;

public:
	BasicApplication();

	bool keyPressed(const KeyboardEvent& evt) override;

protected:
	void createBasicScene();
	void createAdvancedScene();
	void createTerrainScene();
};

#endif // !__BASIC_APPLICATION_H__

