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
font::drawString(std::string str, float x, float y, camera *c)
{
    unsigned int i;

    float r = 1.0;
    float g = 1.0;
    float b = 1.0;
    float a = 1.0;

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
        else if (str[i] == '\\')
        {
            if ( i+9 >= str.length() )
                continue;
            char rb[3], gb[3], bb[3], ab[3];

            rb[0] = str[++i]; rb[1] = str[++i]; rb[2] = '\0';
            gb[0] = str[++i]; gb[1] = str[++i]; gb[2] = '\0';
            bb[0] = str[++i]; bb[1] = str[++i]; bb[2] = '\0';
            ab[0] = str[++i]; ab[1] = str[++i]; ab[2] = '\0';

            r = strtol(rb, NULL, 16) / 255.0;
            g = strtol(gb, NULL, 16) / 255.0;
            b = strtol(bb, NULL, 16) / 255.0;
            a = strtol(ab, NULL, 16) / 255.0;

            i++;
        }
        else
        {
            this->g->r->addQuad(tex->getTexture(), 1.0, c,
                          xp, yp, w, h,
                          (str[i] % 16) * ts, (str[i] / 16) * ts, ts, ts,
                          r, g, b, a);
            xp += w;
        }
    }
}
