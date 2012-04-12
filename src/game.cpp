#include <iostream>
#include <cstdio>

#ifdef TARGET_SDL
#include <SDL.h>
#endif

#include "renderer.h"
#include "resourcemanager.h"
#include "game.h"
#include "image.h"
#include "drawable.h"
#include "tileset.h"
#include "tilemap.h"
#include "resource.h"
#include "font.h"
#include "sprite.h"
#include "megaman.h"
#include "input.h"

game::game() : c(0, 0, 960, 640)
{
    updateno = 0;

    in = new input();
    r = new renderer(960, 640);
    rm = new resourcemanager(this);
    f = new font(rm->getImage("charmap3.png"), this, 16, 16);

    assets.push_back(new tilemap(this, "tilemap.png", "gfx.png", "gfxts1.json"));
    assets.push_back(new megaman(this, 124*32, 64, 0));

    std::cout << "Made game" << std::endl;
}

game::~game()
{
    delete(rm);
    delete(r);
    delete(f);
    delete(in);
}

void
game::render()
{
    r->clear();

    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->render();
    }

    f->drawString("\\000000ff\\trygve is testing", 2, 2, NULL);
    f->drawString("\\ff0000ff\\trygve is testing", 0, 0, NULL);


    r->swap();
}

int
game::update()
{
    updateno++;

#ifdef TARGET_SDL
    if ( updateno % 60 == 0 )
    {
        char caption[128];
        sprintf(caption, "Assets: %lu", assets.size());
        SDL_WM_SetCaption(caption, NULL);
    }
#endif

    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->update();
    }


    this->setReload(0);

    return 0;
}

int
game::collides(float x, float y, float w, float h, drawable * me)
{
    int ret = 0;
    for (uint32_t i=0; i < assets.size(); i++)
    {
        if ( assets[i] == me )
            continue;

        ret |= assets[i]->collidesWith(x, y, w, h, me);

    }
    return ret;
}

void
game::setReload( int val )
{
    this->reload = val;
}

int
game::getReload()
{
    return reload;
}
