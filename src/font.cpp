#include "font.h"
#include "image.h"
#include "game.h"
#include "renderer.h"

font::font(image *font, game *g, float w, float h)
{
    tex = font;
    this->g = g;
    this->w = w;
    this->h = h;
}

font::~font()
{

}

void
font::drawString(std::string str, float x, float y)
{
    unsigned int i;

    float xp = x;
    float yp = y;
    float ts = 1.0 / 16.0;

    for(i=0;i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            xp += w;
        }
        else if (str[i] == '\n')
        {
            xp = x;
            yp += h;
        }
        else
        {
            g->r->addQuad(tex->getTexture(),
                          xp, yp, w, h,
                          (str[i] % 16) * ts, (str[i] / 16) * ts, ts, ts);
            xp += w;
        }
    }
}
