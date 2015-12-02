#include <cstdio>
#include <cmath>
#include <memory>
#include "aicomponent.h"
#include "aiworld.h"
#include "object.h"
#include "render.h"
#include "rendercomponent.h"

int main()
{
    std::shared_ptr<AIWorld> ai_world (new AIWorld());
    std::shared_ptr<Render> render (new Render());

    DrawablePtr yoshi (new Drawable());
    yoshi->SetTexture(1);
    yoshi->SetWidth(100.0);
    yoshi->SetHeight(100.0);
    yoshi->SetLayer(Render::LayerBg);

    std::shared_ptr<RenderComponent> render_comp (new RenderComponent());
    render_comp->AddDrawable(yoshi);
    render->AddComponent(render_comp);

    std::shared_ptr<AIComponent> ai_comp(new AIComponent());
    ai_comp->SetGoalPosition(Vector2(120.0, 120.0));
    ai_comp->SetMaxSpeed(1.);
    ai_world->AddComponent(ai_comp);

    std::shared_ptr<Object> yoshi_obj(new Object());
    yoshi_obj->SetPosition(Vector2(0, 0));
    yoshi_obj->SetComponent(AIComponentId, ai_comp);
    yoshi_obj->SetComponent(RenderComponentId, render_comp);


    float theta = 0.0f;
    uint32_t rate = 6;
    uint64_t frame = 0;

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

        ai_comp->SetGoalPosition(Vector2(120.0 * cos(theta), 120.0 * sin(theta)));

        yoshi_obj->Update(frame);
        yoshi->SetFrame((frame / rate) % 8);
        render->Draw();
        fprintf(stderr, "frame: %u\n", (frame / rate) % 8);

        theta += 0.01;

        theta = fmod(theta, 2*3.14159);
        if(theta > 0.0 && theta < 3.15159)
        {
            yoshi->SetWidth(-100.0);
        }
        else
        {
            yoshi->SetWidth(100.0);
        }

        ++frame;
    }

    return 0;
}
