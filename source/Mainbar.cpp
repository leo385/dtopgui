#include "Mainbar.h"

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

	//Initialize devices
	initImageOfDevice<Router>(0);
	initImageOfDevice<Switch>(1);
	initImageOfDevice<Server>(2);
}

void Mainbar::AllocateDeviceFromCell_id(const int& id, const DeviceType& type)
{
	if(b_SelectedCell != nullptr)
	{
		if(b_SelectedCell->nID != id)
		{
			std::cout << "None any of id\n";
		}
		else
		{
			deviceFactory = new DeviceFactory(type, id, {-100,-100}, {40, 40}); 		
		}
	}
}

bool Mainbar::isMouseOnImageDevice(olc::vf2d& mouse, _vecPtr_IResourceLoad& vec, int& i)
{
	return mouse.x >= vec.at(i).get()->getPos().x && mouse.y >= vec.at(i).get()->getPos().y
		&& mouse.x < vec.at(i).get()->getPos().x + vec.at(i).get()->getSize().x
		&& mouse.y < vec.at(i).get()->getPos().y + vec.at(i).get()->getSize().y;
}

void Mainbar::Update(olc::PixelGameEngine* pge, float& dt)
{
	_space->Update(pge, dt);

	vMouse = { (float)pge->GetMouseX(), (float)pge->GetMouseY() };

	for (int i = 0; i < 3; i++)
	{

		if (isMouseOnImageDevice(vMouse, vecResourceImage, i))
		{
			if (pge->GetMouse(0).bPressed)
			{
				b_SelectedCell = &vecCells[i].first;
				idDevice = b_SelectedCell->nID;
			}
		}
		
		vecCells[i].first.color = olc::WHITE;
		
	}
		
	//Cancel Choosing device
	if(pge->GetKey(olc::Key::ESCAPE).bPressed)
	{
        deviceFactory = nullptr;
		b_SelectedCell = nullptr;
	}
	
	//Allocate device on heap in deviceFactory pointer
	AllocateDeviceFromCell_id(1, DeviceType::ROUTER);
	AllocateDeviceFromCell_id(2, DeviceType::SWITCH);
	AllocateDeviceFromCell_id(3, DeviceType::SERVER);

	//Events mouse handler related with using nodes with devices.
	if(pge->GetMouse(0).bPressed)
	{
	     tmpDevice = nullptr;
	     selectedNode = nullptr;
	}
		
	//Add device in the space and push to vector
	if (b_SelectedCell != nullptr && pge->GetMouse(0).bReleased)
	{
		tmpDevice = deviceFactory->getDevice();
		selectedNode = tmpDevice->GetNextNode(_space->vCursor);

		vecDevices.emplace_back(tmpDevice, idDevice);
	}

	//Hit node within device and moving around
	if (pge->GetMouse(0).bPressed)
	{
		selectedNode = nullptr;

		for (auto& vdn : vecDevices)
		{
			selectedNode = vdn.first->HitNode(_space->vCursor);

			if (selectedNode != nullptr)
			{
				idDevice = vdn.second;
			}

			if (selectedNode != nullptr)
			{
				break;
			}
		}
	}

	if (selectedNode != nullptr)
	{
		selectedNode->pos = _space->vCursor;
	}

	if (pge->GetMouse(0).bReleased)
	{
		selectedNode = nullptr;
		b_SelectedCell = nullptr;
	}
     
}

void Mainbar::Draw(olc::PixelGameEngine* pge)
{
	_space->Draw(pge);
	
	//assignment static variables
	sDevice::fWorldScale = _space->fScale;
	sDevice::vWorldOffset = _space->vOffset;

	pge->SetPixelMode(olc::Pixel::MASK);
	
	//Current pick name of device
	nameOfDevice = " ";
	
	//Cursor mechanism unit
	_space->WorldToScreen(_space->vCursor, _space->sx, _space->sy);
	pge->DrawCircle(_space->sx, _space->sy, 3, olc::GREEN);


	//Draw undersign for new device instance
	if(b_SelectedCell != nullptr)
	{
		for(int i = _space->sx; i < _space->sx + (int)deviceFactory->getDevice()->_size.x / 2; i+=1*(int)_space->fScale)
		{
			for(int j = _space->sy; j < _space->sy + (int)deviceFactory->getDevice()->_size.y / 2; j+=1*(int)_space->fScale)
			{
				pge->DrawCircle(i, j, 3, olc::GREEN);	
			}
		}
		
		nameOfDevice = deviceFactory->getDevice()->getDeviceName();
	}
	
	
	//device_identify_by_name while hitting nodes
	if (selectedNode != nullptr)
	{
		nameOfDevice = deviceFactory->getDevice()->getDeviceName();

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

			//...

			default:
				nameOfDevice = " ";
			break;
		}

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
	
		


}


