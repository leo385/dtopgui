#include "Rectangle.h"


sRectangle::sRectangle(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
{
	nMaxNodes = 2;
	vecNodes.reserve(nMaxNodes);

	IResourceLoad_id = nID;
	IResourceLoad_pos = pos;
	IResourceLoad_size = size;

	_nID = IResourceLoad_id;
	_pos = IResourceLoad_pos;
	_size = IResourceLoad_size;

	IResourceLoad::setGraphic("rectangle.png");
	sItem::setName("Rectangle");

}

void sRectangle::DrawImage(olc::PixelGameEngine* pge)
{
	pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
}

void sRectangle::Draw(olc::PixelGameEngine* pge)
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

	pge->DrawRect(sx, sy, ex - sx, ey - sy, olc::GREEN);
}
