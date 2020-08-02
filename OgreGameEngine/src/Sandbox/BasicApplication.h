#ifndef __BASIC_APPLICATION_H__
#define __BASIC_APPLICATION_H__

#include "Core/Application.h"

class BasicApplication : public Application
{
private:
	bool advancedScene_;
	int currentShadowType_;

public:
	BasicApplication();

	bool keyPressed(const KeyboardEvent& evt) override;

protected:
	void createBasicScene();
	void createAdvancedScene();
	void createInputScene();
};

#endif // !__BASIC_APPLICATION_H__

