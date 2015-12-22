#include "geometry.h"

Geometry::Geometry()
{
    state_ = std::make_shared<RenderState>();
    vbo_ = std::make_shared<VBO>(VBO::ArrayBuffer);
    layer_      = 0;
}

void Geometry::SetState(std::shared_ptr<RenderState> state)
{
    state_ = state;
}

void Geometry::SetLayer(int32_t layer)
{
    layer_ = layer;
}

std::shared_ptr<RenderState> Geometry::GetState() const
{
    return state_;
}

std::shared_ptr<VBO> Geometry::GetVBO() const
{
    return vbo_;
}

int32_t Geometry::GetLayer() const
{
    return layer_;
}
