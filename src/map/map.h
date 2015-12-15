#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <string>
#include <vector>
#include <memory>

class Layer;
class ObjectGroup;
class Tileset;

class Map
{
public:
    typedef std::shared_ptr<Tileset> TilesetPtr;
    typedef std::shared_ptr<Layer> LayerPtr;
    typedef std::vector<TilesetPtr> TilesetList;
    typedef std::vector<LayerPtr> LayerList;
    typedef std::vector< std::shared_ptr<ObjectGroup> > ObjectGroupList;

    Map();
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
