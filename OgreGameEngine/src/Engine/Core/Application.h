#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "InputListener.h"

class Application : InputListener
{
protected:
	const char* name_;

public:
	explicit Application(const char* name);
	virtual ~Application();

	virtual void run();
	
	void pollEvents();
};

#endif // !__APPLICATION_H__