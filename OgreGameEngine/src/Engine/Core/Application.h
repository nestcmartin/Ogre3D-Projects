#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "InputSystem/InputListener.h"

class Clock;

class Application : public InputListener
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