#include <iostream>
#include <cstdio>

#include <SDL.h>

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

game::game()
{
    updateno = 0;

    in = new input();
    r = new renderer(960, 640);
    rm = new resourcemanager(this);
    f = new font(rm->getImage("charmap3.png"), this, 16, 16);

    c.x = 0;
    c.y = 0;
    c.w = 960;
    c.h = 640;

    assets.push_back(new tilemap(this, rm->getImage("tilemap.png"), "tileset2.png", "tileset2.json"));

    assets.push_back(new megaman(this, 20, 20, 20));
//    assets.push_back(new sprite(this, 20, 20, 20, "megaman.png", resource("sprite.json").getJson()));
//    assets.push_back(new tilemap(this, "tileset.png", resource("tilemap.json").getJson()));
//    tileset foo(this, "tileset.png", resource("tileset.json").getJson());

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


    f->drawString("\\ff0000ff\\foo", 0, 0);

    r->swap();
}

int
game::update()
{
    updateno++;

    if ( updateno % 60 == 0 )
    {
        char caption[128];
        sprintf(caption, "Assets: %lu", assets.size());
        SDL_WM_SetCaption(caption, NULL);
    }

    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->update();
    }


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
