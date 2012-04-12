#ifndef __FONT_H__
#define __FONT_H__

#include <string>

class image;
class game;
class camera;

class font {
    public:
        font(image *font, game *g, float w, float h);
        ~font();

        void drawString(std::string str, float x, float y, camera *c);

    private:
        image *tex;
        game *g;

        float w, h;
};

#endif /* __FONT_H__ */
