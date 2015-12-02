#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <cstdio>
#include "render.h"
#include "vector.h"

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

#endif // DRAWABLE_H_INCLUDED
