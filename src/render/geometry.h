#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "../global.h"
#include "renderstate.h"
#include "vbo.h"

class Geometry
{
    std::shared_ptr<RenderState> state_;
    std::shared_ptr<VBO> vbo_;
public:
    Geometry();
    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    void SetState(std::shared_ptr<RenderState> state);

    std::shared_ptr<RenderState> GetState() const;
    std::shared_ptr<VBO> GetVBO() const;
};

#endif
