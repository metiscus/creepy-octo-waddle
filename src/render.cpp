#include <glad/glad.h>
#include "render.h"
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
    // clean-up textures
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

        // vertex + uv data
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }
}

void Render::LoadTexture(uint32_t id)
{
    // right now the texture names are hard coded
    const char *files[] = {"data/yoshi.png"};
    uint32_t tile_info[] = {32, 32};

    if(textures_.count(id) == 0)
    {
        struct textureinfo info;
        int c;
        uint8_t *data = stbi_load(files[id], (int*)&info.width, (int*)&info.height, (int*)&c, 4);
        info.channels = 4;
        info.tile_width = tile_info[id * 2];
        info.tile_height = tile_info[id * 2 + 1];
        glGenTextures(1, &info.handle);
        glBindTexture(GL_TEXTURE_2D, info.handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        free(data);

        textures_.insert(std::make_pair(id, info));
    }
}
