#ifndef RENDERCOMPONENT_H_INCLUDED
#define RENDERCOMPONENT_H_INCLUDED

#include "component.h"
#include <cstdint>
#include "drawable.h"
#include "render.h"
#include "vector.h"

class RenderComponent : public Component
{
    std::vector<Drawable> drawables_;
public:
    RenderComponent();
    virtual ~RenderComponent() = default;

    void AddDrawable(const Drawable& drawable);
    const std::vector<Drawable>& GetDrawables() const;

    virtual void Update(uint64_t frame);
    virtual RenderComponent* AsRenderComponent();
};

#endif // RENDERCOMPONENT_H_INCLUDED
