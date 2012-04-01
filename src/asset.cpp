#include "asset.h"

#include "game.h"
#include "renderer.h"
#include "resourcemanager.h"
#include "image.h"

asset::asset(game *game, int x, int y, int z)
{
    g = game;

    texture = g->rm->getImage("tex.png");

    this->x = x;
    this->y = y;
    this->z = z;
}

asset::asset(game *game)
{
    g = game;

    texture = g->rm->getImage("tex.png");

    this->x = rand() % 960;
    this->y = rand() % 640;
    this->z = 0;
}


void
asset::render()
{
    g->r->addQuad(texture->getTexture(),
                      x, y, 50, 50,
                      0, 0, 1, 1);
}
