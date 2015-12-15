#ifndef TEXTUREDATA_H_INCLUDED
#define TEXTUREDATA_H_INCLUDED

#include "../global.h"

class TextureData
{
public:
    enum TexelType {
        Texel_Invalid = 0,  //!< Invalid texel format
        Texel_U8 = 1,       //!< Unsigned byte 0-255
        Texel_F32 = 4       //!< 32 bit float 
    };
    
    TextureData();
    TextureData(int width, int height, int channels, TexelType type, const unsigned char* data);
    ~TextureData();
    

    void resize(int width, int height, int channels, TexelType type, const unsigned char* data);
    

    int getWidth() const;

    int getHeight() const;

    int getChannels() const;

    TexelType getType() const;
        

    unsigned char* getData();

    const unsigned char* getData() const;

    unsigned char* operator[](const unsigned int& index);

    unsigned char* operator()(const unsigned int& x, const unsigned int& y);
    
    void flipImageVertical();
    
private:
    int mWidth;                         //!< Width in texels
    int mHeight;                        //!< Height in texels
    int mChannels;                      //!< Color component count 
    TexelType mType;                    //!< Type of each color component
    std::vector<unsigned char> mData;   //!< Raw data (protected with a std::vector)
};

#endif // TEXTUREDATA_H_INCLUDED