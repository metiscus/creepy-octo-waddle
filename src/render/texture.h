#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../global.h"

#include "texturedata.h"

class Texture
{
public:
    Texture();
    ~Texture();
    
    /**
        \brief load a texture from an image file
        \param filename c-string containing the name of an image file to load
    */
    bool loadFromFile(const char* filename);

    /**
        \brief load a texture from a TextureData object
        \param data a reference to the data from which to populate the object
    */
    bool setFromData(const TextureData& data);
    
    /// Returns a reference to the internal image data, sets dirty bit
    TextureData& getDataRW();

    /// Returns a reference to the internal image data, does not set the dirty big
    const TextureData& getDataRO() const;
    
    /// Binds the texture to the currently active texture unit
    void bind();
    
    /// Describes various texture parameters that can be set
    enum Parameter {
        MinFilter,      //!< Minification filter
        MagFilter,      //!< Magnification filter
        Wrap_S,         //!< Texture wrap in s direction (x)
        Wrap_T,         //!< Texture wrap in t direction (y)
    };
    
    /**
        \brief Sets a texture parameter for this texture
        \param param which parameter to set the value for
        \param value an OpenGL enum to set for that parameter
    */
    void setParameter( Parameter param, unsigned int value );
    
    /// Returns the width in texels
    int getWidth() const;
    /// Returns the height in texels
    int getHeight() const;
    
    /// Checks for equality between textures
    bool operator==(const Texture& rhs) const;
    
    /**
        \brief Enable hardware mipmap generation
        Important! Texture that are not power of 2 may segfault. YMMV
    */
    void enableGenerateMipmaps();

    /**
        \brief Disable hardware mipmap generation
    */
    void disableGenerateMipmaps();
    
    /// Returns the raw OpenGL object
    unsigned int getObject();
    
    /// Sets the dirty bit which causes the texture to get reuploaded.
    /// This is expensive, so only call this when you have changed the data
    /// through a pointer or some other naughty activity.
    void dirty();
    
private:
    unsigned int mTexture;      //!< OpenGL texture object
    bool mIsDirty;              //!< Flag that indicates if the texture data needs reuploaded
    bool mGenerateMipmaps;      //!< Flag that controls hardware mipmap generation
    TextureData mData;          //!< Raw data for the texture (to be uploaded when dirty)
    
    void _updateImageData();    //!< Handles uploading dirty data to OpenGL
};

#endif /* TEXTURE_H_ */
