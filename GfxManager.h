#ifndef GFX_MANAGER_H
#define GFX_MANAGER_H

#include "Engine.h"

class GfxManager
{
public:
	static void drawPoint(int x, int y, uint32_t color);
	static void drawCircle(int x, int y, int r, uint32_t color);
};

#endif // GFX_MANAGER_H