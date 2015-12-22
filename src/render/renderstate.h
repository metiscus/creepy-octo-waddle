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

typedef std::shared_ptr<RenderState> RenderStatePtr;

inline bool operator< (const RenderState& lhs, const RenderState& rhs)
{
    if(lhs.GetBlending() && !rhs.GetBlending())
        return true;

    if(lhs.GetProgram() != rhs.GetProgram())
    {
        return lhs.GetProgram() < rhs.GetProgram();
    }

    for(uint32_t ii=0; ii<MaxTextureUnits; ++ii)
    {
        if(lhs.GetActiveTexture(ii) != rhs.GetActiveTexture(ii))
        {
            return lhs.GetActiveTexture(ii) < rhs.GetActiveTexture(ii);
        }
    }
}

inline bool operator< (const RenderStatePtr& lhs, const RenderStatePtr& rhs)
{
    if(!rhs && lhs)
        return true;
    else if(rhs && !lhs)
        return false;
    else
        return lhs.get() < rhs.get();
}

#endif
