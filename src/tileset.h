#ifndef __TILESET_H__
#define __TILESET_H__

#include <map>
#include <json/json.h>

#include "tile.h"

class game;
class image;

class tileset {
    public:
        tileset(game *g, std::string t, Json::Value json);
        ~tileset();

        void update();

        tile * operator[](int index);
        tile * getIndex(int index);

    private:
        float tw, th;        
        image *tex;

        std::map<int, tile*> tiles;
        tile * deftile;

};

#endif /* __TILESET_H__ */
