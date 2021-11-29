#pragma once
#include "olcPixelGameEngine.h"

#include <vector>
#include <memory>

struct World
{
	//For Cells ID and Grid Pixels
	using f_floatPerPixel = float;
	using i_intID = uint32_t;

	//For IP_ADDRESSING
	using Ip_Addrv4 = uint32_t;

	//static variables world
	static f_floatPerPixel fWorldScale;
	static olc::vf2d vWorldOffset;

	struct sCellSquare
	{
		olc::vf2d vCell = { 0.0f, 0.0f };
		olc::vi2d vCellSize = { 40, 40 };
		olc::vf2d vCellPadding = { 4.0f, 4.0f };

		olc::Pixel color;

		World::i_intID nID = 0;
	};

	
	
	olc::vf2d vMouse = { 0.f, 0.f };

	//MAINBAR_CPP_VARIABLES, cells in leftbar 
	sCellSquare cell;
	sCellSquare* b_SelectedCell = nullptr; //this pointer has been used in mainbar.cpp
	i_intID* b_SelectedID = nullptr; //this too


	virtual void Create(olc::PixelGameEngine* pge) = 0;
	virtual void Update(olc::PixelGameEngine* pge, float& dt) = 0;
	virtual void Draw(olc::PixelGameEngine* pge) = 0;
};


