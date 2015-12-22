#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "../global.h"
#include "renderstate.h"
#include "vbo.h"

class Geometry
{
    int32_t layer_;
    std::shared_ptr<RenderState> state_;
    std::shared_ptr<VBO> vbo_;
public:
    Geometry();
    virtual ~Geometry() = default;
    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    void SetState(std::shared_ptr<RenderState> state);
    void SetLayer(int32_t layer);

    virtual void Update(uint64_t dt) = 0;

    std::shared_ptr<RenderState> GetState() const;
    std::shared_ptr<VBO> GetVBO() const;
    int32_t GetLayer() const;
};

typedef std::shared_ptr<Geometry> GeometryPtr;

#endif
