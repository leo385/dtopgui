#pragma once

#include "Device.h"

struct sNode
{
	sDevice* parent = nullptr;
	olc::vf2d pos = {0,0};
};
