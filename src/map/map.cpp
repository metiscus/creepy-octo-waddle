#include "map.h"
#include "layer.h"
#include "objectgroup.h"
#include "tileset.h"
#include "../resource.h"
#include "../log.h"

const ResourceType Map::TypeId =
{
0x23, 0x4c, 0x06, 0xb0,
0x68, 0xeb,
0x46, 0xd2,
0xac, 0xa8,
0xba, 0x1f, 0x54, 0x40, 0x38, 0xd2
};

Map::Map(const ResourceType& id)
    : Resource(id, TypeId)
{
    ;
}

Map::~Map()
{
    ;
}

bool Map::Load(const std::string &filename)
{
    rapidxml::file<> mapfile(filename.c_str());

    rapidxml::xml_document<> doc;
    doc.parse<0>(mapfile.data());

    // get map node
    rapidxml::xml_node<> *map = doc.first_node("map");

    if (!map)
    {
        Error("%s did not contain a valid map.", filename.c_str());
        return false;
    }

    // parse out tile sets
    for (rapidxml::xml_node<> *itr = map->first_node("tileset"); itr;
         itr = itr->next_sibling("tileset"))
    {
        std::shared_ptr<Tileset> tsPtr(new Tileset());
        tsPtr->Load(itr);
        tilesets_.push_back(tsPtr);
    }

    // parse out layers
    for (rapidxml::xml_node<> *itr = map->first_node("layer"); itr;
         itr = itr->next_sibling("layer"))
    {
        std::shared_ptr<Layer> layerPtr(new Layer(itr));
        if (layerPtr.get() != NULL)
        {
            layers_.push_back(layerPtr);
        }
    }

    // parse out object groups
    for (rapidxml::xml_node<> *itr = map->first_node("objectgroup"); itr;
         itr = itr->next_sibling("objectgroup"))
    {
#if 0
        std::shared_ptr<ObjectGroup> objgrpPtr(new ObjectGroup(itr));
        if (objgrpPtr.get() != NULL)
        {
            object_groups_.push_back(objgrpPtr);
        }
#endif
    }

    return true;
}

Map::LayerList Map::GetLayers()
{
    return layers_;
}

Map::ObjectGroupList Map::GetObjectGroups()
{
    return object_groups_;
}

Map::TilesetList Map::GetTilesets()
{
    return tilesets_;
}
