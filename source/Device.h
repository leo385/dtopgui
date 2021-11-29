#pragma once
#include "Shape.h"

struct sDevice : public sShape
{
	 int _nID = 0;
	 olc::vf2d _pos = { 0,0 };
	 olc::vi2d _size = { 0,0 };
	 std::string _deviceName;

	 virtual void Draw(olc::PixelGameEngine* pge) = 0;

	 void setDeviceName(const char* name)
	 {
		_deviceName = name;	
	 }

	 std::string getDeviceName() const
	 {
		return _deviceName;
	 }
};
