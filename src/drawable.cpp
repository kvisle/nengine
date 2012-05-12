#include <cstdio>
#include "drawable.h"

#include "game.h"
#include "image.h"
#include "resourcemanager.h"

drawable::drawable(game *game, int x, int y, int z, std::string texture)
{
    g = game;

    this->x = x;
    this->y = y;
    this->z = z;

    removeme = 0;

    tex = g->rm->getImage(texture);
}

drawable::~drawable()
{

}

void
drawable::render()
{

}

void
drawable::update()
{

}

int
drawable::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    (void)other;
    (void)bits;

    return 0;
}

void
drawable::input(union ninput in)
{
    (void)in;
}

void
drawable::pickUp(drawable *d)
{

}

void
drawable::unLock(drawable *d)
{

}

void
drawable::damage(drawable *d)
{

}

void
drawable::kill()
{

}

int
drawable::identify()
{
    return -1;
}

void
drawable::remove()
{
    puts("remove()");
    removeme = 1;
}

int
drawable::inFrame()
{
    return 1;
}
