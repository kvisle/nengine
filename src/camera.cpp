#include "camera.h"
#include "sprite.h"

camera::camera(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}


void
camera::snapAt(int x, int y)
{
    this->x = (x / w) * w;
    this->y = (y / h) * h;
}

void
camera::centerAt(int x, int y)
{
    this->x = x - (w / 2);
    this->y = y - (h / 2);
}

void
camera::keepInFrame(sprite *s, int margx, int margy)
{
    if ( s->x < this->x + margx )
        this->x = s->x - margx;

    if ( s->x + s->qw > this->x + this->w - margx )
        this->x = s->x + s->qw + margx - this->w;

    if ( s->y < this->y + margy )
        this->y = s->y - margy;

    if ( s->y + s->qh > this->y + this->h - margy )
        this->y = s->y + s->qh + margy - this->h;

}
