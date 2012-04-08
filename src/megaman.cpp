#include "megaman.h"
#include "font.h"
#include "game.h"

megaman::megaman(game *g, int x, int y, int z)
       : sprite(g, x, y, z, "megaman.png")
{
    loadJson(std::string("sprite.json"));
}

megaman::~megaman()
{

}

void
megaman::update()
{
    moveGravity();
}

void
megaman::render()
{
    sprite::render();

    g->f->drawString("megaman", x - 24, y - 24);
}

void
megaman::moveGravity()
{
    int gy = 8, gx = 0;

    if ( !attemptMove(&gx, &gy) )
    {
        setAnimation(3);
    }
    else
    {
        setAnimation(0);
    }
}
