#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include "drawable.h"

class overlay : public drawable {
    public:
        overlay(game *g);
        virtual void render();

};

#endif /* __OVERLAY_H__ */
