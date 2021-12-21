#pragma once
#include "ItemProporties.h"
#include "IResourceLoad.h"

class Laptop : public sItem, public IResourceLoad<olc::Sprite>
{
public:
	Laptop(const int& nID, const olc::vf2d& pos, const olc::vi2d& size);

	//For toolbar
	void DrawImage(olc::PixelGameEngine* pge) override;

	//For allocated device
    void Draw(olc::PixelGameEngine* pge) override;
};

