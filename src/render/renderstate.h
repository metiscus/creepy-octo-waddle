#ifndef RENDERSTATE_H_INCLUDED
#define RENDERSTATE_H_INCLUDED

#include "../global.h"

constexpr uint32_t MaxTextureUnits = GL_MAX_TEXTURE_UNITS;

class RenderState
{
    std::array<uint32_t, MaxTextureUnits> textures_;
    std::array<bool, MaxTextureUnits> units_;
    uint32_t program_;
    bool blending_;

public:
    RenderState();
    void EnableBlending();
    void DisableBlending();
    void EnableTextureUnit(uint32_t unit);
    void DisableTextureUnit(uint32_t unit);
    void SetActiveTexture(uint32_t unit, uint32_t texture);

    bool GetBlending() const;
    bool GetTextureUnitActive(uint32_t unit) const;
    uint32_t GetActiveTexture(uint32_t unit) const;

    void SetProgram(uint32_t program);
    uint32_t GetProgram() const;

    void ApplyState();
    void ApplyState(const RenderState& state);
};

#endif
