#include "texturedata.h"

#include "../log.h"

TextureData::TextureData()
    : mWidth(0)
    , mHeight(0)
    , mChannels(0)
    , mType(Texel_Invalid)
{
    ;
}

TextureData::TextureData(int width, int height, int channels, TexelType type,
                         const unsigned char *data)
    : mWidth(width)
    , mHeight(height)
    , mChannels(channels)
    , mType(type)
{
    Log::Write(Log::RenderGroup, "TextureData: width=%d height=%d channels=%d type=%d data=%p.", width, height,
          channels, type, data);

    resize(width, height, channels, type, data);
}

TextureData::~TextureData()
{
    ;
}

void TextureData::resize(int width, int height, int channels, TexelType type,
                         const unsigned char *data)
{
    Log::Write(Log::RenderGroup, "TextureData: width=%d height=%d channels=%d type=%d data=%p.", width, height,
          channels, type, data);

    assert(width > 0 && height > 0 && channels > 0 && data && type != TextureData::Texel_Invalid);
    mWidth = width;
    mHeight = height;
    mChannels = channels;
    mType = type;

    // clear existing data
    mData.clear();

    // compute texel width in bytes
    size_t texelWidth = (int)type;
    mData.insert(mData.begin(), data,
                 data + (width * height * channels * texelWidth));
}

int TextureData::getWidth() const
{
    return mWidth;
}

int TextureData::getHeight() const
{
    return mHeight;
}

int TextureData::getChannels() const
{
    return mChannels;
}

TextureData::TexelType TextureData::getType() const
{
    return mType;
}

unsigned char *TextureData::getData()
{
    return &mData[0];
}

const unsigned char *TextureData::getData() const
{
    return &mData[0];
}

unsigned char *TextureData::operator[](const unsigned int &index)
{
    // compute texel width in bytes
    const size_t texelWidth = (size_t)mType;
    return &mData[index * texelWidth * mChannels];
}

unsigned char *TextureData::operator()(const unsigned int &x,
                                       const unsigned int &y)
{
    // compute texel width in bytes
    const size_t texelWidth = (size_t)mType;
    return &(mData[texelWidth * (y * mWidth * mChannels + x)]);
}

void TextureData::flipImageVertical()
{
    // compute texel width in bytes
    const size_t texelWidth = (size_t)mType;
    const size_t lineWidth = texelWidth * mChannels * mWidth;
    std::vector<unsigned char> scanline;
    scanline.resize(lineWidth);
    for (int ii = 0; ii <= mHeight / 2; ++ii)
    {
        unsigned char *ptr_to = &mData[ii * lineWidth];
        unsigned char *ptr_from = &mData[(mHeight - 1 - ii) * lineWidth];
        scanline.assign(ptr_to, ptr_to + lineWidth);
        memcpy(ptr_to, ptr_from, lineWidth);
        memcpy(ptr_from, &scanline[0], lineWidth);
    }
}