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
tile::setCR(int cr)
{
    tw = th = cr;
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

Json::Value
tile::asJSON()
{
    Json::Value me;

    me["x"] = index;

    if ( bits )
        me["b"] = bits;

    if ( interval != 10 )
        me["i"] = interval;

    for (int i = 0; i < frames_n; i++)
    {
        me["frames"][i] = frames[i];
    }

    return me;
}

void
tile::addFrame(int id)
{
    if ( frames_n == 64 )
        return;
    frames[frames_n] = id;
    frames_n++;
}

void
tile::clearFrames(void)
{
    frame = 0;
    frames_n = 0;
}

int
tile::getFrames()
{
    return frames_n;
}

int
tile::getFrame(int id)
{
    if ( id < 0 )
        return 0;

    if ( frames_n <= id )
        return 0;

    return frames[id];
}

int 
tile::getInterval()
{
    return interval;
}

void
tile::setInterval(int v)
{
    if ( v == 0 )
        return;
    if ( v > 300 )
        return;

    interval = v;
}

