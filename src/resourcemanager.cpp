#include "game.h"
#include "resourcemanager.h"
#include "resource.h"
#include "image.h"
#include "tileset.h"

resourcemanager::resourcemanager(game *g)
{
    this->g = g;
}

void
resourcemanager::freeImages()
{
    std::map<std::string, image*>::iterator i;

    i = img.begin();

    while ( i != img.end() )
    {
        delete i->second;
        i++;
    }
}

void
resourcemanager::freeTilesets()
{
    std::map<std::string, tileset*>::iterator i;

    i = ts.begin();

    while ( i != ts.end() )
    {
        delete i->second;
        i++;
    }
}

resourcemanager::~resourcemanager()
{
    freeTilesets();
    freeImages();
}

image *
resourcemanager::getImage(std::string filename)
{
    if ( !img[filename] ) {
        resource r(filename);
        img[filename] = new image((const unsigned char *) r.getRaw(), r.getLength());
    }

    if ( !img[filename] ) {
        return NULL;
    }

    return img[filename];
}

unsigned char *
resourcemanager::getPixels(std::string filename)
{
    return getImage(filename)->pixels;
}

tileset *
resourcemanager::getTileset(std::string filename, std::string tex)
{
    if ( !ts[filename] ) {
        resource r(filename);
        ts[filename] = new tileset(g, tex, r.getJson());
    }

    if ( !ts[filename] ) {
        return NULL;
    }

    return ts[filename];
}
