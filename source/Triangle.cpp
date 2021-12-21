#include "Triangle.h"


sTriangle::sTriangle(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
{
	nMaxNodes = 3;
	vecNodes.reserve(nMaxNodes);

	IResourceLoad_id = nID;
	IResourceLoad_pos = pos;
	IResourceLoad_size = size;

	_nID = IResourceLoad_id;
	_pos = IResourceLoad_pos;
	_size = IResourceLoad_size;

	IResourceLoad::setGraphic("triangle.png");
	sItem::setName("Triangle");

}

void sTriangle::DrawImage(olc::PixelGameEngine* pge)
{
	pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
}

void sTriangle::Draw(olc::PixelGameEngine* pge)
{	
	if (vecNodes.size() > 0)
	{
		for (auto& node : vecNodes)
		{
			node.color = olc::BLUE;
		}
	}

	WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
	WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);
	WorldToScreen(sItem::getElementOfNode(2)->pos, cx, cy);

	pge->DrawTriangle(sx, sy, ex, ey, cx, cy, olc::GREEN);
	
}
