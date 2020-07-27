#ifndef __OVERLAY_MANAGER_H__
#define __OVERLAY_MANAGER_H__

#include "Core/Singleton.h"
#include "Core/STLHeaders.h"

class Overlay;

class OverlayManager : public Singleton<OverlayManager>
{
	friend Singleton<OverlayManager>;

private:
	std::unordered_map<const char*, Overlay*> overlays_;

public:
	virtual ~OverlayManager();

	void addOverlay(const char* name, int zorder);

private:
	OverlayManager();
};

#endif // !__OVERLAY_MANAGER_H__

