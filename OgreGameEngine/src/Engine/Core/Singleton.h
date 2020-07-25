#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "STLHeaders.h"

template<typename T>
class Singleton
{
private:
	static std::unique_ptr<T> instance_;

protected:
	Singleton() {}

public:
	virtual ~Singleton() {}

	template<typename ...Targs>
	inline static T* init(Targs&&...args)
	{
		assert(instance_.get() == nullptr);
		instance_.reset(new T(std::forward<Targs>(args)...));
		return instance_.get();
	}

	inline static void close() 
	{
		instance_.reset();
	}

	inline static T* Instance()
	{
		if (instance_.get() == nullptr)
		{
			init();
		}
		return instance_.get();
	}
};

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;

#endif // !__SINGLETON_H__