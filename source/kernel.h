#pragma once
#include "World.h"
#include "Mainbar.h"

class kernel : public olc::PixelGameEngine
{
public:
	kernel();
	
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	World* world = nullptr;
};

