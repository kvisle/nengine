#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <vector>

#include "json/json.h"

#include "drawable.h"

class tileset;
class game;
class image;

class tilemap : public drawable {
    public:
        tilemap(game *g, std::string t, Json::Value json);
        tilemap(game *g, std::string imgr, std::string t, std::string tileset);

        ~tilemap();

        virtual void render();
        virtual void update();

        void loadMap(std::string imgr);

        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);

        int w, h;
        int tw, th;

        int checkSlope(int x, int y, int w, int h, int type);
        void getTileBox(int *x, int *y, int *w, int *h, int tileid);


    private:
        tileset *ts;

        std::vector<int> map;
        std::string imgrname;
};

#endif /* __TILEMAP_H__ */
