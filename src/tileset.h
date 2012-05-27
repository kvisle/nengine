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
        tileset(game *g, std::string t);
        ~tileset();

        void setCR(int cr);
        int getCR();

        void update();
        void newTile(int id);
        void delTile(int id);

        tile * operator[](int index);
        tile * getIndex(int index);
        int inMap(int index);

        std::string asJSON();
        std::string getTexName();

    private:
        float tw, th;        
        image *tex;

        std::map<int, tile*> tiles;
        tile * deftile;
        game * g;
        std::string texname;

};

#endif /* __TILESET_H__ */
