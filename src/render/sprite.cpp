#include "sprite.h"

Sprite::Sprite()
{
    animation_  = 0;
    frame_rate_ = 1;
    frame_      = 0;
    max_frame_  = 1;
    width_      = 0.f;
    height_     = 0.f;
    layer_      = 0;
    is_transparent_ = false;
    is_dirty_   = true;
}

void Sprite::SetFrame(uint32_t frame)
{
    frame_ = frame;
    is_dirty_   = true;
}

void Sprite::SetMaxFrame(uint32_t max_frame)
{
    assert(max_frame != 0);
    max_frame_ = max_frame;
}

void Sprite::SetFrameRate(uint32_t rate)
{
    frame_rate_ = rate;
}

void Sprite::SetAnimation(uint32_t animation)
{
    animation_ = animation;
    is_dirty_   = true;
}

void Sprite::SetWidth(float width)
{
    width_ = width;
    is_dirty_   = true;
}

void Sprite::SetHeight(float height)
{
    height_ = height;
    is_dirty_   = true;
}

void Sprite::SetSize(float width, float height)
{
    width_ = width;
    height_ = height;
    is_dirty_   = true;
}

void Sprite::SetLayer(int32_t layer)
{
    layer_ = layer;
}

void Sprite::SetPosition(const Vector& position)
{
    position_ = position;
}

void Sprite::SetOffset(const Vector& offset)
{
    offset_ = offset;
}

void Sprite::SetIsTransparent(bool trans)
{
    is_transparent_ = trans;
}

uint32_t Sprite::GetAnimation() const
{
    return animation_;
}

uint32_t Sprite::GetFrame() const
{
    return frame_;
}

uint32_t Sprite::GetMaxFrame() const
{
    return max_frame_;
}

uint32_t Sprite::GetFrameRate() const
{
    return frame_rate_;
}

float Sprite::GetWidth() const
{
    return width_;
}

float Sprite::GetHeight() const
{
    return height_;
}

void Sprite::GetSize(float& width, float& height) const
{
    width = width_;
    height = height_;
}

int32_t Sprite::GetLayer() const
{
    return layer_;
}

const Vector& Sprite::GetPosition() const
{
    return position_;
}

const Vector& Sprite::GetOffset() const
{
    return offset_;
}

bool Sprite::GetIsTransparent() const
{
    return is_transparent_;
}

struct triangle_generator
{
    triangle_generator(Vector c, float w, float h)
        : vert(0)
        , center(c)
        , h_width(0.5f * w)
        , h_height(0.5f * h)
    { }

    int vert;
    Vector center;
    float h_width;
    float h_height;

    inline void operator()(std::vector<float>& data)
    {
        switch(vert)
        {
            case 0:
                data.push_back(center.x - h_width);
                data.push_back(center.y - h_height);
                data.push_back(0.0f);
                data.push_back(0.0f);
                break;
            case 1:
                data.push_back(center.x + h_width);
                data.push_back(center.y - h_height);
                data.push_back(1.0f);
                data.push_back(0.0f);
                break;
            case 2:
                data.push_back(center.x - h_width);
                data.push_back(center.y + h_height);
                data.push_back(0.0f);
                data.push_back(1.0f);
                break;
            case 3:
                data.push_back(center.x - h_width);
                data.push_back(center.y + h_height);
                data.push_back(0.0f);
                data.push_back(1.0f);
                break;
            case 4:
                data.push_back(center.x + h_width);
                data.push_back(center.y - h_height);
                data.push_back(1.0f);
                data.push_back(0.0f);
                break;
            case 5:
                data.push_back(center.x + h_width);
                data.push_back(center.y + h_height);
                data.push_back(1.0f);
                data.push_back(1.0f);
                break;
            default:
                assert(false); // idiot!
        }
        ++vert;
    }
};

void Sprite::Update(uint64_t frame)
{
    uint32_t old_frame = frame_;
    if(frame_rate_ > 0 && max_frame_ > 1)
    {
        frame_ = (frame / frame_rate_) % max_frame_;
    }
    else
    {
        frame_ = max_frame_;
    }

    if(frame_ != old_frame)
        is_dirty_ = true;

    // update the vbo
    if(is_dirty_)
    {
        is_dirty_ = false;

        std::vector<float> buffer_data;
        triangle_generator gen(GetPosition(), GetWidth(), GetHeight());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());
        gen(buffer_data);
        buffer_data.push_back(GetAnimation());
        buffer_data.push_back(GetFrame());

        GetVBO()->SetData(&buffer_data[0], buffer_data.size()*sizeof(float));
    }
}
