#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <vector>

#include "json/json.h"

#include "drawable.h"

class tileset;
class game;

class tilemap : public drawable {
    public:
        tilemap(game *g, std::string t, Json::Value json);
        ~tilemap();

        virtual void render();
        virtual void update();

        int w, h;
        int tw, th;

    private:
        tileset *ts;

        std::vector<int> map;
};

#endif /* __TILEMAP_H__ */
