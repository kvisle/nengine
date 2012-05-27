#include "tileset.h"

#include "resourcemanager.h"
#include "game.h"
#include "image.h"

tileset::tileset(game *g, std::string t, Json::Value json)
{
    this->g = g;
    tex = g->rm->getImage(t);
    texname = t;

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

tileset::tileset(game *g, std::string t)
{
    this->g = g;
    texname = t;
    tex = g->rm->getImage(t);
    tw = 0;
    th = 0;
    deftile = new tile(g, t, 0, 0, 0, 0, 0, tw, th);
    std::cout << "new tileset.\n";
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

int
tileset::getCR()
{
    return tw;
}

void
tileset::setCR(int cr)
{
    std::map<int, tile*>::iterator i;

    tw = th = cr;

    i = tiles.begin();

    while ( i != tiles.end() )
    {
        i->second->setCR(cr);
        i++;
    }
    deftile->setCR(cr);
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

int
tileset::inMap(int index)
{
    if ( tiles.count(index) == 0 )
        return 0;

    return 1;
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

std::string
tileset::asJSON()
{
    int element = 0;
    Json::StyledWriter writer;
//    Json::FastWriter writer;
    Json::Value me;
    std::map<int, tile*>::iterator i;


    me["wc"] = tw;
    me["hc"] = th;

    i = tiles.begin();

    while ( i != tiles.end() )
    {
        me["tiles"][element] = i->second->asJSON();
        i++;
        element++;
    }
    return writer.write(me);
}

void
tileset::newTile(int id)
{
    if ( tiles.count(id) > 0 )
    {
        std::cout << "Tile id " << id << " already exists, not overwriting\n";
        return;
    }

    std::cout << "New tile using texture: " << texname << std::endl;
    tiles[id] = new tile(g, texname, id, 0, 10, 0, 0, tw, th);
}

void
tileset::delTile(int id)
{
    tiles.erase(id);
}

std::string
tileset::getTexName()
{
    return texname;
}
