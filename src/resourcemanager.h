#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <string>
#include <map>

class game;
class image;
class tileset;

class resourcemanager {
    public:
        resourcemanager(game *g);
        ~resourcemanager();

        image * getImage(std::string filename);
        tileset * getTileset(std::string filename, std::string tex);

        unsigned char *getPixels(std::string filename);

    private:
        void freeImages();
        void freeTilesets();


        game *g;
        std::map<std::string, image*> img;
        std::map<std::string, tileset*> ts;

};

#endif /* __RESOURCEMANAGER_H__ */
