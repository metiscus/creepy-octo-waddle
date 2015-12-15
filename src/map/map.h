#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "../global.h"
#include "../resource.h"

class Layer;
class ObjectGroup;
class Tileset;

// Resource Type is: 234c06b0-68eb-46d2-aca8-ba1f544038d2

class Map : public Resource
{
public:
    static const ResourceType TypeId;

    typedef std::shared_ptr<Tileset> TilesetPtr;
    typedef std::shared_ptr<Layer> LayerPtr;
    typedef std::vector<TilesetPtr> TilesetList;
    typedef std::vector<LayerPtr> LayerList;
    typedef std::vector< std::shared_ptr<ObjectGroup> > ObjectGroupList;

    Map(const ResourceType& id);
    ~Map();

    bool Load(const std::string& filename);

    LayerList GetLayers();
    ObjectGroupList GetObjectGroups();
    TilesetList GetTilesets();

private:
    LayerList       layers_;
    ObjectGroupList object_groups_;
    TilesetList     tilesets_;
};

typedef std::shared_ptr<Map> MapPtr;

#endif /* MAP_H_INCLUDED */
