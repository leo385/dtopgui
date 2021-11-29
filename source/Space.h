#pragma once

#include "World.h"
#include <cmath>

class Space : public World
{
public:
	Space()
	{
		std::cout << "Klasa Space\n";
	}
	
	
	void WorldToScreen(const olc::vf2d& v, int& nScreenX, int& nScreenY)
	{
		nScreenX = (v.x - vOffset.x) * fScale;
		nScreenY = (v.y - vOffset.y) * fScale;
	}
	
	void ScreenToWorld(int nScreenX, int nScreenY, olc::vf2d& v)
	{
  		v.x = (float)(nScreenX)	/ fScale + vOffset.x;
		v.y = (float)(nScreenY) / fScale + vOffset.y;
	}

	void Create(olc::PixelGameEngine* pge) override
	{
		vOffset = {(float)(-pge->ScreenWidth() / 2) / fScale, (float)(-pge->ScreenHeight() / 2) / fScale};
	}

	void Update(olc::PixelGameEngine* pge, float& dt) override
	{
		vMouse = {(float)pge->GetMouseX(), (float)pge->GetMouseY()};
		
		ScreenToWorld(0, 0, vWorldLeftTop);
		ScreenToWorld(pge->ScreenWidth(), pge->ScreenHeight(), vWorldRightBottom);

		//clipping lines from screen
		vWorldLeftTop.x = std::floorf(vWorldLeftTop.x);
		vWorldLeftTop.y = std::floorf(vWorldLeftTop.y);

		vWorldRightBottom.x = std::ceil(vWorldRightBottom.x);
		vWorldRightBottom.y = std::ceil(vWorldRightBottom.y);

		//Events handling	
		if(pge->GetMouse(2).bPressed)
		{
			vPanning = vMouse;
		}
		
		
		if(pge->GetMouse(2).bHeld)
		{
			vOffset -= (vMouse - vPanning) / fScale;
			vPanning = vMouse;
		}


		ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseBeforeZoom);

		if(pge->GetMouseWheel() > 0)
		{
			fScale *= 1.1f;
		}

		if(pge->GetMouseWheel() < 0)
		{
			fScale *= 0.9f;
		}
			
		ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseAfterZoom);	
		
		vOffset += (vMouseBeforeZoom - vMouseAfterZoom);		

		//Cursor mechanism

		vCursor.x = floorf((vMouseAfterZoom.x + 0.5f) * fGrid);
		vCursor.y = floorf((vMouseAfterZoom.y + 0.5f) * fGrid);

	}

	void Draw(olc::PixelGameEngine* pge) override
	{
	
	        //Draw Axis X & Y

		WorldToScreen({0, vWorldLeftTop.y}, sx, sy);
		WorldToScreen({0, vWorldRightBottom.y}, ex, ey);
		
		pge->DrawLine(sx, sy, ex, ey, olc::BLACK, 0xF0F0F0F0);

		WorldToScreen({vWorldLeftTop.x, 0}, sx, sy);
		WorldToScreen({vWorldRightBottom.x, 0}, ex, ey);

		pge->DrawLine(sx, sy, ex, ey, olc::BLACK, 0xF0F0F0F0);

		//Draw dots
		
		for(f_floatPerPixel x = vWorldLeftTop.x; x < vWorldRightBottom.x; x+=fGrid)
		{
			for(f_floatPerPixel y = vWorldLeftTop.y; y < vWorldRightBottom.y; y+=fGrid)
			{
				WorldToScreen({x, y}, sx, sy);
				pge->DrawCircle(sx, sy, 1, olc::BLUE);
			}
		}
	

	}

public:
	olc::vf2d vCursor = {0,0};
	int sx, sy, ex, ey;
	
	f_floatPerPixel fScale = 10.0f;
	olc::vf2d vOffset = {0, 0};

private:
	olc::vf2d vWorldLeftTop = {0,0};
	olc::vf2d vWorldRightBottom = {0,0};

	olc::vf2d vPanning = {0, 0};
	
	olc::vf2d vMouseBeforeZoom = {0, 0};
	olc::vf2d vMouseAfterZoom = {0, 0};

	f_floatPerPixel fGrid = 1.0f;
	
};
