#pragma once

#include "Router.h"
#include "Switch.h"
#include "Server.h"
#include "PC.h"
#include "Laptop.h"

#include "MainFactory.h"

enum DeviceType
{
	ROUTER = 1,
	SWITCH,
	SERVER,
	COMPUTER,
	LAPTOP
};

class DeviceFactory : public MainFactory<DeviceFactory,DeviceType>
{
public:
	DeviceFactory(MainFactory* mainfactory)
		: _mainfactory(mainfactory) {}

	void initItems(const DeviceType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size) override
	{
		switch (type)
		{
			//1. Devices
		case ROUTER:
			item = new Router(id, pos, size);
			break;

		case SWITCH:
			item = new Switch(id, pos, size);
			break;

		case SERVER:
			item = new Server(id, pos, size);
			break;

		case COMPUTER:
			item = new PC(id, pos, size);
			break;

		case LAPTOP:
			item = new Laptop(id, pos, size);
			break;

		default:
			std::cout << "Could not find picked type\n";
			break;
		}
	}

	DeviceFactory(const DeviceType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size)
		: _deviceType(type)
	{
		initItems(type, id, pos, size);
	}

	~DeviceFactory()
	{
		if(item == nullptr)
		{
	          delete item;
		}
	}

	//Override ItemProporties
	sItem* getItem() override
	{
		return item;
	}

private:
	DeviceType _deviceType;
	MainFactory* _mainfactory = nullptr;
};


