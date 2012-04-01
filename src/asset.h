#ifndef __ASSET_H__
#define __ASSET_H__

class game;
class image;

class asset {
    public:
        asset(game *game);
        asset(game *game, int x, int y, int z);

        virtual void render();

    private:
        int x, y, z;

        game *g;
        image *texture;

};

#endif /* __ASSET_H__ */
