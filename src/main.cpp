#include <cstdio>
#include <cmath>
#include <memory>
#include "aicomponent.h"
#include "aiworld.h"
#include "object.h"
#include "physicscomponent.h"
#include "render.h"
#include "rendercomponent.h"
#include "resourcemanager.h"
#include "render/texture.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/log/trivial.hpp>

std::shared_ptr<AIWorld> ai_world;
std::shared_ptr<Render> render;

template<typename Base>
class Wrapper
{
    struct Element
    {
        std::string name_;
        
        Element(const std::string& name)
        {
            name_ = name;
        }
    };

public:
    std::shared_ptr<Resource> operator()(rapidxml::xml_node<> *node)
    {
        
    };
};

void add_yoshi( std::vector<std::shared_ptr<Object> > &objects, int x, int y)
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
    yoshi_obj->SetPosition(Vector(x, y));
    yoshi_obj->SetComponent(AIComponentId, ai_comp);
    yoshi_obj->SetComponent(RenderComponentId, render_comp);
    yoshi_obj->SetComponent(PhysicsComponentId, phy_comp);

    objects.emplace_back(yoshi_obj);
}

int main()
{
    ResourceManager::CreateInstance();
    ResourceLoader imageLoader;
    imageLoader.type = Resource::StringToResourceType("89d94ad2-a732-49de-8ef5-ca9579c000d3");
    imageLoader.load_fun = [](rapidxml::xml_document<> &doc) -> std::shared_ptr<Resource>
    {
        return Texture::Load(doc);
    };
    
    ResourceManager::GetInstance().AddResourceLoader(imageLoader);
    
    ai_world = std::make_shared<AIWorld>();//(new AIWorld());
    render = std::make_shared<Render>();//(new Render());

    std::vector<std::shared_ptr<Object> > objects;   
    
    const float circle_radius = 220.0;
    const int yoshi_count = 32;
    for(int i=0; i<yoshi_count; ++i)
    {
        add_yoshi(objects, 200, 200);
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
                add_yoshi(objects,200, 200);
                //quit = true;
            }
        }

        int ii = 0;
        for(auto obj : objects)
        {
            auto ai_comp = obj->GetComponent<AIComponent>();
            float mytheta = fmod(theta + 3.14159 * 2.0 / (float)objects.size() * (float)(ii++), 2.0*3.14159);

            ai_comp->SetGoalPosition(Vector(circle_radius * cos(mytheta), circle_radius * sin(mytheta)));
            obj->Update(frame);

            auto physics_comp = obj->GetComponent<PhysicsComponent>();
            Vector velocity = physics_comp->GetVelocity();
            velocity.Normalize();

            auto render_comp = obj->GetComponent<RenderComponent>();
            auto drawables = render_comp->GetDrawables();
            if(acos(velocity.Dot(Vector(0.0, 1.0)) <= 0.5 * M_PI_2))
            {
                drawables[0]->SetAnimation(3);
            }
            else if(acos(velocity.Dot(Vector(0.0, -1.0)) <= 0.5 * M_PI_2))
            {
                drawables[0]->SetAnimation(2);
            }
            else if (velocity.x > 0)
            {
                drawables[0]->SetAnimation(0);
            }
            else
            {
                drawables[0]->SetAnimation(1);
            }

            Vector position = obj->GetPosition();
            drawables[0]->SetHeight( 64.0 - 16. * position.y / circle_radius );
            drawables[0]->SetWidth( 64.0 - 16. * position.y / circle_radius );
        }

        render->Draw();

        theta += 0.01;
        theta = fmod(theta, 2*3.14159);
        ++frame;
    }

    return 0;
}

