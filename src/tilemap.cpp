#include <iostream>
#include <cstdio>
#include "resourcemanager.h"
#include "tilemap.h"
#include "tileset.h"
#include "tile.h"
#include "game.h"
#include "image.h"
#include "bits.h"

tilemap::tilemap(game *g, std::string t, Json::Value json)
       : drawable(g, 0, 0, 0, t)
{
    int i; 

    w = json.get("width", 0).asInt();
    h = json.get("height", 0).asInt();

    tw = json.get("twidth", 0).asInt();
    th = json.get("theight", 0).asInt();

    ts = g->rm->getTileset(json.get("tileset", "tileset.json").asString(), t);

    for ( i = 0 ; json["tilemap"][i].isInt() ;i++ )
    {
        map.push_back(json["tilemap"][i].asInt());
    }

    if ( i != w * h )
    {
        std::cout << "Tilemap is invalid, dimensions incorrect: " << w << "x" << h << " should be " << w * h << " but is " << map.size() << std::endl;
    }

}

tilemap::tilemap(game *g, std::string imgr, std::string t, std::string tileset)
       : drawable(g, 0, 0, 0, t)
{
    ts = g->rm->getTileset(tileset, t);
    imgrname = imgr;


    loadMap(imgr);
}

void
tilemap::loadMap(std::string imgr)
{
    image * img = g->rm->getImage(imgr, 1);

    w = img->w;
    h = img->h;

    tw = 16;
    th = 16;

    map.reserve(w*h);

    for (int i = 0; i < w * h; i++)
    {
        int x = 0;

        unsigned char r = img->pixels[i*4];
        unsigned char g = img->pixels[i*4+1];
        unsigned char b = img->pixels[i*4+2];
        unsigned char a = img->pixels[i*4+3];

        if      ( r == 0x00 && g == 0xcc && b == 0x00 ) x = 0;
        else if ( r == 0x00 && g == 0x66 && b == 0xb3 ) x = 1;
        else if ( r == 0xff && g == 0x80 && b == 0x00 ) x = 2;
        else if ( r == 0xff && g == 0xcc && b == 0x00 ) x = 3;
        else if ( r == 0x33 && g == 0x00 && b == 0x99 ) x = 4;
        else if ( r == 0x99 && g == 0x00 && b == 0x99 ) x = 5;
        else if ( r == 0xcc && g == 0xff && b == 0x00 ) x = 6;
        else if ( r == 0xff && g == 0x00 && b == 0x00 ) x = 7;
        else if ( r == 0x80 && g == 0x80 && b == 0x80 ) x = 8;
        else if ( r == 0x00 && g == 0x8f && b == 0x00 ) x = 9;
        else if ( r == 0x00 && g == 0x48 && b == 0x7d ) x = 10;
        else if ( r == 0xb3 && g == 0x5a && b == 0x00 ) x = 11;
        else if ( r == 0xb3 && g == 0x8f && b == 0x00 ) x = 12;
        else if ( r == 0x6b && g == 0x00 && b == 0x6b ) x = 13;
        else if ( r == 0x8f && g == 0xb3 && b == 0x00 ) x = 14;
        else if ( r == 0xb3 && g == 0x00 && b == 0x00 ) x = 15;
        else if ( r == 0xbe && g == 0xbe && b == 0xbe ) x = 16;
        else if ( r == 0x80 && g == 0xff && b == 0x80 ) x = 17;
        else if ( r == 0x80 && g == 0xc9 && b == 0xff ) x = 18;
        else if ( r == 0xff && g == 0xc0 && b == 0x80 ) x = 19;
        else if ( r == 0xff && g == 0xe6 && b == 0x80 ) x = 20;
        else if ( r == 0xaa && g == 0x80 && b == 0xff ) x = 21;
        else if ( r == 0xee && g == 0x00 && b == 0xcc ) x = 22;
        else if ( r == 0xff && g == 0x80 && b == 0x80 ) x = 23;
        else if ( r == 0x66 && g == 0x66 && b == 0x00 ) x = 24;
        else if ( r == 0xff && g == 0xbf && b == 0xff ) x = 25;
        else if ( r == 0x00 && g == 0xff && b == 0xcc ) x = 26;
        else if ( r == 0xcc && g == 0x66 && b == 0x99 ) x = 27;
        else if ( r == 0x99 && g == 0x99 && b == 0x00 ) x = 28;
        else                                            x = -1;

        map[i] = x;
        (void)a;
    }
}

