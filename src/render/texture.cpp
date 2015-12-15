#include "../global.h"

#include "../log.h"
#include "../stb_image.h"
#include "texture.h"

const ResourceType Texture::TypeId =
{
    0x89, 0xd9, 0x4a, 0xd2,
    0xa7, 0x32,
    0x49, 0xde,
    0x8e, 0xf5,
    0xca, 0x95, 0x79, 0xc0, 0x00, 0xd3
};

Texture::Texture(const ResourceId& id)
    : Resource(id, TypeId)
    , is_dirty_(false)
    , generate_mipmaps_(true)
{
    glGenTextures(1, &texture_);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_);
}

bool Texture::LoadFromFile(const char *filename)
{
    if (!filename)
    {
        Log::Write(Log::RenderGroup, "Texture: null filename.");
        return false;
    }

    int c, width, height;
    const GLubyte *loadedData = stbi_load(filename, &width, &height, &c, 4);
    if (loadedData != NULL)
    {
        is_dirty_ = true;

        Log::Write(Log::RenderGroup, "Texture: loaded %s (%d x %d) with %d channels.", filename, width, height, c);
        Log::Write(Log::RenderGroup, "Texture: forcing RGBA.");

        // copy data to internal buffer and release
        data_.resize(width, height, 4, TextureData::Texel_U8, loadedData);
        stbi_image_free((void *)loadedData);

        // some file extensions require flipping
        std::string extension = filename;
        size_t itr = extension.rfind(".");
        if (itr != std::string::npos)
        {
            extension = extension.substr(itr + 1, extension.length() - itr);
            Log::Write(Log::RenderGroup, "Texture: file is of type %s.", extension.c_str());
            if (extension != "bmp")
            {
                // textureVFlip(mData.getData(), width, height);
                data_.flipImageVertical();
                Log::Write(Log::RenderGroup, "Texture: inverting scanlines.");
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        Log::Write(Log::RenderGroup, "Texture: Error loading %s. (%s).", filename, stbi_failure_reason());
        return false;
    }

    return true;
}

bool Texture::SetFromData(const TextureData &data)
{
    is_dirty_ = true;
    data_ = data;
    return true;
}

TextureData &Texture::GetDataRW()
{
    is_dirty_ = true; // automatically mark as dirty
    return data_;
}

const TextureData &Texture::GetDataRO() const
{
    return data_;
}

void Texture::Dirty()
{
    is_dirty_ = true;
}

bool Texture::operator==(const Texture &rhs) const
{
    return texture_ == rhs.texture_;
}

void Texture::SetParameter(Texture::Parameter param, unsigned int value)
{
    GLenum glparam;

    switch (param)
    {
    case MinFilter:
        glparam = GL_TEXTURE_MIN_FILTER;
        break;
    case MagFilter:
        glparam = GL_TEXTURE_MAG_FILTER;
        break;
    case Wrap_S:
        glparam = GL_TEXTURE_WRAP_S;
        break;
    case Wrap_T:
        glparam = GL_TEXTURE_WRAP_T;
        break;
    default:
        return;
        break;
    }

    Bind();
    glTexParameteriv(GL_TEXTURE_2D, glparam, (GLint *)&value);
}

int Texture::GetWidth() const
{
    return data_.getWidth();
}

int Texture::GetHeight() const
{
    return data_.getHeight();
}

unsigned int Texture::GetObject()
{
    return texture_;
}

void Texture::Bind()
{
    _updateImageData();
    glBindTexture(GL_TEXTURE_2D, texture_);
}

void Texture::EnableGenerateMipmaps()
{
    generate_mipmaps_ = true;
}

void Texture::DisableGenerateMipmaps()
{
    generate_mipmaps_ = false;
}

void Texture::_updateImageData()
{
    if (is_dirty_)
    {
        is_dirty_ = false;
        Log::Write(Log::RenderGroup, "Texture: texture %d has dirty data, refreshing.", texture_);

        glBindTexture(GL_TEXTURE_2D, texture_);

        GLenum texelType = GL_RGBA;

        switch (data_.getChannels())
        {
        case 1:
            texelType = GL_RED;
            break;
        case 2:
            texelType = GL_RG;
            break;
        case 3:
            texelType = GL_RGB;
            break;
        case 4:
            texelType = GL_RGBA;
            break;
        default:
        {
            Log::Write(Log::RenderGroup, "Texture: invalid channel count, ignoring data.");
            return;
            break;
        }
        }

        GLenum dataType;
        switch (data_.getType())
        {
        case TextureData::Texel_U8:
            dataType = GL_UNSIGNED_BYTE;
            break;
        case TextureData::Texel_F32:
            dataType = GL_FLOAT;
            break;

        case TextureData::Texel_Invalid: // intentional fall-through
        default:
        {
            Log::Write(Log::RenderGroup, "Texture: invalid channel size, ignoring data.");
            return;
            break;
        }
        }

        if (data_.getType() != TextureData::Texel_F32)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, texelType, data_.getWidth(),
                         data_.getHeight(), 0, texelType, dataType, data_.getData());
        }
        else
        {
            // support non-normalized textures
            // possible to use GL_RGBA32F as well if you need more resolution
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, data_.getWidth(),
                         data_.getHeight(), 0, texelType, dataType, data_.getData());
        }

        if (generate_mipmaps_)
        {
            Log::Write(Log::RenderGroup, "Texture: generating mipmaps.");
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
}
