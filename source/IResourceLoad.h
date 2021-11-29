#pragma once
#include <memory>
#include "olcPixelGameEngine.h"

template<typename D>
struct IResourceLoad
{
	void setGraphic(const char* file)
	{
		char pathToGFX[100] = "$(ProjectDir)../../../gfx/";
		strcat_s(pathToGFX, sizeof(pathToGFX), file);
		uImage = std::make_unique<D>(pathToGFX);
	}

	virtual void DrawImage(olc::PixelGameEngine* pge) = 0;

	olc::vf2d getPos() const
	{
		return IResourceLoad_pos;
	}
	
	olc::vf2d getSize() const
	{
		return IResourceLoad_size;
	}

	std::unique_ptr<D> uImage;

	int IResourceLoad_id;
	olc::vf2d IResourceLoad_pos;
	olc::vi2d IResourceLoad_size;
};
