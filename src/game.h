#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "camera.h"

class renderer;
class resourcemanager;
class image;
class drawable;
class font;
class input;

class game {
    public:
        game();
        ~game();

        void render();
        int update();

        int collides(float x, float y, float w, float h, drawable *me);

        renderer *r;
        resourcemanager *rm;
        input *in;

        camera c;
        font *f;

    private:
        std::vector<drawable*> assets;
        int updateno;
};

#endif /* __GAME_H__ */
