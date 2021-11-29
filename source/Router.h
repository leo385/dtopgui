#pragma once
#include "Device.h"
#include "IResourceLoad.h"

class Router : public sDevice, public IResourceLoad<olc::Sprite>
{
public:
	Router() = default;
	Router(const int& nID, const olc::vf2d& pos, const olc::vi2d& size);

	//For Toolbar
	void DrawImage(olc::PixelGameEngine* pge) override;

	//When allocated device
	void Draw(olc::PixelGameEngine* pge) override;	
};

