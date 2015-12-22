#include "geometry.h"

Geometry::Geometry()
{
    state_ = std::make_shared<RenderState>();
    vbo_ = std::make_shared<VBO>(VBO::ArrayBuffer);
}

void Geometry::SetState(std::shared_ptr<RenderState> state)
{
    state_ = state;
}

std::shared_ptr<RenderState> Geometry::GetState() const
{
    return state_;
}

std::shared_ptr<VBO> Geometry::GetVBO() const
{
    return vbo_;
}
