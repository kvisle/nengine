#ifndef __MEGAMAN_H__
#define __MEGAMAN_H__

#include "sprite.h"
#include "input.h"

class megaman : public sprite {
    public:

        megaman(game *g, int x, int y, int z);
        ~megaman();

        virtual void update();
        virtual void render();
        virtual void input(union ninput in);

    private:

        int jumping;
        int falling;
        int walking;

        int jump_progress;
        int jump_start;

        int moveLeftRight();
        int moveGravity();
        int moveJump();
};

#endif /* __MEGAMAN_H__ */