tilemap::~tilemap()
{

}

void
tilemap::render()
{
    int tx = g->c.x / tw;
    int ty = g->c.y / th;
    int lx = (g->c.x + g->c.w) / tw;
    int ly = (g->c.y + g->c.h) / th;

    for (int xp = tx; xp <= lx ; xp++)
    {
        for (int yp = ty; yp <= ly ; yp++)
        {
            int i = yp*w+xp;
            ts->getIndex(map[i])->render((i % w) * tw, (i / w) * th, tw, th);
        }
    }

/*    for (int i = 0; i < w * h; i++)
    {
        ts->getIndex(map[i])->render((i % w) * tw, (i / w) * th, tw, th);
    }*/
}

void
tilemap::update()
{
    ts->update();

    if ( g->getReload() ) {
        loadMap(imgrname);
    }
}

int
tilemap::checkSlope(int x, int y, int w, int h, int type)
{
    if ( type == BIT_SLOPE_NE || type == BIT_SLOPE_NW )
    { /* flip_y */
        y = (th - y - h);
    }

    if ( type == BIT_SLOPE_SW || type == BIT_SLOPE_NW )
    { /* flip_x */
        x = (tw - x - w);
    }

    if ( x+w + y+h > tw )
        return 1;

    return 0;
}

void
tilemap::getTileBox(int *x, int *y, int *w, int *h, int tileid)
{
    int tx = (tileid % this->w) * tw;
    int ty = (tileid / this->w) * th;

    int bx = *x - tx;
    int by = *y - ty;

    if ( bx < 0 ) bx = 0;
    if ( by < 0 ) by = 0;

    int bw = ( *x + *w > tx+tw ) ? tw - bx :  *x + *w - tx - bx;
    int bh = ( *y + *h > ty+th ) ? th - by :  *y + *h - ty - by;

    *x = bx;
    *y = by;
    *w = bw;
    *h = bh;
}

int
tilemap::collidesWith(float x, float y, float w, float h, drawable *other)
{
    int ret = 0;
    int tx = x / tw;
    int ty = y / th;

    int lx = (x+w-1) / tw;
    int ly = (y+h-1) / th;

    for (int xp = tx; xp <= lx ; xp++)
    {
        for (int yp = ty; yp <= ly ; yp++)
        {
            int bits = ts->getIndex(map[yp*this->w+xp])->bits;

            int tbx = x;
            int tby = y;
            int tbw = w;
            int tbh = h;

            getTileBox(&tbx, &tby, &tbw, &tbh, (yp*this->w)+xp);

            if ( bits & BIT_SOLID )
                ret |= BIT_SOLID;

            if ( (bits & BIT_SLOPE_NE) && checkSlope(tbx, tby, tbw, tbh, BIT_SLOPE_NE) ) 
                ret |= (BIT_SOLID|BIT_SLOPE_NE);

            if ( (bits & BIT_SLOPE_NW) && checkSlope(tbx, tby, tbw, tbh, BIT_SLOPE_NW) )
                ret |= (BIT_SOLID|BIT_SLOPE_NW);

            if ( (bits & BIT_SLOPE_SE) && checkSlope(tbx, tby, tbw, tbh, BIT_SLOPE_SE) )
                ret |= (BIT_SOLID|BIT_SLOPE_SE);

            if ( (bits & BIT_SLOPE_SW) && checkSlope(tbx, tby, tbw, tbh, BIT_SLOPE_SW) )
                ret |= (BIT_SOLID|BIT_SLOPE_SW);

        }
    }

    return ret;
    (void)other;
}
