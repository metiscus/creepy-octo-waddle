#ifndef RENDERCOMPONENT_H_INCLUDED
#define RENDERCOMPONENT_H_INCLUDED

#include "component.h"
#include <cstdint>
#include "vector.h"
#include "render.h"

class Drawable
{
    uint32_t texture_;
    uint32_t frame_;
    float width_;
    float height_;
    Render::Layer layer_;
    Vector2 position_;
    Vector2 offset_;

public:
    Drawable();

    void SetTexture(uint32_t id);
    void SetFrame(uint32_t frame);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    void SetLayer(Render::Layer layer);
    void SetPosition(const Vector2& position);
    void SetOffset(const Vector2& offset);
    uint32_t GetTexture() const;
    uint32_t GetFrame() const;
    float GetWidth() const;
    float GetHeight() const;
    void GetSize(float& width, float& height) const;
    Render::Layer GetLayer() const;
    const Vector2& GetPosition() const;
    const Vector2& GetOffset() const;
};

class RenderComponent : public Component
{
    std::vector<Drawable> drawables_;
public:
    RenderComponent();
    virtual ~RenderComponent() = default;

    void AddDrawable(const Drawable& drawable);
    const std::vector<Drawable>& GetDrawables() const;

    virtual void Update(uint64_t frame);
    virtual RenderComponent* AsRenderComponent();
};

#endif // RENDERCOMPONENT_H_INCLUDED
