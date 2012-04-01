#include "tileset.h"

#include "resourcemanager.h"
#include "game.h"
#include "image.h"

tileset::tileset(game *g, std::string t, Json::Value json)
{
    tex = g->rm->getImage(t);

    tw = json.get("wc", 8).asInt();
    th = json.get("hc", 8).asInt();

    int i = 0;
    Json::Value jtile = json["tiles"][i++];
    
    while ( !jtile.isNull() )
    {
        int index      = jtile.get("x", -1).asInt();
        int bits       = jtile.get("b", 0).asInt();
        int interval   = jtile.get("i", 10).asInt();
        int frames_n   = 0;
        int frames[64];

        if ( jtile["frames"].isArray() )
        {
            for ( frames_n = 0; jtile["frames"][frames_n].isInt() ; frames_n++)
            {
                frames[frames_n] = jtile["frames"][frames_n].asInt();
            }
        }
        else
        {
            std::cout << "Tile does not animate.\n";
        }

        if ( tiles.count(index) == 0 )
        {
            tiles[index] = new tile(g, t, index, bits, interval, frames_n, frames, tw, th);
        }
        else {
            std::cout << "Tile id " << (i -1 ) << " already exists, not overwriting\n";
        }

        jtile = json["tiles"][i++];
    }

    deftile = new tile(g, t, 0, 0, 0, 0, 0, tw, th);
}

tileset::~tileset()
{
    std::map<int, tile*>::iterator i;

    i = tiles.begin();

    while ( i != tiles.end() )
    {
        delete i->second;
        i++;
    }

    delete deftile;
}

tile * 
tileset::operator[](int index)
{
    if ( tiles.count(index) == 0 )
    {
        deftile->setIndex(index);
        return deftile;
    }

    return tiles[index];
}

tile *
tileset::getIndex(int index)
{
    if ( tiles.count(index) == 0 )
    {
        deftile->setIndex(index);
        return deftile;
    }

    return tiles[index];
}

void
tileset::update()
{
    std::map<int, tile*>::iterator i;
    i = tiles.begin();

    while ( i != tiles.end() )
    {
        i->second->update();
        i++;
    }
}
