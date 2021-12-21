#pragma once


#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

#include "MainFactory.h"

enum ShapeType
{
	RECTANGLE = 1,
	TRIANGLE,
	CIRCLE,
	DIAMOND
};

class ShapeFactory : public MainFactory<ShapeFactory,ShapeType>
{
public:
	ShapeFactory(MainFactory* mainfactory)
		: _mainfactory(mainfactory){}

	void initItems(const ShapeType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size) override
	{
		switch (type)
		{
		case RECTANGLE:
			item = new sRectangle(id, pos, size);
		break;

		case TRIANGLE:
			item = new sTriangle(id, pos, size);
		break;
		
		case CIRCLE:
			item = new sCircle(id, pos, size);
		break;

		default:
			std::cout << "Could not find picked type\n";
			break;
		}
	}

	ShapeFactory(const ShapeType& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size)
		: _shapeType(type)
	{
		initItems(type, id, pos, size);
	}

	~ShapeFactory()
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
	ShapeType _shapeType;
	MainFactory* _mainfactory = nullptr;
};


