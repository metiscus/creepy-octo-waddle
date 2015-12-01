#include "rendercomponent.h"
#include "object.h"

Drawable::Drawable()
    : texture_(0)
    , frame_(0)
    , width_(0)
    , height_(0)
    , layer_(Render::LayerDefault)
{
    ;
}

void Drawable::SetTexture(uint32_t id)
{
    texture_ = id;
}

void Drawable::SetFrame(uint32_t frame)
{
    frame_ = frame;
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

uint32_t Drawable::GetFrame() const
{
    return frame_;
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

//////////[ Render Component]//////////
RenderComponent::RenderComponent()
{
    ;
}

void RenderComponent::AddDrawable(const Drawable& drawable)
{
    drawables_.emplace_back(drawable);
}

const std::vector<Drawable>& RenderComponent::GetDrawables() const
{
    return drawables_;
}

void RenderComponent::Update(uint64_t frame)
{
    (void)frame;
    const Vector2& position = GetParent()->GetPosition();
    for(auto drawable : drawables_)
    {
        drawable.SetPosition(position);
    }
}

RenderComponent* RenderComponent::AsRenderComponent()
{
    return this;
}
