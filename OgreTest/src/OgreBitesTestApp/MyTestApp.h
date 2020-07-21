#ifndef __MY_TEST_APP_H__
#define __MY_TEST_APP_H__

#include "Ogre.h"
#include "OgreApplicationContext.h"

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    MyTestApp();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
};

#endif // !__MY_TEST_APP_H__