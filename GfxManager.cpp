#ifndef GFX_MANAGER
#define GFX_MANAGER



#include "GfxManager.h"
#include "Engine.h"
#include <math.h>

void GfxManager::drawPoint(int x, int y, uint32_t color)
{
	if (0 <= x && x < SCREEN_WIDTH
	&&  0 <= y && y < SCREEN_HEIGHT)
	{
		buffer[y][x] = color;
	}
}

void GfxManager::drawCircle(int x, int y, int r, uint32_t color)
{
	if (x + r < 0             ||
		x - r > SCREEN_WIDTH  ||
		y + r < 0             ||
		y - r > SCREEN_HEIGHT) {
		return;
	}

	int rr = r * r;
	for (int i = x - r; i <= x + r; i++)
	{
		int root = sqrt(rr - (i - x) * (i - x));
		int j_min = y - root;
		int j_max = y + root;
		for (int j = j_min; j <= j_max; j++)
		{
			GfxManager::drawPoint(i, j, color);
		}
	}
}

#endif // GFX_MANAGER