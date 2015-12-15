#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include "rapidxml/rapidxml.hpp"
#pragma GCC diagnostic pop

typedef uint32_t TileId;

class Layer
{
public:
    Layer();
    Layer( rapidxml::xml_node<>* node );

    void Load( rapidxml::xml_node<>* layerNode );
    void Save( rapidxml::xml_node<>* mapNode );

    void Resize(uint32_t width, uint32_t height, TileId defaultValue);

    const std::string& GetName() const;
    void SetName( const std::string& name );
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    const TileId& Get(uint32_t x, uint32_t y);
    void Set(uint32_t x, uint32_t y, const TileId& id);

private:
    uint32_t width_;
    uint32_t height_;
    std::string name_;
    std::vector<TileId> data_;
};


#endif /* LAYER_H_INCLUDED */
