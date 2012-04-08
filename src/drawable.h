#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <string>

class game;
class image;

class drawable {
    public:
        drawable(game *game, int x, int y, int z, std::string texture);
        ~drawable();

        virtual void render();
        virtual void update();
        virtual int collidesWith(float x, float y, float w, float h, drawable *other);


        game *g;
        int x, y, z;

        image *tex;

    private:
        // Does this even make sense?

};

#endif /* __DRAWABLE_H__ */
