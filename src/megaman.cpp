#include <cstdio>
#include "bits.h"
#include "megaman.h"
#include "font.h"
#include "game.h"
#include "input.h"

#define ANIMATION_IDLE  0
#define ANIMATION_WALK  1
#define ANIMATION_FALL  3

megaman::megaman(game *g, int x, int y, int z)
       : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("player.json"));
    g->in->subscribe(this);

    jumping = 0;
    falling = 0;
    walking = 0;
    jump_start = 0;
}

megaman::~megaman()
{
    g->in->unsubscribe(this);
}

void
megaman::update()
{
    falling = moveGravity();
    walking = moveLeftRight();
    jumping = moveJump();

    if      ( falling ) setAnimation(ANIMATION_FALL);
    else if ( jumping ) setAnimation(ANIMATION_FALL);
    else if ( walking ) setAnimation(ANIMATION_WALK);
    else                setAnimation(ANIMATION_IDLE);

    g->c.snapAt(x+16, y+16);
}

void
megaman::render()
{
    sprite::render();
}

int
megaman::moveGravity()
{
    if ( jumping )
        return 0;
    int gy = 5, gx = 0;

    return !attemptMove(&gx, &gy, 0);
}

int
megaman::moveLeftRight()
{
    int gx = 0, gy = 0;
    if ( g->in->keys['a'] || g->in->keys['A'] )
    {
        gx -= 2;
    }
    if ( g->in->keys['d'] || g->in->keys['D'] )
    {
        gx += 2;
    }

    if ( gx < 0 )
    {
        flip_x = 1;
    }
    else if ( gx > 0 )
    {
        flip_x = 0;
    }

    if ( gx == 0 )
        return 0;

    return !attemptMove(&gx, &gy, BIT_SLOPE_SW|BIT_SLOPE_SE);
}

int
megaman::moveJump()
{
    int ret;

    if ( falling )
        return 0;

    if ( !g->in->keys[' '] )
        return 0;

    if ( !jumping && jump_start )
    {
        jump_progress = 0;
        jump_start = 0;
    }

    if ( jump_progress >= 20 )
    {
        return 0;
    }

    int gx = 0;
    int gy = -4;

    jump_progress++;

    ret = !attemptMove(&gx, &gy, 0);

    if ( ret == 0 )
        jump_progress = 21;

    return ret;
}

void
megaman::input(union ninput in)
{
    switch(in.type)
    {
    case NINPUT_KEYDOWN:
        if ( in.key.sym == ' ' ) { jump_start = 1; }
        break;
    case NINPUT_KEYUP:
        break;
    }
}
