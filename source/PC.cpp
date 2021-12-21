#include "PC.h"


PC::PC(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
{
	nMaxNodes = 1;
	vecNodes.reserve(nMaxNodes);

	IResourceLoad_id = nID;
	IResourceLoad_pos = pos;
	IResourceLoad_size = size;

	_nID = IResourceLoad_id;
	_pos = IResourceLoad_pos;
	_size = IResourceLoad_size;

	IResourceLoad::setGraphic("pc.png");
	sItem::setName("PC");

}

void PC::DrawImage(olc::PixelGameEngine* pge)
{
	pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
}

void PC::Draw(olc::PixelGameEngine* pge)
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
