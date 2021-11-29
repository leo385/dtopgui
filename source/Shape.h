#pragma once
#include "World.h"

struct sShape;

struct sNode
{
	sShape* parent = nullptr;
	olc::vf2d pos = {0,0};
};

struct sShape
{
	uint32_t nMaxNodes = 0;

	int sx = 0;
	int sy = 0;
	int ex = 0;
	int ey = 0;

	 std::vector<sNode> vecNodes;	

	 static float fWorldScale;
	 static olc::vf2d vWorldOffset;

	 void WorldToScreen(const olc::vf2d& p, int& nScreenX, int& nScreenY)
	 {
		nScreenX = (p.x - vWorldOffset.x) * fWorldScale;
	        nScreenY = (p.y - vWorldOffset.y) * fWorldScale;	
	 }
	
	 sNode* getElement(unsigned i)
	{
		return &vecNodes.at(i);
	}

	 sNode* GetNextNode(const olc::vf2d& v)
	 {
		if(vecNodes.size() == nMaxNodes)
		{
			return nullptr;
		}

		sNode n;
		n.parent = this;
		n.pos = v;

		vecNodes.push_back(n);
		return &vecNodes[vecNodes.size() - 1];
	 }

	 sNode* HitNode(olc::vf2d& v)
	 {
		 for (auto& n : vecNodes)
		 {
			 if ((v - n.pos).mag() < 0.01f)
			 {
				 return &n;
			 }
    	 }
		 return nullptr;
	 }

	 void DrawNodes(olc::PixelGameEngine* pge)
	 {
		for(auto& n : vecNodes)
		{
			WorldToScreen(n.pos, sx, sy);
			pge->FillCircle(sx, sy, 3, olc::RED);
		}
	 }

};
