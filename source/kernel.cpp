#define OLC_PGE_APPLICATION
#include "kernel.h"

kernel::kernel()
{
    sAppName = "dtopgui";
 
    world = new Mainbar({0.0f, 150.0f});
}

bool kernel::OnUserCreate()
{
    world->Create(this);
    return true;
}

bool kernel::OnUserUpdate(float fElapsedTime)
{
    world->Update(this, fElapsedTime);
    Clear(olc::DARK_GREY);
    world->Draw(this);

    return true;
}
