#ifndef __MY_TEST_APP_H__
#define __MY_TEST_APP_H__

#include "Ogre.h"
#include "OgreInput.h"
#include "OgreApplicationContextSDL.h"

class MyTestApp : public OgreApplicationContextSDL, public InputListener
{
public:
    MyTestApp();
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};

#endif // !__MY_TEST_APP_H__