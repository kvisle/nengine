#ifndef __TILE_H__
#define __TILE_H__

#include <json/json.h>

#include "drawable.h"

class tile : public drawable {
    public:
        tile(game *g, std::string tex, int x, int b, int i, int fc, int f[64], int tw, int th);
        ~tile();

        void render(float x, float y, float w, float h);
        void update();

        void setCR(int cr);
        void setIndex(int x);
        void addFrame(int id);
        void clearFrames(void);
        int getFrames();
        int getFrame(int id);
        int getInterval();
        void setInterval(int v);

        Json::Value asJSON();

        int index;
        int bits;

    private:
//        int index;
//        int bits;
        int interval;
        int frames_n;
        int frames[64];
        int tw, th;
        int frame;
        int n;
};

#endif /* __TILE_H__ */
