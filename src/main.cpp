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
    yoshi.SetWidth(150.0);
    yoshi.SetHeight(150.0);
    yoshi.SetLayer(Render::LayerBg);

    std::shared_ptr<RenderComponent> render_comp (new RenderComponent());
    render_comp->AddDrawable(yoshi);
    std::shared_ptr<Object> yoshi_obj(new Object());
    std::shared_ptr<Component> comp(render_comp.get());
    yoshi_obj->SetComponent(RenderComponentId, render_comp);
    yoshi_obj->SetPosition(Vector2(0, 0));
    render->AddComponent(render_comp);

    uint32_t rate = 30;

    bool quit = false;
    while(!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            //If user closes the window
            if (e.type == SDL_QUIT){
                quit = true;
            }
            //If user presses any key
            if (e.type == SDL_KEYDOWN){
                //quit = true;
            }
            //If user clicks the mouse
            if (e.type == SDL_MOUSEBUTTONDOWN){
                //quit = true;
            }
        }

        render->Draw();
        ++rate;
    }

    return 0;
}
