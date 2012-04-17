#ifndef __OSD_H__
#define __OSD_H__

#include "drawable.h"

class osd : public drawable {
    public:
        osd(game *gobj);

        virtual void render();
        virtual void update();

        void drawHealthBar();
        void drawAmmo();
};

#endif /* __OSD_H__ */
