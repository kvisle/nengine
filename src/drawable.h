#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <string>

#include "input.h"

class game;
class image;

class drawable {
    public:
        drawable(game *game, int x, int y, int z, std::string texture);
        ~drawable();

        virtual void render();
        virtual void update();
        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);
        virtual void input(union ninput in);
        virtual void pickUp(drawable *d);
        virtual void unLock(drawable *d);
        virtual void damage(drawable *d);
        virtual void kill();

        virtual int identify();
        virtual int inFrame();

        game *g;
        int x, y, z;

        image *tex;

        void remove();

        int removeme;

    private:
        // Does this even make sense?

};

#endif /* __DRAWABLE_H__ */
