#include <iostream>
#include <cstdio>

#include "tile.h"
#include "game.h"
#include "renderer.h"
#include "image.h"

tile::tile(game *g, std::string tex, int x, int b, int i, int fc, int f[64], int tw, int th)
    : drawable(g, 0, 0, 0, tex)
{
    index = x;
    bits = b;
    interval = i;
    frames_n = fc;
    frame = 0;
    n = 0;

    printf("TILE: %d, bits: %d\n", index, bits);

    this->tw = tw;
    this->th = th;

    for (int i = 0; i < fc; i++)
        frames[i] = f[i];
}

tile::~tile()
{
}

void
tile::setIndex(int x)
{
    index = x;
}

void
tile::render(float x, float y, float w, float h)
{
    int ind = frames_n ? frames[frame] : index;
    float sx = ( ind % tw ) * ( 1.0 / tw );
    float sy = ( ind / tw ) * ( 1.0 / th );
    float sw = 1.0 / tw;
    float sh = 1.0 / th;

    if ( ind < 0 )
        return;
//    printf("Rendering at: %2.2f, %2.2f, %2.2f, %2.2f\n", sx, sy, sw, sh);

    g->r->addQuad(tex->getTexture(), &(g->c),
                  x, y, w, h,
                  sx, sy, sw, sh);
}

void
tile::update()
{
    if (++n % interval == 0)
    {
        if (++frame >= frames_n)
            frame = 0;
    }
}
