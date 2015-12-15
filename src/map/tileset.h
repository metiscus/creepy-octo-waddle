#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED

#include "../global.h"
#include "../vector.h"

class Tileset
{
public:
    struct Image
    {
        Image() {
            filename = "";
            width = 0;
            height = 0;
        }
        std::string filename;
        uint32_t width;
        uint32_t height;
    };

    Tileset();

    void Load(rapidxml::xml_node<>* tsNode);

    void GetTileIdRange(uint32_t &low, uint32_t &high) const;
    bool ContainsTile(uint32_t gid) const;
    Vector GetTexCoords(uint32_t gid) const;
    Vector GetTexCoordStep() const;
    Image GetImage() const;

    std::string GetName() const;

    uint32_t GetTileWidth() const;
    uint32_t GetTileHeight() const;

private:
    uint32_t first_gid_;
    uint32_t last_gid_;
    uint32_t tile_width_;
    uint32_t tile_height_;
    std::string name_;

    Image image_;
};

#endif /* TILESET_H_INCLUDED */
