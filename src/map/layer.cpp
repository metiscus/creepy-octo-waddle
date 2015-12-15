#include "layer.h"
#include "../log.h"
#include <fstream>
#include <sstream>

Layer::Layer()
    : width_(0)
    , height_(0)
    , name_("unnamed layer")
{
    ;
}

Layer::Layer(rapidxml::xml_node<> *node)
{
    Load(node);
}

void Layer::Load(rapidxml::xml_node<> *layerNode)
{
    // parse tag attributes
    name_ = layerNode->first_attribute("name")->value();

    std::stringstream ss;
    ss << layerNode->first_attribute("width")->value();
    ss >> width_;
    ss.clear();

    ss << layerNode->first_attribute("height")->value();
    ss >> height_;
    ss.clear();

    Log::Write(Log::DebugGroup, "layer %s (%dx%d).", name_.c_str(), width_, height_);

    // parse data child
    rapidxml::xml_node<> *dataNode = layerNode->first_node("data");
    if (!dataNode)
    {
        Log::Write(Log::ErrorGroup, "unable to find data node for map layer.");
    }
    else
    {
        // check for encoding types (some are unsupported)
        std::string encodingType = dataNode->first_attribute("encoding")->value();
        if (encodingType == "csv")
        {
            std::string data = dataNode->value();
            ss << data;

            std::string field;
            while (std::getline(ss, field, ','))
            {
                std::stringstream conv(field);
                TileId tileId;
                conv >> tileId;
                data_.push_back(tileId);
            }
        }
        else
        {
            Log::Write(Log::ErrorGroup,"data is encoded using unsupported format %s.",
                  encodingType.c_str());
        }
    }
}

void Layer::Save(rapidxml::xml_node<> *mapNode)
{
    //mb_unimplemented();
}

void Layer::Resize(uint32_t width, uint32_t height, TileId defaultValue)
{
    width_ = width;
    height_ = height;
    data_.clear();
    data_.resize(width, height);
    for (uint32_t ii = 0; ii < width * height; ++ii)
    {
        data_[ii] = defaultValue;
    }
}

const std::string &Layer::GetName() const
{
    return name_;
}

void Layer::SetName(const std::string &name)
{
    name_ = name;
}

uint32_t Layer::GetWidth() const
{
    return width_;
}

uint32_t Layer::GetHeight() const
{
    return height_;
}

const TileId &Layer::Get(uint32_t x, uint32_t y)
{
    return data_[x + y * width_];
}

void Layer::Set(uint32_t x, uint32_t y, const TileId &id)
{
    data_[x + y * width_] = id;
}
