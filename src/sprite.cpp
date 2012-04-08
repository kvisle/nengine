#include <cstdio>
#include "game.h"
#include "drawable.h"
#include "sprite.h"
#include "renderer.h"
#include "image.h"
#include "font.h"
#include "resource.h"

sprite::sprite(game *g, int x, int y, int z, std::string tex)
      : drawable(g, x, y, z, tex)
{
    frame = 0;
    intcount = 0;
    animation = 0;
}

sprite::sprite(game *g, int x, int y, int z, std::string tex, Json::Value json)
      : drawable(g, x, y, z, tex)
{
    frame = 0;
    intcount = 0;
    animation = 0;

    loadJson(json);
}

void
sprite::loadJson(std::string res)
{
    loadJson(resource(res).getJson());
}

void
sprite::loadJson(Json::Value json)
{
    qw = json.get("qw", 32).asInt();
    qh = json.get("qh", 32).asInt();

    for (int i = 0 ; !json["box"][i].isNull() ;i++ )
    {
        struct box boxv;

        Json::Value box = json["box"][i];

        boxv.x = box.get("x", 0).asInt();
        boxv.y = box.get("y", 0).asInt();
        boxv.w = box.get("w", 0).asInt();
        boxv.h = box.get("h", 0).asInt();
        boxv.bits = box.get("bits", 0).asInt();

        boxes.push_back(boxv);
    }

    for (int i = 0 ; !json["frames"][i].isNull() ; i++)
    {
        struct frame framev;
        Json::Value frame = json["frames"][i];

        framev.x = frame.get("x", 0.0).asFloat();
        framev.y = frame.get("y", 0.0).asFloat();
        framev.w = frame.get("w", 0.0).asFloat();
        framev.h = frame.get("h", 0.0).asFloat();
        framev.ox = frame.get("ox", 0.0).asFloat();
        framev.oy = frame.get("oy", 0.0).asFloat();

        for (int y = 0 ; frame["box"][y].isInt() ;y++ )
        {
            framev.boxes.push_back(frame["box"][y].asInt());
        }

        frames.push_back(framev);
    }

    for (int i = 0 ; !json["animations"][i].isNull() ; i++)
    {
        struct animation aniv;
        Json::Value animation = json["animations"][i];

        aniv.loop = animation.get("loop", 1).asInt();
        aniv.interval = animation.get("interval", 10).asInt();
        aniv.next = animation.get("next", 0).asInt();

        for (int y = 0 ; animation["frames"][y].isInt() ;y++ )
        {
            aniv.frames.push_back(animation["frames"][y].asInt());
        }
        animations.push_back(aniv);
    }

    printInfo();
}

sprite::~sprite()
{

}

void
sprite::printInfo()
{
    std::cout << "Animations: " << animations.size() << std::endl;
    std::cout << "Boxes: " << boxes.size() << std::endl;
    std::cout << "Frames: " << frames.size() << std::endl;
}

void
sprite::render()
{
    if ( animation >= (signed int)animations.size() )
        return;

    if ( ++intcount >= animations[animation].interval )
    {
        frame++;
        intcount = 0;

        if ( frame >= (signed int)animations[animation].frames.size() )
        {
            frame = 0;
            if ( !animations[animation].loop )
            {
                animation = animations[animation].next;
            }
        }
    }

    struct frame * f = &(frames[animations[animation].frames[frame]]);

/*    printf("animation %02d, frame(%02d/%02d)=%02d\n", 
            animation,
            frame,
            animations[animation].frames.size(),
            animations[animation].frames[frame]);*/

    g->r->addQuad(tex->getTexture(),
                  x+f->ox, y+f->oy, qw, qh,
                  f->x, f->y, f->w, f->h);

    renderBox();
}

void
sprite::renderBox()
{
    for (int i = 0; i < frames[animations[animation].frames[frame]].boxes.size(); i++)
    {
        struct box myb = boxes[frames[animations[animation].frames[frame]].boxes[i]];
        myb.x += this->x;
        myb.y += this->y;

        g->r->addOpQuad(myb.x, myb.y, myb.w, myb.h,
                        1, 1, 1, 0.5);
    }
}

void
sprite::update()
{
}

int
sprite::attemptMove(int *x, int *y)
{
    int ret = 0;
    while( *x != 0 || *y != 0 )
    {
        if ( *x > 0 ) {
            ret = attemptMoveStep(1, 0);
            if ( ret )
                return ret;
            *x -= 1;
            this->x++;
        }
        if ( *x < 0 ) {
            ret = attemptMoveStep(-1, 0);
            if ( ret )
                return ret;
            *x += 1;
            this->x--;
        }
        if ( *y > 0 ) {
            ret = attemptMoveStep(0, 1);
            if ( ret )
                return ret;
            *y -= 1;
            this->y++;
        }
        if ( *y < 0 ) {
            ret = attemptMoveStep(0, -1);
            if ( ret )
                return ret;
            *y += 1;
            this->y--;
        }
    }
    return 0;
}

int
sprite::attemptMoveStep(int x, int y)
{
    int ret = 0;

    for (int i = 0; i < frames[animations[animation].frames[frame]].boxes.size(); i++)
    {
        struct box myb = boxes[frames[animations[animation].frames[frame]].boxes[i]];
        myb.x += this->x + x;
        myb.y += this->y + y;

//        printf("x: %02d y: %02d w: %02d h: %02d\n", myb.x, myb.y, myb.w, myb.h);

        ret |= g->collides(myb.x, myb.y, myb.w, myb.h, this);
    }

    return ret;
}

void
sprite::setAnimation(int x)
{
    if ( animation == x )
        return;

    if ( x < 0 || x > animations.size() )
        return;

    animation = x;
    frame = 0;

}
