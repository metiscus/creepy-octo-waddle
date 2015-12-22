#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "../global.h"
#include "../vector.h"
#include "../render.h"
#include "geometry.h"

class Sprite : public Geometry
{
    uint32_t animation_;
    uint32_t frame_rate_;
    uint32_t frame_;
    uint32_t max_frame_;
    float width_;
    float height_;
    int32_t layer_;
    Vector position_;
    Vector offset_;
    bool is_transparent_;
    bool is_dirty_;

public:
    Sprite();
    virtual ~Sprite() = default;

    void SetFrame(uint32_t frame);
    void SetMaxFrame(uint32_t maxframe);
    void SetAnimation(uint32_t animation);
    void SetFrameRate(uint32_t rate);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    void SetLayer(int32_t layer);
    void SetPosition(const Vector& position);
    void SetOffset(const Vector& offset);
    void SetIsTransparent(bool trans);
    uint32_t GetFrame() const;
    uint32_t GetMaxFrame() const;
    uint32_t GetAnimation() const;
    uint32_t GetFrameRate() const;
    float GetWidth() const;
    float GetHeight() const;
    void GetSize(float& width, float& height) const;
    int32_t GetLayer() const;
    const Vector& GetPosition() const;
    const Vector& GetOffset() const;
    bool GetIsTransparent() const;

    virtual void Update(uint64_t dt);
};

#endif
