#include "megaman.h"
#include "font.h"
#include "game.h"
#include "input.h"

#define ANIMATION_IDLE  0
#define ANIMATION_WALK  1
#define ANIMATION_FALL  3

megaman::megaman(game *g, int x, int y, int z)
       : sprite(g, x, y, z, "megaman.png")
{
    loadJson(std::string("sprite.json"));

    jumping = 0;
    falling = 0;
    walking = 0;
}

megaman::~megaman()
{

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
}

void
megaman::render()
{
    sprite::render();

    g->f->drawString("megaman", x - 24, y - 24);
}

int
megaman::moveGravity()
{
    if ( jumping )
        return 0;
    int gy = 8, gx = 0;

    return !attemptMove(&gx, &gy);
}

int
megaman::moveLeftRight()
{
    int gx = 0, gy = 0;
    if ( g->in->keys['a'] || g->in->keys['A'] )
    {
        gx -= 4;
    }
    if ( g->in->keys['d'] || g->in->keys['D'] )
    {
        gx += 4;
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

    return !attemptMove(&gx, &gy);
}

int
megaman::moveJump()
{
    if ( falling )
        return 0;

    if ( !g->in->keys[' '] )
        return 0;

    if ( !jumping )
    {
        jump_progress = 0;
    }

    if ( jump_progress >= 20 )
    {
        return 0;
    }

    int gx = 0;
    int gy = -8;

    jump_progress++;

    return !attemptMove(&gx, &gy);
}
