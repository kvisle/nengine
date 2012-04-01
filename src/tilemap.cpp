#include <iostream>

#include "resourcemanager.h"
#include "tilemap.h"
#include "tileset.h"
#include "tile.h"
#include "game.h"

tilemap::tilemap(game *g, std::string t, Json::Value json)
       : drawable(g, 0, 0, 0, t)
{
    int i; 

    w = json.get("width", 0).asInt();
    h = json.get("height", 0).asInt();

    tw = json.get("twidth", 0).asInt();
    th = json.get("theight", 0).asInt();

    ts = g->rm->getTileset(json.get("tileset", "tileset.json").asString(), t);

    for ( i = 0 ; json["tilemap"][i].isInt() ;i++ )
    {
        map.push_back(json["tilemap"][i].asInt());
    }

    if ( i != w * h )
    {
        std::cout << "Tilemap is invalid, dimensions incorrect: " << w << "x" << h << " should be " << w * h << " but is " << map.size() << std::endl;
    }

}

tilemap::~tilemap()
{

}

void
tilemap::render()
{
    for (int i = 0; i < w * h; i++)
    {
        ts->getIndex(map[i])->render((i % w) * tw, (i / w) * th, tw, th);
    }
}

void
tilemap::update()
{
    ts->update();
}
