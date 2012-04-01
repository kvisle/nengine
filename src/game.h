#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "camera.h"

class renderer;
class resourcemanager;
class image;
class drawable;

class game {
    public:
        game();
        ~game();

        void render();
        int update();

        renderer *r;
        resourcemanager *rm;

        camera c;


    private:
        std::vector<drawable*> assets;
        int updateno;
};

#endif /* __GAME_H__ */
