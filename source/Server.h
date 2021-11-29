#pragma once
#include "Device.h"
#include "IResourceLoad.h"

class Server : public sDevice, public IResourceLoad<olc::Sprite>
{
public:
	Server(const int& nID, const olc::vf2d& pos, const olc::vi2d& size);

	//For toolbar
	void DrawImage(olc::PixelGameEngine* pge) override;

	//For allocated device
    void Draw(olc::PixelGameEngine* pge) override;
};

