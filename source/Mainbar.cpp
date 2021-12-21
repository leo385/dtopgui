#include "Mainbar.h"

//function that make push images to vector for devices on toolbar
template<typename T>
void Mainbar::initImageOfDevice(const unsigned& nElement)
{
	vecResourceImage.push_back(
		{ std::make_unique<T>(T(vecCells[nElement].second,
		{ vecCells[nElement].first.vCell.x, vecCells[nElement].first.vCell.y },
		{ vecCells[nElement].first.vCellSize.x, vecCells[nElement].first.vCellSize.y })) });
}


Mainbar::Mainbar(const olc::vf2d& pos)
	: _pos(pos)
{
	_space = new Space();
}


void Mainbar::Create(olc::PixelGameEngine* pge)
{
	_space->Create(pge);

	vecCells.reserve(16);

	//Generate Position of cells and id for them
	for (float cellX = (_pos.x + cell.vCellPadding.x); cellX < (_pos.x + (float)_size.x); cellX += fGrid)
	{
		for (float cellY = (_pos.y + cell.vCellPadding.y); cellY < (_pos.y + (float)_size.y); cellY += fGrid)
		{
			cell.nID++;
			cell.vCell = { cellX, cellY };
			vecCells.push_back({ cell, cell.nID });	
		}
	}

	//Initialize item images in toolbar vector resources
	//devices image
	initImageOfDevice<Router>(0);
	initImageOfDevice<Switch>(1);
	initImageOfDevice<Server>(2);
	initImageOfDevice<PC>(3);
	initImageOfDevice<Laptop>(4);

	//shapes image
	initImageOfDevice<sRectangle>(5);
	initImageOfDevice<sTriangle>(6);
	initImageOfDevice<sCircle>(7);

	//media image
	initImageOfDevice<connector::sStraight>(8);
	initImageOfDevice<connector::sCross>(9);
	initImageOfDevice<connector::sFiber>(10);
	initImageOfDevice<connector::sDce>(11);
	initImageOfDevice<connector::sDte>(12);
	initImageOfDevice<connector::sConsole>(13);
	initImageOfDevice<connector::sUsb>(14);

	//Rubber
	initImageOfDevice<sEraser>(15);

}

//Allocating an item function when click in toolbar
template<class F, typename TY>
void Mainbar::AllocateItemFromCell_id(const int& id, const TY& type, olc::vf2d& pos)
{
	if(b_SelectedCell != nullptr)
	{
		if(b_SelectedCell->nID == id)
		{
			factory<F, TY> = new F(type, id, { pos.x, pos.y }, { 40, 40 });
		}
	}
}

//When mouse is in Image "area" on toolbar (Collision)
bool Mainbar::isMouseOnImageDevice(olc::vf2d& mouse, _vecPtr_IResourceLoad& vec, int& i)
{
	return mouse.x >= vec.at(i).get()->getPos().x && mouse.y >= vec.at(i).get()->getPos().y
		&& mouse.x < vec.at(i).get()->getPos().x + vec.at(i).get()->getSize().x
		&& mouse.y < vec.at(i).get()->getPos().y + vec.at(i).get()->getSize().y;
}

bool Mainbar::nodeCollision(sNode* n1, sNode* n2)
{
	return std::fabsf((n1->pos.x - n2->pos.x)*(n1->pos.x - n2->pos.x) + (n1->pos.y - n2->pos.y) * (n1->pos.y - n2->pos.y)) < 0.01f;
}


