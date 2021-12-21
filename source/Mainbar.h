#pragma once

#include "Space.h"
#include "DeviceFactory.h"
#include "ShapeFactory.h"
#include "MediaFactory.h"

//declare rubber struct
struct sEraser;

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

	template<class F, typename TY> //class F - Factory, TY - type factory <enum class>
	void AllocateItemFromCell_id(const int& id, const TY& type, olc::vf2d& pos);

	bool isMouseOnImageDevice(olc::vf2d& mouse, _vecPtr_IResourceLoad& vec, int& i); 

	bool nodeCollision(sNode* n1, sNode* n2);


private:

	//it size specify the two vectors with nodes and devices
	int vecSize = 0;

	olc::vf2d _pos;
	olc::vi2d _size = {100, 400};

	f_floatPerPixel fGrid = 50.f;

	//from my "own variable" that assign vector with pointer to sprite image resource.
	_vecPtr_IResourceLoad vecResourceImage;	

	//new allocated item from factory template
	template<class F, typename TY>
	inline static MainFactory<F, TY>* factory;

	Space* _space = nullptr;

	sItem* tmpDevice = nullptr;
	sItem* tmpShape = nullptr;
	sItem* tmpMedia = nullptr;

	sNode* selectedDeviceNode = nullptr; //device's node pointer
	sNode* selectedShapeNode = nullptr;  //shape's node pointer
	sNode* selectedMediaNode = nullptr; // media's node pointer

	sEraser* rubber = nullptr;
	bool bErase = false;

	olc::vf2d mousePos = { 0,0 };
	olc::vf2d nodeTmpPos = { 0,0 };

	//id - identify devices and nodes both of them
	int idDevice;
	int idNode;

	std::string nameOfDevice;

	olc::vf2d pos = { 0,0 };

	//containers for devices and shapes
	std::vector<std::pair<sItem*, i_intID>> vecDevices;
	std::vector<std::pair<sCellSquare, i_intID>> vecCells;
	std::vector<std::pair<sNode*, int>> vecAllNodes;
	
	std::list<sItem*> listShapes;
	std::vector<sItem*> vecMedia; //vector with type of media connectors
};

struct sEraser : public sItem, public IResourceLoad<olc::Sprite>
{

	olc::vf2d _pos;
	olc::vi2d _size = { 40, 40 };

	int id = 16;
	
	sEraser() = default;
	sEraser(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
	{
		IResourceLoad_id = nID;
		IResourceLoad_pos = pos;
		IResourceLoad_size = size;

		_nID = IResourceLoad_id;
		_pos = IResourceLoad_pos;
		_size = IResourceLoad_size;

		// Throw an exception if file does not exist!
		IResourceLoad::setGraphic("eraser.png");
	}

	void DrawImage(olc::PixelGameEngine* pge) override
	{
		pge->DrawSprite((int)_pos.x, (int)_pos.y, IResourceLoad::uImage.get(), 1);
	}

	void Draw(olc::PixelGameEngine* pge) override
	{
		//0
	}


};
