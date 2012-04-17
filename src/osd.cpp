#include "osd.h"

#include "renderer.h"
#include "game.h"
#include "font.h"

osd::osd(game *gobj)
   : drawable(gobj, 0, 0, 0, "gfx.png")
{

}

void
osd::render()
{
    drawHealthBar();
    drawAmmo();
}

void
osd::drawHealthBar()
{
    int x = 55;
    int y = 4;
    g->f->drawString("\\000000ff\\health", x+9, y+1, NULL);
    g->f->drawString("\\ff0000ff\\health", x+8, y, NULL);

    g->r->addOpQuad(NULL,
                    x+1, y+12, 100, 16,
                    0, 0, 0, 1);

    g->r->addOpQuad(NULL,
                    x, y+11, 100, 16,
                    1, 1, 1, 1);

    g->r->addOpQuad(NULL,
                    x+1, y+12, 98, 14,
                    1, 0, 0, 1);

}

void
osd::drawAmmo()
{
    int x = 4;
    int y = 4;

    g->f->drawString("\\000000ff\\ammo", x+9, y+1, NULL);
    g->f->drawString("\\ffd373ff\\ammo", x+8, y, NULL);

    g->r->addOpQuad(NULL,
                    x+1, y+12, 48, 16,
                    0, 0, 0, 1);

    g->r->addOpQuad(NULL,
                    x, y+11, 48, 16,
                    1, 1, 1, 1);

    g->f->drawString("\\000000ff\\000", x+12, y+14, NULL);
}


void
osd::update()
{

}
