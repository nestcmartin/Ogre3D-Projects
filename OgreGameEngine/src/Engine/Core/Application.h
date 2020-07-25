#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "InputListener.h"

class Clock;
class Application : InputListener
{
protected:
	Clock* clock_;
	const char* name_;

public:
	explicit Application(const char* name);
	virtual ~Application();

	virtual void run();
	
	void pollEvents();
};

#endif // !__APPLICATION_H__