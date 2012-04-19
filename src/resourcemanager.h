#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <string>
#include <map>

class game;
class image;
class tileset;
class sound;

class resourcemanager {
    public:
        resourcemanager(game *g);
        ~resourcemanager();

        image * getImage(std::string filename);
        image * getImage(std::string filename, int forcereload);
        tileset * getTileset(std::string filename, std::string tex);
        sound * getSound(std::string filename);


        unsigned char *getPixels(std::string filename);

    private:
        void freeImages();
        void freeTilesets();


        game *g;
        std::map<std::string, image*> img;
        std::map<std::string, tileset*> ts;
        std::map<std::string, sound*> snd;

};

#endif /* __RESOURCEMANAGER_H__ */
