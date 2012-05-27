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
        tilemap(game *g, std::string mapfile, tileset * ts);
        tilemap(game *g, std::string imgr, std::string t, std::string tileset);
        tilemap(game *g, tileset *ts);

        ~tilemap();

        virtual void render();
        virtual void update();

        void loadMap(Json::Value json, std::string gfx);
        void loadMap(std::string imgr);

        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);

        int w, h;
        int tw, th;

        int checkSlope(int x, int y, int w, int h, int type);
        void getTileBox(int *x, int *y, int *w, int *h, int tileid);
        int getTWH();
        void setTWH(int wh);
        int getW();
        int getH();
        int getTileAt(int x, int y);
        void setTileAt(unsigned int index, int id);

        void addTopRows(int n);
        void addBotRows(int n);
        void addRightCols(int n);
        void addLeftCols(int n);
        void delTopRows(int n);
        void delBotRows(int n);
        void delRightCols(int n);
        void delLeftCols(int n);

        void enableGrid();
        void disableGrid();

        std::string asJSON();

    private:
        tileset *ts;

        std::vector<int> map;
        std::string imgrname;
        int grid;
};

#endif /* __TILEMAP_H__ */
