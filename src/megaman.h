#ifndef __MEGAMAN_H__
#define __MEGAMAN_H__

#include "sprite.h"

class megaman : public sprite {
    public:

        megaman(game *g, int x, int y, int z);
        ~megaman();

        virtual void update();
        virtual void render();

    private:

        void moveGravity();
};

#endif /* __MEGAMAN_H__ */
