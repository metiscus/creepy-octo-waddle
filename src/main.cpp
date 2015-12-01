#include <cstdio>
#include <memory>
#include "object.h"
#include "render.h"
#include "rendercomponent.h"


int main()
{
    std::shared_ptr<Render> render (new Render());

    Drawable yoshi;
    yoshi.SetTexture(1);
    yoshi.SetWidth(64.0);
    yoshi.SetHeight(64.0);

    std::shared_ptr<RenderComponent> render_comp (new RenderComponent());
    render_comp->AddDrawable(yoshi);
    render->AddComponent(render_comp);


    for(int ii=0; ii<300; ++ii)
    {
        render->Draw();
        fprintf(stderr, "%d\n", ii);
    }

    return 0;
}
