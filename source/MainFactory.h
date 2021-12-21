#ifndef MAINFACTORY_H
#define MAINFACTORY_H

/*
	This struct collaborating with other Factories.
*/
#include "ItemProporties.h" //sItem

template<class F, typename T>
struct MainFactory
{
	MainFactory() = default;
	~MainFactory() {}

	sItem* item = nullptr;
	virtual sItem* getItem() = 0;

	virtual void initItems(const T& type, const int& id, const olc::vf2d& pos, const olc::vi2d& size) = 0;
};


#endif MAINFACTORY_H