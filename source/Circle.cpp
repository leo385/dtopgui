#include "Circle.h"


sCircle::sCircle(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
{
	nMaxNodes = 2;
	vecNodes.reserve(nMaxNodes);

	IResourceLoad_id = nID;
	IResourceLoad_pos = pos;
	IResourceLoad_size = size;

	_nID = IResourceLoad_id;
	_pos = IResourceLoad_pos;
	_size = IResourceLoad_size;

	IResourceLoad::setGraphic("circle.png");
	sItem::setName("Circle");

}

void sCircle::DrawImage(olc::PixelGameEngine* pge)
{
	pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
}

void sCircle::Draw(olc::PixelGameEngine* pge)
{	
	if (vecNodes.size() > 0)
	{
		for (auto& node : vecNodes)
		{
			node.color = olc::BLUE;
		}
	} 

	float fRadius = (vecNodes[0].pos - vecNodes[1].pos).mag();

	WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
	WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

	pge->DrawLine(sx, sy, ex, ey, olc::WHITE, 0xFF0000);
	pge->DrawCircle(sx, sy, fRadius * fWorldScale, olc::GREEN);
}
