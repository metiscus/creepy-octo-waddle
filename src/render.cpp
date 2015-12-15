#include <glad/glad.h>
#include "render.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <queue>
#include "log.h"
#include "rendercomponent.h"
#include <string>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma GCC diagnostic pop

#include "resourcemanager.h"
#include "render/texture.h"

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

    SDL_GL_MakeCurrent(window_, context_);
    if(!gladLoadGL()) {
         printf("Something went wrong!\n");
         exit(-1);
    }

    InitGl();
}

Render::~Render()
{
    // clean-up sdl
    // clean-up textures
    // clean-up vao/vbos
    //assert(false); // don't remove until all cleanup tasks finished
}

inline std::string FileToString(const std::string& filename)
{
    std::string ret;

    std::ifstream infile(filename.c_str());
    for(std::string line; std::getline(infile, line); )
    {
        ret += line + std::string("\n");
    }
    return ret;
}

inline uint32_t BuildShader(uint32_t type, const std::string& filename)
{
    Log::Write(Log::RenderGroup, "Loading shader %s", filename.c_str());

    std::string shader_src = FileToString(filename);
    uint32_t shader = glCreateShader(type);
    char *source = strdup(shader_src.c_str());
    glShaderSource(shader, 1, (const GLchar**)&source, nullptr);
    free(source);
    glCompileShader(shader);
    int is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if(!is_compiled)
    {
       int32_t max_length;
       glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
       char *error_message = (char *)malloc(max_length);
       assert(error_message);
       glGetShaderInfoLog(shader, max_length, &max_length, error_message);
       Log::Write(Log::RenderGroup, "begin shader compile error\n%s", error_message);
       Log::Write(Log::RenderGroup, "end shader compile error");
       free(error_message);
       assert(false); // idiot! fix your code.
    }
    return shader;
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

        // point {x,y} uv{s,t}
        uint32_t stride = 4 * sizeof(float) + 2 * sizeof(float);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (void*)(0));
        glEnableVertexAttribArray(0);

        // tile id {x,y}
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 4));
        glEnableVertexAttribArray(1);
    }

    // Activate texture 0
    glActiveTexture(GL_TEXTURE0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // build shader program
    uint32_t vertex_shader = BuildShader(GL_VERTEX_SHADER, "data/shader.vert");
    uint32_t fragment_shader = BuildShader(GL_FRAGMENT_SHADER, "data/shader.frag");
    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    glBindAttribLocation(program_, 0, "position");
    glBindAttribLocation(program_, 1, "tile_id");

    glBindFragDataLocation(program_, 0, "frag_color");

    glLinkProgram(program_);

    int32_t is_linked = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, (int *)&is_linked);
    if(!is_linked)
    {
        int32_t max_length;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &max_length);
        char *error_message = (char *)malloc(max_length);
        assert(error_message);
        glGetProgramInfoLog(program_, max_length, &max_length, error_message);
        Log::Write(Log::RenderGroup, "begin shader link error\n%s", error_message);
        Log::Write(Log::RenderGroup, "end shader link error");
        free(error_message);
        assert(false); // idiot! fix your code.
    }

    glUseProgram(program_);

    // cleanup shader objects
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // gather uniforms and set up view
    tile_size_uniform_   = glGetUniformLocation(program_, "tile_size");

    view_uniform_        = glGetUniformLocation(program_, "view");
    glm::mat4 view       = glm::lookAt(
                                        glm::vec3(0.0, 0.0, 3.0),
                                        glm::vec3(0.0, 0.0, 0.0),
                                        glm::vec3(0.0, 1.0, 0.0) );
    glUniformMatrix4fv(view_uniform_, 1, GL_FALSE, glm::value_ptr(view));

    projection_uniform_  = glGetUniformLocation(program_, "projection");
    glm::mat4 projection = glm::ortho(-400.0, 400.0, -300.0, 300.0, 0.1, 10.0);
    glUniformMatrix4fv(projection_uniform_, 1, GL_FALSE, glm::value_ptr(projection));

    // texture is always texture unit 0
    uint32_t sampler_uniform = glGetUniformLocation(program_, "texture");
    glUniform1i(sampler_uniform, 0);
    glBindSampler(0, sampler_uniform);

    glClearColor(0.f, 0.2f, 0.2f, 0.f);
    glClearDepth(0.0);
    
    ResourceManager::GetInstance().LoadResource( Resource::StringToResourceId("948f16fa-78ed-11e5-8bcf-feff819cdc9f") );
    auto res = ResourceManager::GetInstance().GetResource(Resource::StringToResourceId("948f16fa-78ed-11e5-8bcf-feff819cdc9f"));
    auto tex = std::static_pointer_cast<Texture>(res);

    struct textureinfo info;
    info.channels = 4;
    info.width = tex->GetWidth();
    info.height = tex->GetHeight();
    info.tile_width = 64;
    info.tile_height = 64;
    textures_.insert(std::make_pair(1, info));
}

