#pragma once
#include "World.h"

struct sItem;

struct sNode
{
	sItem* parent = nullptr;
	olc::vf2d pos = {0,0};
	float fRadius = 3.0f;
	olc::Pixel color;
};

struct sItem
{
	int _nID = 0;
	olc::vf2d _pos = { 0,0 };
	olc::vi2d _size = { 40,40 };
	std::string _name;

	uint32_t nMaxNodes = 0;

	int sx = 0;
	int sy = 0;

	int ex = 0;
	int ey = 0;

	//third point (cx, cy) for triangle, diamond
	int cx = 0;
	int cy = 0;

	std::vector<sNode> vecNodes;	

	 static float fWorldScale;
	 static olc::vf2d vWorldOffset;
	
	 void WorldToScreen(const olc::vf2d& p, int& nScreenX, int& nScreenY)
	 {
			nScreenX = (p.x - vWorldOffset.x) * fWorldScale;
	        nScreenY = (p.y - vWorldOffset.y) * fWorldScale;	
	 }
	
	 sNode* getElementOfNode(unsigned i)
	 {
		return &vecNodes.at(i);
	 }

	 sNode* GetNextNode(const olc::vf2d& v)
	 {
		 if (vecNodes.size() == nMaxNodes)
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
		 for (auto& n : vecNodes)
		 {
			 WorldToScreen(n.pos, sx, sy);
			 pge->FillCircle(sx, sy, n.fRadius, n.color);
		 }
	 }


	 virtual void Draw(olc::PixelGameEngine* pge) = 0;


	 sItem& getItem()
	 {
		 return *this;
	 }

	 //name functions
	 void setName(const char* name)
	 {
		 _name = name;
	 }

	 std::string getName() const
	 {
		 return _name;
	 }

	 void setPosition(olc::vf2d& pos)
	 {
		 _pos = pos;
	 }

};
