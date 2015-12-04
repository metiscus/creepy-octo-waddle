#include "drawable.h"
#include "render.h"
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <rapidxml/rapidxml.hpp>
#pragma GCC diagnostic pop

Drawable::Drawable()
{
    texture_    = 0;
    animation_  = 0;
    frame_rate_ = 1;
    frame_      = 0;
    max_frame_  = 1;
    width_      = 0.f;
    height_     = 0.f;
    layer_      = Render::LayerDefault;
    is_transparent_ = false;
}

inline std::string FileToString(const std::string& filename)
{
    std::string ret;

    std::ifstream infile(filename.c_str());
    for(std::string line; std::getline(infile, line); )
    {
        ret += line + std::string("\n");
    }
    return ret;
}

DrawablePtr Drawable::LoadFile(const std::string& filename)
{
    DrawablePtr drawable(new Drawable());
    using namespace rapidxml;

    std::string xml_text_str = FileToString(filename);
    std::vector<char> xml_text;
    xml_text.resize(xml_text_str.length());
    strcpy(&xml_text[0], xml_text_str.c_str());

    xml_document<> doc;
    doc.parse<0>(&xml_text[0]);

    // read the document and populate the fields of the drawable here
    //http://rapidxml.sourceforge.net/manual.html

    return drawable;
}

void Drawable::SetTexture(uint32_t id)
{
    assert(id != 0);
    texture_ = id;
}

void Drawable::SetFrame(uint32_t frame)
{
    frame_ = frame;
}

void Drawable::SetMaxFrame(uint32_t max_frame)
{
    assert(max_frame != 0);
    max_frame_ = max_frame;
}

void Drawable::SetFrameRate(uint32_t rate)
{
    frame_rate_ = rate;
}

void Drawable::SetAnimation(uint32_t animation)
{
    animation_ = animation;
}

void Drawable::SetWidth(float width)
{
    width_ = width;
}

void Drawable::SetHeight(float height)
{
    height_ = height;
}

void Drawable::SetSize(float width, float height)
{
    width_ = width;
    height_ = height;
}

void Drawable::SetLayer(Render::Layer layer)
{
    layer_ = layer;
}

void Drawable::SetPosition(const Vector2& position)
{
    position_ = position;
}

void Drawable::SetOffset(const Vector2& offset)
{
    offset_ = offset;
}

void Drawable::SetIsTransparent(bool trans)
{
    is_transparent_ = trans;
}

uint32_t Drawable::GetTexture() const
{
    return texture_;
}

uint32_t Drawable::GetAnimation() const
{
    return animation_;
}

uint32_t Drawable::GetFrame() const
{
    return frame_;
}

uint32_t Drawable::GetMaxFrame() const
{
    return max_frame_;
}

uint32_t Drawable::GetFrameRate() const
{
    return frame_rate_;
}

float Drawable::GetWidth() const
{
    return width_;
}

float Drawable::GetHeight() const
{
    return height_;
}

void Drawable::GetSize(float& width, float& height) const
{
    width = width_;
    height = height_;
}

Render::Layer Drawable::GetLayer() const
{
    return layer_;
}

const Vector2& Drawable::GetPosition() const
{
    return position_;
}

const Vector2& Drawable::GetOffset() const
{
    return offset_;
}

bool Drawable::GetIsTransparent() const
{
    return is_transparent_;
}

void Drawable::Update(uint64_t frame)
{
    if(frame_rate_ > 0 && max_frame_ > 1)
    {
        frame_ = (frame / frame_rate_) % max_frame_;
    }
    else
    {
        frame_ = max_frame_;
    }
}
