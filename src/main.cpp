#include <cstdio>
#include <cmath>
#include <memory>
#include "aicomponent.h"
#include "aiworld.h"
#include "object.h"
#include "physicscomponent.h"
#include "render.h"
#include "rendercomponent.h"

int main()
{
    std::shared_ptr<AIWorld> ai_world (new AIWorld());
    std::shared_ptr<Render> render (new Render());

    std::vector<std::shared_ptr<Object> > objects;


    const float circle_radius = 250.0;
    const int yoshi_count = 10;
    for(int i=0; i<yoshi_count; ++i)
    {
        DrawablePtr yoshi (new Drawable());
        yoshi->SetTexture(1);
        yoshi->SetWidth(64.0);
        yoshi->SetHeight(64.0);
        yoshi->SetMaxFrame(8);
        yoshi->SetFrameRate(4);
        yoshi->SetLayer(Render::LayerBg);

        std::shared_ptr<RenderComponent> render_comp (new RenderComponent());
        render_comp->AddDrawable(yoshi);
        render->AddComponent(render_comp);

        std::shared_ptr<AIComponent> ai_comp(new AIComponent());
        ai_comp->SetMaxSpeed(3.5);
        ai_world->AddComponent(ai_comp);

        std::shared_ptr<PhysicsComponent> phy_comp(new PhysicsComponent());

        std::shared_ptr<Object> yoshi_obj(new Object());
        yoshi_obj->SetPosition(Vector2(200, 200));
        yoshi_obj->SetComponent(AIComponentId, ai_comp);
        yoshi_obj->SetComponent(RenderComponentId, render_comp);
        yoshi_obj->SetComponent(PhysicsComponentId, phy_comp);

        objects.emplace_back(yoshi_obj);
    }

    float theta = 0.0f;
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

        int ii = 0;
        for(auto obj : objects)
        {
            auto ai_comp = obj->GetComponent<AIComponent>();
            float mytheta = fmod(theta + 3.14159 * 2 / (float)yoshi_count * (float)(ii++), 2*3.14159);

            ai_comp->SetGoalPosition(Vector2(circle_radius * cos(mytheta), circle_radius * sin(mytheta)));
            obj->Update(frame);

            auto render_comp = obj->GetComponent<RenderComponent>();
            auto drawables = render_comp->GetDrawables();
            if(mytheta > 0.0 && mytheta < 3.15159)
            {
                //drawables[0]->SetWidth(-64.0);
                drawables[0]->SetAnimation(1);
            }
            else
            {
                //drawables[0]->SetWidth(64.0);
                drawables[0]->SetAnimation(0);
            }
        }

        render->Draw();

        theta += 0.01;
        theta = fmod(theta, 2*3.14159);
        ++frame;
    }

    return 0;
}
