#ifndef __TEST_APP_H__
#define __TEST_APP_H__

#include "Core/ApplicationContext.h"
#include "InputSystem/InputListener.h"

class TestApp : public ApplicationContext, public InputListener
{
public:
    TestApp();

    void setup() override;
    bool keyPressed(const KeyboardEvent& evt) override;
};

#endif // !__TEST_APP_H__