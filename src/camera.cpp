#include "camera.h"

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
