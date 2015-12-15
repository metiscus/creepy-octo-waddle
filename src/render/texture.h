#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../global.h"

#include "texturedata.h"
#include "../resource.h"

// Resource ID Type is {234c06b0-68eb-46d2-aca8-ba1f544038d2}

class Texture : public Resource
{
public:
    static const ResourceType TypeId;
    
    Texture(const ResourceId& id);
    ~Texture();

    static std::shared_ptr<Resource> Load(rapidxml::xml_document<> &doc);
    
    bool LoadFromFile(const char* filename);

    bool SetFromData(const TextureData& data);

    TextureData& GetDataRW();

    const TextureData& GetDataRO() const;
    
    void Bind();
    
    /// Describes various texture parameters that can be set
    enum Parameter {
        MinFilter,      //!< Minification filter
        MagFilter,      //!< Magnification filter
        Wrap_S,         //!< Texture wrap in s direction (x)
        Wrap_T,         //!< Texture wrap in t direction (y)
    };
    

    void SetParameter( Parameter param, unsigned int value );
    
    int GetWidth() const;
    int GetHeight() const;
    
    bool operator==(const Texture& rhs) const;
    

    // Important! Texture that are not power of 2 may segfault. YMMV
    void EnableGenerateMipmaps();


    void DisableGenerateMipmaps();
    
    unsigned int GetObject();
    
    void Dirty();
    
private:
    unsigned int texture_;      //!< OpenGL texture object
    bool is_dirty_;              //!< Flag that indicates if the texture data needs reuploaded
    bool generate_mipmaps_;      //!< Flag that controls hardware mipmap generation
    TextureData data_;          //!< Raw data for the texture (to be uploaded when dirty)
    
    void _updateImageData();    //!< Handles uploading dirty data to OpenGL
};

#endif /* TEXTURE_H_ */
