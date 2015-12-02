#include "drawable.h"
#include "render.h"
#include <cassert>

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
