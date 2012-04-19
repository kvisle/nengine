#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>
#include <vector>

#include <json/json.h>

#include "drawable.h"

class game;

struct box {
    int x, y, w, h, bits;
};

struct animation {
    unsigned int loop;
    unsigned int next;
    unsigned int interval;
    std::vector<int> frames;
};

struct frame {
    float x, y, w, h, ox, oy;
    std::vector<int> boxes;
};

class sprite : public drawable {
    public:
        sprite(game *g, int x, int y, int z, std::string tex, Json::Value spec);
        sprite(game *g, int x, int y, int z, std::string tex);

        ~sprite();

        virtual void render();
        virtual void renderBox();
        virtual void update();

        int attemptMove(int *x, int *y, int bits);
        int attemptMoveStep(int *x, int *y, int bits);

        void loadJson(Json::Value spec);
        void loadJson(std::string res);
    
        float qw, qh;

        void printInfo();
        void setAnimation(unsigned int x);

        unsigned int frame, intcount, animation;

        int flip_x, flip_y;

    private:
        std::vector<struct box> boxes;
        std::vector<struct animation> animations;
        std::vector<struct frame> frames;

};

#endif /* __SPRITE_H__ */
