#ifndef __BASIC_APPLICATION_H__
#define __BASIC_APPLICATION_H__

#include "Core/Application.h"

class Camera;

class BasicApplication : public Application
{
private:
	Camera* cam_;
	bool advancedScene_;
	int currentShadowType_;

public:
	BasicApplication();

	bool keyPressed(const KeyboardEvent& evt) override;

protected:
	void createBasicScene();
};

#endif // !__BASIC_APPLICATION_H__

