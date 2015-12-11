#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <array>
#include "component.h"
#include "componentcontainer.h"
#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class RenderComponent;

class Render : public ComponentContainer<RenderComponent>
{
public:
    enum Layer
    {
        LayerDefault = 0,
        LayerBg = LayerDefault,
        LayerFg,
        //LayerUi,
        LayerCount
    };

private:
    SDL_Window *window_;
    SDL_GLContext context_;

    std::array<uint32_t, LayerCount> vaos_;
    std::array<uint32_t, LayerCount> vbos_;

    uint32_t bound_texture_;
    uint32_t program_;
    uint32_t view_uniform_;
    uint32_t projection_uniform_;
    uint32_t tile_size_uniform_;

    struct textureinfo
    {
        uint32_t handle;
        uint32_t width;
        uint32_t height;
        uint32_t channels;
        uint32_t tile_width;
        uint32_t tile_height;
    };

    std::unordered_map<uint32_t, textureinfo> textures_;

    void InitGl();
    void LoadTexture(uint32_t id);
    void BindTexture(uint32_t id);

public:
    Render();
    ~Render();

    void Draw();
};

#endif // RENDER_H_INCLUDED
