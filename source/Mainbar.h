#pragma once
#include "DeviceFactory.h"
#include "Space.h"

class Mainbar : public World
{
public:
	//my variables
	using _vecPtr_IResourceLoad = std::vector<std::unique_ptr<IResourceLoad<olc::Sprite>>>;


public:
	Mainbar(const olc::vf2d& pos);

	void Create(olc::PixelGameEngine* pge) override;
	void Draw(olc::PixelGameEngine* pge) override;
        void Update(olc::PixelGameEngine* pge, float& dt) override;

	template<typename T>
	void initImageOfDevice(const unsigned& nElement);

	void AllocateDeviceFromCell_id(const int& id, const DeviceType& type);
	
	bool isMouseOnImageDevice(olc::vf2d& mouse, _vecPtr_IResourceLoad& vec, int& i); 

private:
	olc::vf2d _pos;
	olc::vi2d _size = {100, 400};

	f_floatPerPixel fGrid = 50.f;

	_vecPtr_IResourceLoad vecResourceImage;	

	DeviceFactory* deviceFactory = nullptr;
	Space* _space = nullptr;
	sNode* selectedNode = nullptr;

	//for devices
	sDevice* tmpDevice = nullptr;
	int idDevice;

	std::string nameOfDevice;

	olc::vf2d pos = {0,0};

	std::vector<std::pair<sCellSquare, i_intID>> vecCells;
	//std::vector<sDevice*> vecDevices;
	
	//refactoring
	std::vector<std::pair<sDevice*, i_intID>> vecDevices;

};

