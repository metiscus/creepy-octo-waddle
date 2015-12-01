#include <glad/glad.h>
#include "render.h"
#include "rendercomponent.h"
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Render::Render()
    : window_(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetSwapInterval(1); // attempt to use v-sync
    window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    assert(window_ != nullptr);
    context_ = SDL_GL_CreateContext(window_);
    assert(context_ != nullptr);

    InitGl();
}

Render::~Render()
{
    // clean-up sdl
    // clean-up textures
    // clean-up vao/vbos
    assert(false);
}

void Render::InitGl()
{
    for(uint32_t ii=0; ii<LayerCount; ++ii)
    {
        // generate the vao + vbo for each layer
        glGenVertexArrays(1, &vaos_[ii]);
        glBindVertexArray(vaos_[ii]);
        glGenBuffers(1, &vbos_[ii]);
        glBindBuffer(GL_ARRAY_BUFFER, vbos_[ii]);

        // center, width, height
        uint32_t stride = 4 * sizeof(float) + 2 * sizeof(uint32_t);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (void*)(0));
        glEnableVertexAttribArray(0);

        // texture id, tile id
        glVertexAttribPointer(1, 2, GL_UNSIGNED_INT, GL_FALSE, stride, (void*)(sizeof(float) * 4));
        glEnableVertexAttribArray(1);
    }
}

void Render::LoadTexture(uint32_t id)
{
    assert(id != 0); // 0 is reserved

    // right now the texture names are hard coded
    const char *files[] = { "", "data/yoshi.png"};
    uint32_t tile_info[] = {0, 0, 32, 32};

    if(textures_.count(id) == 0)
    {
        struct textureinfo info;
        assert(files[id]);
        uint8_t *data = stbi_load(files[id], (int*)&info.width, (int*)&info.height, (int*)&info.channels, 0);
        assert(data);
        info.tile_width = tile_info[id * 2];
        info.tile_height = tile_info[id * 2 + 1];
        glGenTextures(1, &info.handle);
        glBindTexture(GL_TEXTURE_2D, info.handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        assert(info.channels == 3 || info.channels==4);
        if(info.channels==3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        free(data);

        textures_.insert(std::make_pair(id, info));
    }
}

void Render::BindTexture(uint32_t id)
{
    if(id == bound_texture_)
    {
        return;
    }

    if(id == 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        auto itr = textures_.find(id);
        assert(itr!=textures_.end());
        if(itr!=textures_.end())
        {
            glBindTexture(GL_TEXTURE_2D, itr->second.handle);
        }
    }
    bound_texture_ = id;
}

void Render::Draw()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // sort components into bins based on layer
    std::array<std::vector<Drawable>, LayerCount> bins;
    for(auto comp : components_)
    {
        RenderComponent *render_comp = comp->AsRenderComponent();
        assert(render_comp); // this should always pass
        const std::vector<Drawable>& drawables = render_comp->GetDrawables();
        for(auto drawable : drawables)
        {
            bins[drawable.GetLayer()].emplace_back(drawable);
        }
    }

    // allocate a buffer to hold the buffer data
    std::vector<float> buffer_data;
    buffer_data.reserve(6 * components_.size());

    std::unordered_map<uint32_t, std::vector<Drawable*> > tex_map;
    // render the layers
    for(uint32_t layer_id = LayerBg; layer_id < LayerCount; ++layer_id)
    {
        // sort drawables based on texture
        for(auto drawable : bins[layer_id])
        {
            tex_map[drawable.GetTexture()].emplace_back(&drawable);
        }

        // draw each drawable
        for(auto itr : tex_map)
        {
            buffer_data.clear();
            BindTexture(itr.first);
            for(auto drawable : itr.second)
            {
                const Vector2& position = drawable->GetPosition();
                buffer_data.push_back(position.x);
                buffer_data.push_back(position.y);
                buffer_data.push_back(drawable->GetWidth());
                buffer_data.push_back(drawable->GetHeight());
                buffer_data.push_back(drawable->GetFrame());
            }
        }
    }

    SDL_GL_SwapWindow(window_);
}
