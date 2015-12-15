#include "tileset.h"
#include "../log.h"

#include <sstream>

Tileset::Tileset()
    : first_gid_(0)
    , last_gid_(0)
    , tile_width_(0)
    , tile_height_(0)
    , name_("")
{
    ;
}

void Tileset::Load(rapidxml::xml_node<> *tsNode)
{
    if (!tsNode)
    {
        Error("(null) node passed in.");
    }
    else
    {
        name_ = tsNode->first_attribute("name")->value();

        std::stringstream ss;
        ss << tsNode->first_attribute("tilewidth")->value();
        ss >> tile_width_;
        ss.clear();

        ss << tsNode->first_attribute("tileheight")->value();
        ss >> tile_height_;
        ss.clear();

        // gid
        ss << tsNode->first_attribute("firstgid")->value();
        ss >> first_gid_;
        ss.clear();

        // get the image
        rapidxml::xml_node<> *imageNode = tsNode->first_node("image");
        if (!imageNode)
        {
            Error("Tileset does not include an image element.");
        }
        else
        {
            image_.filename = imageNode->first_attribute("source")->value();

            ss << imageNode->first_attribute("width")->value();
            ss >> image_.width;
            ss.clear();

            ss << imageNode->first_attribute("height")->value();
            ss >> image_.height;
            ss.clear();

            last_gid_ = first_gid_ + image_.width / tile_width_ * (image_.height / tile_height_);

            Debug("Loaded tileset '%s' (%u x %u) <%s, %u, %u>.", name_.c_str(),
                  tile_width_, tile_height_, image_.filename.c_str(), image_.width,
                  image_.height);
        }
    }
}

void Tileset::GetTileIdRange(uint32_t &low, uint32_t &high) const
{
    low = first_gid_;
    high = last_gid_;
}

bool Tileset::ContainsTile(uint32_t gid) const
{
    return (gid >= first_gid_) && (gid <= last_gid_) && (first_gid_ != last_gid_);
}

Vector Tileset::GetTexCoords(uint32_t gid) const
{
    Vector coords(0., 0.);
    if (!ContainsTile(gid))
    {
        Error("Requested gid %u is not part of tileset %s.", gid, name_.c_str());
    }
    else
    {
        // compute index
        const uint32_t imageIndex = gid - first_gid_;

        // get texture params and xy
        const uint32_t imageWidthInTiles = image_.width / tile_width_;
        const uint32_t row = imageIndex / imageWidthInTiles;
        const uint32_t column = imageIndex % imageWidthInTiles;

        // compute y coordinate
        Vector step((float)tile_width_ / (float)image_.width,
                       (float)tile_height_ / (float)image_.height);
        coords.x = step.x * column;
        coords.y = 1. - step.y * (row + 1);

        Debug("Tile %u => (%f, %f).", gid, coords.x, coords.y);
    }

    return coords;
}

Vector Tileset::GetTexCoordStep() const
{
    Debug("DDD %d %d %d %d", tile_width_, image_.width, tile_height_, image_.height);
    Debug("DDD %f %f", (float)tile_width_ / (float)image_.width,
         (float)tile_height_ / (float)image_.height);
    return Vector((float)tile_width_ / (float)image_.width,
                     (float)tile_height_ / (float)image_.height);
}

Tileset::Image Tileset::GetImage() const
{
    return image_;
}

std::string Tileset::GetName() const
{
    return name_;
}
