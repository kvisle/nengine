#include "game.h"
#include "renderer.h"
#include "image.h"
#include "overlay.h"

overlay::overlay(game *g)
       : drawable(g, 0, 0, 0, "gfx.png")
{

}

void
overlay::render()
{

}
