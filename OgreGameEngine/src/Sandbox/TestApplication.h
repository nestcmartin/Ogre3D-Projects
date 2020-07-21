#ifndef __TEST_APPLICATION_H__
#define __TEST_APPLICATION_H__

#include "Core/Application.h"
#include "InputSystem/InputListener.h"

class TestApplication : public Application, public InputListener
{
public:
	TestApplication();

	void setup() override;
	bool keyPressed(const KeyboardEvent& evt) override;
};

#endif // !__TEST_APPLICATION_H__