void Mainbar::Update(olc::PixelGameEngine* pge, float& dt)
{
	_space->Update(pge, dt);

	vMouse = { (float)pge->GetMouseX(), (float)pge->GetMouseY() };

	//Assignment cell's id by clicking among the cells, purpose is to identify a cell.
	for (int i = 0; i < 16; i++)
	{

		if (isMouseOnImageDevice(vMouse, vecResourceImage, i))
		{
			if (pge->GetMouse(0).bPressed)
			{
				b_SelectedCell = &vecCells[i].first;
				idDevice = b_SelectedCell->nID;

			}
		}
	}

	//Canceling picked item when dragging.
	if (pge->GetKey(olc::ESCAPE).bPressed)
	{
		b_SelectedCell = nullptr;

		factory<DeviceFactory, DeviceType> = nullptr;
		factory<ShapeFactory, ShapeType> = nullptr;
		factory<MediaFactory, MediaType> = nullptr;
	}

	for (int i = 0; i < 16; i++)
		vecCells[i].first.color = olc::WHITE;
	//EOF_CELLS

	//set pointers to null when clicked is not specified
	if (pge->GetMouse(0).bPressed)
	{
		tmpDevice = nullptr;
		selectedDeviceNode = nullptr;

		tmpShape = nullptr;
		selectedShapeNode = nullptr;

		tmpMedia = nullptr;
		selectedMediaNode = nullptr;
		
	}

	//Add device in the space and push to vector, push nodes to vector too.
	for (int i = 1; i < 6; i++)
	{
		if (b_SelectedCell != nullptr && pge->GetMouse(0).bReleased)
		{
			idNode++;

			if (b_SelectedCell->nID == i)
			{
				//eraser off
				bErase = false;

				if (factory<DeviceFactory, DeviceType> != nullptr)
					tmpDevice = factory<DeviceFactory, DeviceType>->getItem();

				//logic for devices
				selectedDeviceNode = tmpDevice->GetNextNode(_space->vCursor);

				//Temporary node pos of previous location
				mousePos = { _space->vCursor.x, _space->vCursor.y };

				vecDevices.emplace_back(tmpDevice, idDevice);

				//vector with nodes was needed to check collision between them and set new position.
				vecAllNodes.emplace_back(selectedDeviceNode, idNode);

				vecSize++;
			}
		}
	}
	//EOF_DEVICE



	//SHAPES, get new allocated shape to tmpShape pointer from ShapeFactory
	if (b_SelectedCell != nullptr && factory<ShapeFactory, ShapeType> != nullptr)
	{
		tmpShape = factory<ShapeFactory, ShapeType>->getItem();
	}

	if (tmpShape != nullptr)
	{
		//Shapes logic of nodes
		if (b_SelectedCell != nullptr && pge->GetMouse(0).bReleased)
		{

			//Rectangle two points (sx, sy) and (ex, ey)
			if (b_SelectedCell->nID == 6)
			{
				bErase = false;

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

				
			}

			//Triangle three points (sx, sy) (ex, ey) (cx, cy)
			if (b_SelectedCell->nID == 7)
			{
				bErase = false;

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

			}


			//Circle two points (sx, sy) origin point and (ex, ey) radius 
			if (b_SelectedCell->nID == 8)
			{
				bErase = false;

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);

				selectedShapeNode = tmpShape->GetNextNode(_space->vCursor);
			}

		}

		if (selectedShapeNode != nullptr)
		{
			listShapes.push_back({ tmpShape });
		}

	}

	tmpShape = nullptr;
	//EOF_SHAPES

	//MEDIA

	if (b_SelectedCell != nullptr && factory<MediaFactory, MediaType> != nullptr)
	{
		tmpMedia = factory<MediaFactory, MediaType>->getItem();
	}

	if (tmpMedia != nullptr)
	{
		if (b_SelectedCell != nullptr && pge->GetMouse(0).bReleased)
		{
			for (int i = 9; i < 16; i++)
			{
				if (b_SelectedCell->nID == i)
				{
					//Eraser off
					bErase = false;

					selectedMediaNode = tmpMedia->GetNextNode(_space->vCursor);

					selectedMediaNode = tmpMedia->GetNextNode(_space->vCursor);
				}
			}
	
		}

		if (selectedMediaNode != nullptr)
		{
			vecMedia.push_back({ tmpMedia });
		}
		
	}
		
	
	tmpMedia = nullptr;
	//EOF_MEDIA



	//position that new allocated objects are following when holding mouse left button
	mousePos = { _space->vCursor.x, _space->vCursor.y };
	
	//Hit node within device and moving around
	if (pge->GetMouse(0).bPressed)
	{
		selectedDeviceNode = nullptr;
		selectedShapeNode = nullptr;
		selectedMediaNode = nullptr;

		//hit device's nodes
			for (auto& vdn : vecDevices)
			{
				//When hit a node (it works only after allocated)
				selectedDeviceNode = vdn.first->HitNode(_space->vCursor);

				if (selectedDeviceNode != nullptr)
				{
					

					idDevice = vdn.second;
					break;
				}

			}

			//hit shape's nodes
			for (auto& shape : listShapes)
			{
				selectedShapeNode = shape->HitNode(_space->vCursor);

				if (selectedShapeNode != nullptr)
				{

					break;
				}
			}

			
			for (auto& media : vecMedia)
			{

				selectedMediaNode = media->HitNode(_space->vCursor);

				if (selectedMediaNode != nullptr)
				{

					break;
				}



			}
				

	}

	//Malloc Devices
	AllocateItemFromCell_id<DeviceFactory, DeviceType>(1, DeviceType::ROUTER, mousePos);
	AllocateItemFromCell_id<DeviceFactory, DeviceType>(2, DeviceType::SWITCH, mousePos);
	AllocateItemFromCell_id<DeviceFactory, DeviceType>(3, DeviceType::SERVER, mousePos);
	AllocateItemFromCell_id<DeviceFactory, DeviceType>(4, DeviceType::COMPUTER, mousePos);
	AllocateItemFromCell_id<DeviceFactory, DeviceType>(5, DeviceType::LAPTOP, mousePos);

	//Malloc Shapes
	AllocateItemFromCell_id<ShapeFactory, ShapeType>(6, ShapeType::RECTANGLE, mousePos);
	AllocateItemFromCell_id<ShapeFactory, ShapeType>(7, ShapeType::TRIANGLE, mousePos);
	AllocateItemFromCell_id<ShapeFactory, ShapeType>(8, ShapeType::CIRCLE, mousePos);

	//Malloc media
	AllocateItemFromCell_id<MediaFactory, MediaType>(9, MediaType::STRAIGHT, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(10, MediaType::CROSS, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(11, MediaType::FIBER, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(12, MediaType::DCE, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(13, MediaType::DTE, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(14, MediaType::CONSOLE, mousePos);
	AllocateItemFromCell_id<MediaFactory, MediaType>(15, MediaType::USB, mousePos);

	//ERASER
	if (b_SelectedCell != nullptr && b_SelectedCell->nID == 16 && pge->GetMouse(0).bPressed)
	{
		bErase = true;
	}

	if (bErase)
	{
		rubber = new sEraser();
		rubber->_pos = vMouse;
	}

	if (vecDevices.size() > 1)
	{
		vecDevices.erase(std::remove_if(vecDevices.begin(), vecDevices.end(),
			[&](auto& data)
			{
				if (bErase)
				{
					if (selectedDeviceNode != nullptr && selectedDeviceNode == data.first->HitNode(selectedDeviceNode->pos))
					{
						return true;
					}	
				}

				return false;

			}), vecDevices.end());

	}
	//EOF_ERASER
		
	//updating mousePos x,y ; setting position of node respect vCursor
	if (selectedDeviceNode != nullptr)
	{
		mousePos = { _space->vCursor.x, _space->vCursor.y };
		selectedDeviceNode->pos = _space->vCursor;
	}

	if (selectedShapeNode != nullptr)
	{
		mousePos = { _space->vCursor.x, _space->vCursor.y };
		selectedShapeNode->pos = _space->vCursor;
	}

	if (selectedMediaNode != nullptr)
	{
		mousePos = { _space->vCursor.x, _space->vCursor.y };
		selectedMediaNode->pos = _space->vCursor;
	}


	if (vecSize > 0)
	{
		for (size_t i = 0; i < vecDevices.size() - 1; i++)
		{
			size_t t = 0;

			//Devices collision through the nodes (while new allocating object from Toolbar)
			if (b_SelectedCell != nullptr && pge->GetMouse(0).bReleased)
			{

				if (vecAllNodes[i + t].first->pos == vecAllNodes[(size_t)vecSize - 1].first->pos)
				{
					vecAllNodes[(size_t)vecSize - 1].first->pos = { vecAllNodes[i + t].first->pos.x - 0.02f * fGrid, vecAllNodes[(size_t)vecSize - 1].first->pos.y };
				}

			}

			t += 1;
		}
		
		
//Devices collision through the nodes (after new allocated object from Toolbar)
for (auto& vnodeA : vecAllNodes)
{
	for (auto& vnodeB : vecAllNodes)
	{	
			//check if nodes are the same position
			if (vnodeA.first->pos == vnodeB.first->pos)
			{
				//check if nodes aren't the same ID
				if (vnodeA.second != vnodeB.second)
				{
					if (selectedDeviceNode != nullptr)
					{				
						if (selectedMediaNode != nullptr)
						{
							for (auto& media : vecMedia)
							{
								if (selectedMediaNode == media->HitNode(selectedMediaNode->pos))
								{
									selectedMediaNode->pos = { vnodeB.first->pos.x - 0.02f * fGrid, selectedMediaNode->pos.y };
									selectedDeviceNode->pos = { vnodeB.first->pos.x - 0.02f * fGrid, selectedDeviceNode->pos.y };
								}
							}
						}
						else
						{
							selectedDeviceNode->pos = { vnodeB.first->pos.x - 0.02f * fGrid, selectedDeviceNode->pos.y };
						}
					}
				}
			}			
		}
	}	
}
	
	//set pointers to null, when released to reset them
	if (pge->GetMouse(0).bReleased)
	{
		selectedDeviceNode = nullptr;
		selectedShapeNode = nullptr;
		selectedMediaNode = nullptr;
		b_SelectedCell = nullptr;

	}

}

void Mainbar::Draw(olc::PixelGameEngine* pge)
{
	_space->Draw(pge);
	
	//assignment static variables
	sItem::fWorldScale = _space->fScale;
	sItem::vWorldOffset = _space->vOffset;

	pge->SetPixelMode(olc::Pixel::MASK);
	
	//Current pick name of device
	nameOfDevice = " ";
	
	//Cursor mechanism unit
	_space->WorldToScreen(_space->vCursor, _space->sx, _space->sy);
	pge->DrawCircle(_space->sx, _space->sy, 3, olc::GREEN);


	//Draw undersign for new device instance
	if(b_SelectedCell != nullptr)
	{							
		for (int i = 1; i <= 5; i++)
		{
			if (b_SelectedCell->nID == i)
			{
				for (int i = _space->sx; i < _space->sx + (int)factory<DeviceFactory, DeviceType>->getItem()->_size.x / 2; i += 1 * (int)_space->fScale)
				{
					for (int j = _space->sy; j < _space->sy + (int)factory<DeviceFactory, DeviceType>->getItem()->_size.y / 2; j += 1 * (int)_space->fScale)
					{
						pge->DrawCircle(i, j, 3, olc::GREEN);
					}
				}

				nameOfDevice = factory<DeviceFactory, DeviceType>->getItem()->getName();
			}
		}
		
	}
	
	
	//device_identify_by_name while hitting nodes
	if (selectedDeviceNode != nullptr)
	{
		if (factory<DeviceFactory, DeviceType> != nullptr)
		{
			nameOfDevice = factory<DeviceFactory, DeviceType>->getItem()->getName();
		}

		switch (idDevice)
		{
			case 1:
				nameOfDevice = "Router";
			break;

			case 2:
				nameOfDevice = "Switch";
			break;

			case 3:
				nameOfDevice = "Server";
			break;

			case 4:
				nameOfDevice = "PC";
			break;

			case 5:
				nameOfDevice = "Laptop";
			break;

			//...

			default:
				nameOfDevice = " ";
			break;
		}

	}


	//DRAW_VECTOR_OF_SHAPES
	for (auto& shape : listShapes)
	{
		if (listShapes.size() != NULL)
		{
			shape->Draw(pge);
			shape->DrawNodes(pge);
		}
	}

	if (tmpShape != nullptr)
	{
		tmpShape->Draw(pge);
		tmpShape->DrawNodes(pge);
	}

	

	for (auto& media : vecMedia)
	{
		if (vecMedia.size() != NULL)
		{
			media->Draw(pge);

		}
	}

	//Media draw
	if (tmpMedia != nullptr)
	{
		tmpMedia->Draw(pge);
		tmpMedia->DrawNodes(pge);
	}


	//DRAW_VECTOR_OF_DEVICES_WITH_NODES
	for (auto& vdn : vecDevices)
	{
		if (vecDevices.size() != NULL)
		{
			vdn.first->Draw(pge);
			vdn.first->DrawNodes(pge);
		}
	}


	//For "first" shape/device that are hold in memory
	if (tmpDevice != nullptr)
	{
		tmpDevice->Draw(pge);
		tmpDevice->DrawNodes(pge);
	}

	//rubber draw
	if (bErase && rubber != nullptr)
	{
		pge->DrawRect((int)rubber->_pos.x - (int)rubber->_size.x / 2, (int)rubber->_pos.y - (int)rubber->_size.y / 2, rubber->_size.x, rubber->_size.y, olc::RED);
	}



	//DRAW TOOLBAR ON LEFT SIDE//

	//BORDER PANEL
	pge->FillRect(olc::vf2d(_pos.x, _pos.y), _size, olc::GREY);

	//BUTTONS PANEL
	for (auto& c : vecCells)
	{
		pge->FillRect((int)c.first.vCell.x, (int)c.first.vCell.y, c.first.vCellSize.x, c.first.vCellSize.y, c.first.color);
	}

	//Image Resources for devices in PANEL
	for (auto& dev : vecResourceImage)
	{
		dev->DrawImage(pge);
	}

	pge->SetPixelMode(olc::Pixel::NORMAL);

	//ACCESS_DEVICE_IDENTIFY_BY_NAME
	pge->DrawString(10, 30, "Currently pick: " + nameOfDevice, olc::RED, 2);

	//X&Y Coordinates String <Top/Left>
	pge->DrawString(10, 10, "X= " + std::to_string(vMouse.x) + ", " + "Y= " + std::to_string(vMouse.y), olc::WHITE, 1);
	

	//delete somethings
	if (!bErase)
		delete rubber;

	rubber = nullptr;
}


