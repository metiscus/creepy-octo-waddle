#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <cstdio>
#include <string>
#include <memory>
#include "render.h"
#include "vector.h"

class Drawable;

typedef std::shared_ptr<Drawable> DrawablePtr;

class Drawable
{
    uint32_t texture_;
    uint32_t animation_;
    uint32_t frame_rate_;
    uint32_t frame_;
    uint32_t max_frame_;
    float width_;
    float height_;
    Render::Layer layer_;
    Vector position_;
    Vector offset_;
    bool is_transparent_;

public:
    Drawable();
    virtual ~Drawable() = default;

    static DrawablePtr LoadFile(const std::string& filename);

    void SetTexture(uint32_t id);
    void SetFrame(uint32_t frame);
    void SetMaxFrame(uint32_t maxframe);
    void SetAnimation(uint32_t animation);
    void SetFrameRate(uint32_t rate);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    void SetLayer(Render::Layer layer);
    void SetPosition(const Vector& position);
    void SetOffset(const Vector& offset);
    void SetIsTransparent(bool trans);
    uint32_t GetTexture() const;
    uint32_t GetFrame() const;
    uint32_t GetMaxFrame() const;
    uint32_t GetAnimation() const;
    uint32_t GetFrameRate() const;
    float GetWidth() const;
    float GetHeight() const;
    void GetSize(float& width, float& height) const;
    Render::Layer GetLayer() const;
    const Vector& GetPosition() const;
    const Vector& GetOffset() const;
    bool GetIsTransparent() const;

    void Update(uint64_t frame);

    virtual int32_t GetGeometry(std::vector<float>& vbo);
};

#endif // DRAWABLE_H_INCLUDED
