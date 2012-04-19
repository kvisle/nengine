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
drawable::collidesWith(float x, float y, float w, float h, drawable *other)
{
    (void)x;
    (void)y;
    (void)w;
    (void)h;
    (void)other;

    return 0;
}

void
drawable::input(union ninput in)
{
    (void)in;
}
