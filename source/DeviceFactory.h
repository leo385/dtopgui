#pragma once

#include "Router.h"
#include "Switch.h"
#include "Server.h"

enum DeviceType
{
	ROUTER = 1,
	SWITCH,
	SERVER

};


class DeviceFactory
{
public:
	DeviceFactory() = default;

	DeviceFactory(const DeviceType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size)
		: _deviceType(type)
	{
		switch(type)
		{
			case ROUTER:
				device = new Router(id, pos, size);
			break;

			case SWITCH:
				device = new Switch(id, pos, size);			
			break;
			
			case SERVER:
				device = new Server(id, pos, size);		
			break;

			//...
			default:
				std::cout << "Could not find choosed type\n";
			break;
		}
	}

	~DeviceFactory()
	{
		if(device == nullptr)
		{
	              delete device;
		}
	}
	
	sDevice* getDevice()
	{
		return device;
	}

private:
	sDevice* device = nullptr;
	DeviceType _deviceType;
};