void Render::LoadTexture(uint32_t id)
{
    assert(id != 0); // 0 is reserved

    // right now the texture names are hard coded
    const char *files[] = { "", "data/yoshi.png"};
    uint32_t tile_info[] = {0, 0, 64, 64};
#if 0
    stbi_set_flip_vertically_on_load(1);

    if(textures_.count(id) == 0)
    {
        struct textureinfo info;
        assert(files[id]);
        Log::Write(Log::RenderGroup, "loading %s as texture %d", files[id], id);
        uint8_t *data = stbi_load(files[id], (int*)&info.width, (int*)&info.height, (int*)&info.channels, 4);
        info.channels = 4;
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
        glGenerateMipmap(GL_TEXTURE_2D);

        textures_.insert(std::make_pair(id, info));
    }
#endif
}

void Render::BindTexture(uint32_t id)
{
    if(id == bound_texture_)
    {
        return;
    }

    if(id == 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        auto res = ResourceManager::GetInstance().GetResource(Resource::StringToResourceId("948f16fa-78ed-11e5-8bcf-feff819cdc9f"));
        std::static_pointer_cast<Texture>(res)->Bind();
#if 0        
        auto itr = textures_.find(id);
        if(itr==textures_.end())
        {
            LoadTexture(id);
        }

        itr = textures_.find(id);
        assert(itr!=textures_.end());
        if(itr!=textures_.end())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, itr->second.handle);
        }
#endif
    }
    bound_texture_ = id;
}

void Render::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // sort components into bins based on layer
    std::array<std::vector<DrawablePtr>, LayerCount> bins;
    for(auto comp : components_)
    {
        RenderComponent *render_comp = comp->AsRenderComponent();
        assert(render_comp); // this should always pass
        const std::vector<DrawablePtr>& drawables = render_comp->GetDrawables();
        for(auto drawable : drawables)
        {
            bins[drawable->GetLayer()].push_back(drawable);
        }
    }

    // allocate a buffer to hold the buffer data
    std::vector<float> buffer_data;
    buffer_data.reserve(6 * components_.size());

    auto fnDrawableLess = [](DrawablePtr left, DrawablePtr right)
    {
        return left->GetPosition().y < right->GetPosition().y;
    };

    std::unordered_map<uint32_t, std::vector<DrawablePtr> > tex_map;
    // render the layers
    for(uint32_t layer_id = LayerBg; layer_id < LayerCount; ++layer_id)
    {
        // sort drawables based on texture
        for(auto drawable : bins[layer_id])
        {
            tex_map[drawable->GetTexture()].emplace_back(drawable);
        }

        // draw each drawable
        for(auto itr : tex_map)
        {
            uint32_t drawable_count = 0;
            buffer_data.clear();
            BindTexture(itr.first);
            assert(textures_[itr.first].tile_width > 0 && textures_[itr.first].tile_height > 0);
            glUniform2f(tile_size_uniform_,
                ((float)textures_[itr.first].tile_width) / ((float)textures_[itr.first].width),
                ((float)textures_[itr.first].tile_height) / ((float)textures_[itr.first].height)
            );

            std::priority_queue<DrawablePtr, std::vector<DrawablePtr>, decltype(fnDrawableLess)> transparents(fnDrawableLess);

            for(auto drawable : itr.second)
            {
                transparents.push(drawable);
            }

            while(!transparents.empty())
            {
                auto drawable = transparents.top();
                drawable_count += drawable->GetGeometry(buffer_data);
                transparents.pop();
            }

            glBindVertexArray(vaos_[layer_id]);
            glBindBuffer(GL_ARRAY_BUFFER, vbos_[layer_id]);
            glBufferData(GL_ARRAY_BUFFER, buffer_data.size() * sizeof(float), &buffer_data[0], GL_STATIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, drawable_count);
        }
    }

    SDL_GL_SwapWindow(window_);
}
