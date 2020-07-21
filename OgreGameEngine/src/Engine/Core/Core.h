#ifndef __CORE_H__
#define __CORE_H__

namespace Ogre 
{
	class Root;
}

class Core
{
private:
	static Ogre::Root* root;

public:
	static void Init();
	static void Release();

	static Ogre::Root* Root() { return root; }
};

#endif // !__CORE_H__

