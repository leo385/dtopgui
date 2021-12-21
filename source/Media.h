#pragma once
#include "ItemProporties.h"
#include "IResourceLoad.h"

namespace connector
{
	//Straight Cable Media
	class sStraight : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sStraight(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("straight-through.png");
			sItem::setName("Straight-through");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::BLACK);
		}
	};

	//Cross-Over Cable Media
	class sCross : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sCross(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("cross-over.png");
			sItem::setName("Cross-over");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::BLACK, 0xFFFF00);
		}
	};


	class sFiber : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sFiber(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("fiber.png");
			sItem::setName("Fiber");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::YELLOW);
		}
	};

	class sDce : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sDce(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("dce.png");
			sItem::setName("DCE");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::RED);
		}
	};

	class sDte : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sDte(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("dte.png");
			sItem::setName("DTE");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::DARK_RED);
		}
	};

	class sConsole : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sConsole(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("console.png");
			sItem::setName("Console");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::Pixel(89,171,157));
		}
	};


	class sUsb : public sItem, public IResourceLoad<olc::Sprite>
	{
	public:
		sUsb(const int& nID, const olc::vf2d& pos, const olc::vi2d& size)
		{
			nMaxNodes = 2;
			vecNodes.reserve(nMaxNodes);

			IResourceLoad_id = nID;
			IResourceLoad_pos = pos;
			IResourceLoad_size = size;

			_nID = IResourceLoad_id;
			_pos = IResourceLoad_pos;
			_size = IResourceLoad_size;

			IResourceLoad::setGraphic("usb.png");
			sItem::setName("USB");
		}

		//For toolbar
		void DrawImage(olc::PixelGameEngine* pge) override
		{
			pge->DrawSprite((int)_pos.x, (int)_pos.y, uImage.get(), 1);
		}

		void Draw(olc::PixelGameEngine* pge) override
		{
			WorldToScreen(sItem::getElementOfNode(0)->pos, sx, sy);
			WorldToScreen(sItem::getElementOfNode(1)->pos, ex, ey);

			pge->DrawLine(sx, sy, ex, ey, olc::WHITE);
		}
	};

}