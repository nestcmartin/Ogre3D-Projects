#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <string>

class Application
{
protected:
	uint32_t frame_;
	float deltaTime_;
	std::string name_;

public:
	explicit Application(const std::string& name);
	virtual ~Application();

	virtual void setup() {}
	virtual void shutdown() {}

	virtual void run();
	virtual void pollEvents();

protected:
	void initSubSystems();
	void releaseSubSystems();
};

#endif // !__APPLICATION_H__
