#include "Router.h"

float sItem::fWorldScale = 1.0f;
olc::vf2d sItem::vWorldOffset = { 0,0 };

Router::Router(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
{
	nMaxNodes = 1;
	vecNodes.reserve(nMaxNodes);

	IResourceLoad_id = nID;
	IResourceLoad_pos = pos;
	IResourceLoad_size = size;

	_nID = IResourceLoad_id;
	_pos = IResourceLoad_pos;
	_size = IResourceLoad_size;

	// Throw an exception if file does not exist!
	IResourceLoad::setGraphic("router.png");
	sItem::setName("Router");

}


void Router::DrawImage(olc::PixelGameEngine* pge)
{
	pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
}

void Router::Draw(olc::PixelGameEngine* pge)
{
	if (vecNodes.size() > 0)
	{
		for (auto& node : vecNodes)
		{
			node.color = olc::RED;
		}
	}

	WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
	pge->DrawSprite(sx - _size.x / 2, sy - _size.y / 2, uImage.get(), 1);

}



