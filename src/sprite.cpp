#include <cstdio>
#include "game.h"
#include "bits.h"
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

    flip_x = 0;
    flip_y = 0;
}

sprite::sprite(game *g, int x, int y, int z, std::string tex, Json::Value json)
      : drawable(g, x, y, z, tex)
{
    frame = 0;
    intcount = 0;
    animation = 0;

    flip_x = 0;
    flip_y = 0;

    loadJson(json);
}

void
sprite::damage(drawable *d)
{
    puts("Unimplemented damage function.");
}

void
sprite::kill()
{
    puts("Unimplemented kill function.");
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
    if ( animation >= animations.size() )
        return;

    if ( ++intcount >= animations[animation].interval )
    {
        frame++;
        intcount = 0;

        if ( frame >= animations[animation].frames.size() )
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

    g->r->addQuad(tex->getTexture(), 1.0, &(g->c),
                  x+f->ox, y+f->oy, qw, qh,
                  f->x, f->y, f->w, f->h,
                  1.0f, 1.0f, 1.0f, 1.0f,
                  flip_x, flip_y);

    if ( g->drawBoxes() )
        renderBox();
}

void
sprite::renderBox()
{
    for (unsigned int i = 0; i < frames[animations[animation].frames[frame]].boxes.size(); i++)
    {
        struct box myb = boxes[frames[animations[animation].frames[frame]].boxes[i]];
        myb.x += this->x;
        myb.y += this->y;

        g->r->addOpQuad(&(g->c),
                        myb.x, myb.y, myb.w, myb.h,
                        1, 1, 1, 0.5);
    }
}

void
sprite::update()
{
}

int
sprite::attemptMove(int *x, int *y, int bits)
{
    int ret = 0;
    int mx, my;
    while( *x != 0 || *y != 0 )
    {
        if ( *x > 0 ) {
            mx = 1;
            my = 0;
            ret = attemptMoveStep(&mx, &my, bits);
            if ( ret & BIT_SOLID )
                return ret;
            *x -= 1;
            this->x += mx;
            this->y += my;
        }
        if ( *x < 0 ) {
            mx = -1;
            my = 0;
            ret = attemptMoveStep(&mx, &my, bits);
            if ( ret & BIT_SOLID )
                return ret;
            *x += 1;
            this->x += mx;
            this->y += my;
        }
        if ( *y > 0 ) {
            mx = 0;
            my = 1;
            ret = attemptMoveStep(&mx, &my, bits);
            if ( ret & BIT_SOLID )
                return ret;
            *y -= 1;
            this->x += mx;
            this->y += my;
        }
        if ( *y < 0 ) {
            mx = 0;
            my = -1;
            ret = attemptMoveStep(&mx, &my, bits);
            if ( ret & BIT_SOLID)
                return ret;
            *y += 1;
            this->x += mx;
            this->y += my;
        }
    }
    return 0;
}

int
sprite::attemptMoveStep(int *x, int *y, int bits)
{
    int ret = 0;

    for ( unsigned int i = 0; i < frames[animations[animation].frames[frame]].boxes.size(); i++)
    {
        struct box myb = boxes[frames[animations[animation].frames[frame]].boxes[i]];
        myb.x += this->x + *x;
        myb.y += this->y + *y;

        ret |= g->collides(myb.x, myb.y, myb.w, myb.h, this, myb.bits);
    }

    if ( (ret & (BIT_SLOPE_NE|BIT_SOLID)) == (BIT_SLOPE_NE|BIT_SOLID) && (bits & BIT_SLOPE_NE) )
    {
        if ( *x == 1 && *y == 0 )
        {
            *y -= 1;
            return attemptMoveStep(x, y, 0);
        }
        if ( *x == 0 && *y == -1 )
        {
            *x -= 1;
            return attemptMoveStep(x, y, 0);
        }
    }
    if ( (ret & (BIT_SLOPE_NW|BIT_SOLID)) == (BIT_SLOPE_NW|BIT_SOLID) && (bits & BIT_SLOPE_NW) )
    {
        if ( *x == -1 && *y == 0 )
        {
            *y -= 1;
            return attemptMoveStep(x, y, 0);
        }
        if ( *x == 0 && *y == -1 )
        {
            *x += 1;
            return attemptMoveStep(x, y, 0);
        }
    }
    if ( (ret & (BIT_SLOPE_SE|BIT_SOLID)) == (BIT_SLOPE_SE|BIT_SOLID) && (bits & BIT_SLOPE_SE) )
    {
        if ( *x == 1 && *y == 0 )
        {
            *y -= 1;
            return attemptMoveStep(x, y, 0);
        }
        if ( *x == 0 && *y == 1 )
        {
            *x += 1;
            return attemptMoveStep(x, y, 0);
        }
    }
    if ( (ret & (BIT_SLOPE_SW|BIT_SOLID)) == (BIT_SLOPE_SW|BIT_SOLID) && (bits & BIT_SLOPE_SW) )
    {
        if ( *x == -1 && *y == 0 )
        {
            *y -= 1;
            return attemptMoveStep(x, y, 0);
        }
        if ( *x == 0 && *y == 1 )
        {
            *x += 1;
            return attemptMoveStep(x, y, 0);
        }
    }
    return ret;
}

void
sprite::setAnimation(unsigned int x)
{
    if ( animation == x )
        return;

    if ( x > animations.size() )
        return;

    animation = x;
    frame = 0;

}

int
sprite::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    int ret = 0;

    for (unsigned int i = 0; i < frames[animations[animation].frames[frame]].boxes.size(); i++)
    {
        struct box myb = boxes[frames[animations[animation].frames[frame]].boxes[i]];
        myb.x += this->x;
        myb.y += this->y;

        if ( myb.x > x + w )
            continue;

        if ( myb.y > y + h )
            continue;

        if ( myb.x + myb.w < x )
            continue;

        if ( myb.y + myb.h < y )
            continue;

        if ( bits & BIT_PICKSUP && myb.bits & BIT_PICKUPABLE )
            other->pickUp(this);

        if ( bits & BIT_UNLOCKS && myb.bits & BIT_UNLOCKABLE )
            other->unLock(this);

        if ( bits & BIT_DAMAGEABLE && myb.bits & BIT_DAMAGE )
            other->damage(this);

        if ( bits & BIT_DAMAGE && myb.bits & BIT_DAMAGEABLE )
            damage(other);

        ret |= myb.bits;
    }

    return ret;
}

int
sprite::inFrame()
{
    if ( x+qw > g->c.x && 
         x < g->c.x + g->c.w &&
         y+qh > g->c.y &&
         y < g->c.y + g->c.h )
            return 1;

    return 0;
}
