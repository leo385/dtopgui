#pragma once

#include "Media.h"
#include "MainFactory.h"

enum MediaType
{
	STRAIGHT = 1,
	CROSS,
	FIBER,
	DCE,
	DTE,
	CONSOLE,
	USB
};

class MediaFactory : public MainFactory<MediaFactory,MediaType>
{
public:
	MediaFactory(MainFactory* mainfactory)
		: _mainfactory(mainfactory){}

	void initItems(const MediaType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size) override
	{
		switch (type)
		{
		case STRAIGHT:
			item = new connector::sStraight(id, pos, size);
		break;

		case CROSS:
			item = new connector::sCross(id, pos, size);
		break;

		case FIBER:
			item = new connector::sFiber(id, pos, size);
		break;

		case DCE:
			item = new connector::sDce(id, pos, size);
		break;

		case DTE:
			item = new connector::sDte(id, pos, size);
		break;

		case USB:
			item = new connector::sUsb(id, pos, size);
		break;

		case CONSOLE:
			item = new connector::sConsole(id, pos, size);
		break;

		default:
			std::cout << "Could not find picked type\n";
		break;
		}
	}

	MediaFactory(const MediaType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size)
		: _shapeType(type)
	{
		initItems(type, id, pos, size);
	}

	~MediaFactory()
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
	MediaType _shapeType;
	MainFactory* _mainfactory = nullptr;
};


