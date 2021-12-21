#pragma once
#include "ItemProporties.h"
#include "IResourceLoad.h"

class sTriangle : public sItem, public IResourceLoad<olc::Sprite>
{
public:
	sTriangle(const int& nID, const olc::vf2d& pos, const olc::vi2d& size);

	//For toolbar
	void DrawImage(olc::PixelGameEngine* pge) override;
	void Draw(olc::PixelGameEngine* pge) override;
};

