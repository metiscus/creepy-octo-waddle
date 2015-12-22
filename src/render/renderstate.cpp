#include "renderstate.h"

RenderState::RenderState()
{
    for(uint32_t ii = 0; ii<MaxTextureUnits; ++ii)
    {
        units_[ii]    = false;
        textures_[ii] = 0;
    }

    blending_ = false;
    program_ = 0;
}

void RenderState::EnableBlending()
{
    blending_ = true;
}

void RenderState::DisableBlending()
{
    blending_ = false;
}

void RenderState::EnableTextureUnit(uint32_t unit)
{
    units_[unit] = true;
}

void RenderState::DisableTextureUnit(uint32_t unit)
{
    units_[unit] = false;
}

void RenderState::SetActiveTexture(uint32_t unit, uint32_t texture)
{
    textures_[unit] = texture;
}

bool RenderState::GetBlending() const
{
    return blending_;
}

bool RenderState::GetTextureUnitActive(uint32_t unit) const
{
    return units_[unit];
}

uint32_t RenderState::GetActiveTexture(uint32_t unit) const
{
    return textures_[unit];
}

void RenderState::SetProgram(uint32_t program)
{
    program_ = program;
}

uint32_t RenderState::GetProgram() const
{
    return program_;
}

void RenderState::ApplyState()
{
    if(blending_)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    for(uint32_t ii = 0; ii<MaxTextureUnits; ++ii)
    {
        glActiveTexture(GL_TEXTURE0+ii);
        if(units_[ii])
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures_[ii]);
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    glUseProgram(program_);
}

void RenderState::ApplyState(const RenderState& state)
{
    if(state.blending_ != blending_)
    {
        if(blending_)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }
    }

    for(uint32_t ii = 0; ii<MaxTextureUnits; ++ii)
    {
        if(units_[ii] != state.units_[ii] || textures_[ii] != state.textures_[ii])
        {
            glActiveTexture(GL_TEXTURE0+ii);
            if(units_[ii])
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, textures_[ii]);
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    }

    if(program_ != state.program_)
    {
        glUseProgram(program_);
    }
}
