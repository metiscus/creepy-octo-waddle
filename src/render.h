#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <array>
#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Render
{
public:
    enum Layer
    {
        LayerBg,
        LayerFg,
        LayerUi,
        LayerCount
    };

private:
    SDL_Window *window_;
    SDL_GLContext context_;

    std::array<uint32_t, LayerCount> vaos_;
    std::array<uint32_t, LayerCount> vbos_;

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

public:
    Render();
    ~Render();
};

#endif // RENDER_H_INCLUDED
