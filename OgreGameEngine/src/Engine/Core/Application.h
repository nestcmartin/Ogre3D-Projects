#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Ogre.h"

class Window;

class Application : Ogre::FrameListener
{
protected:
	Window* window_;

public:
	explicit Application(const Ogre::String& name);
	virtual ~Application();

	bool frameStarted(const Ogre::FrameEvent& evt) override;
	bool frameRenderingQueued(const Ogre::FrameEvent& evt) override { return true; }
	bool frameEnded(const Ogre::FrameEvent& evt) override { return true; }

	virtual void setup() {}
	virtual void shutdown() {}

	void run();
	void pollEvents();
};

#endif // !__APPLICATION_H__
