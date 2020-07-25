#ifndef __TEST_APPLICATION_H__
#define __TEST_APPLICATION_H__

#include "Core/Application.h"

class TestApplication : public Application
{
public:
	TestApplication();

	bool keyPressed(const KeyboardEvent& evt) override;
};

#endif // !__TEST_APPLICATION_H__
