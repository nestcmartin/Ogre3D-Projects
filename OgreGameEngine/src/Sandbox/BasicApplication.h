#ifndef __BASIC_APPLICATION_H__
#define __BASIC_APPLICATION_H__

#include "Core/Application.h"
#include "ThirdPersonCharacterController.h"
#include "FirstPersonCharacterController.h"

class Camera;
class BasicApplication : public Application
{
private:
	Camera* camera_;
	ThirdPersonCharacterController* sinbad_;
	FirstPersonCharacterController* fps_;

public:
	BasicApplication();
	virtual ~BasicApplication();

	void run() override;
	bool keyPressed(const KeyboardEvent& evt) override;

protected:
	void createBasicScene();
	void createAdvancedScene();
	void createInputScene();
	void createFPSScene();

	void clearScene();
};

#endif // !__BASIC_APPLICATION_H__