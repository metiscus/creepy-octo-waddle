#ifndef VBO_H_INCLUDED
#define VBO_H_INCLUDED

#include "../global.h"

/**
	\brief An abstraction of a VBO (and a PBO) for OpenGL
*/
class VBO
{
public:
	enum BindMode {
		ArrayBuffer,		//!< As a vertex data buffer
		ElementArrayBuffer,	//!< As an index buffer
		PixelPackBuffer,	//!< Pack pixel buffer
		PixelUnpackBuffer,	//!< Unpack pixel buffer
	};

	enum UsageType {
		StaticDraw,		//!< Write once, draw many
		StaticRead,		//!< Write once, read many
		StaticCopy,		//!< Write once, copy many
		DynamicDraw,	//!< Write many, draw many
		DynamicRead,	//!< Write many, read many
		DynamicCopy,	//!< Write many, copy many
		StreamDraw,		//!< Write many, draw once
		StreamRead,		//!< Write many, read once
		StreamCopy		//!< Write many, copy once
	};

	/*
		\brief Create the VBO (or PBO)
		\param mode sets the target that the vbo will be bound to
		Important! You can't change this once it is set.
	*/
	VBO(BindMode mode);
	~VBO();

	/**
		\brief Sets the data for the VBO
		\param data pointer to the data (can be null in some rare cases)
		\param dataSize size of data pointed to by data
		\param usage the intended usage for the data in this VBO (may impact performance)
	*/
	void SetData(void* data, size_t dataSize, UsageType usage = DynamicDraw);

	/**
		\brief Sets the data for a segment of the VBO
		\param offset offset into the VBO memory to update with this data
		\param data pointer to the data
		\param dataSize size of data pointed to by data
	*/
	void SetDataOffset(int offset, void* data, size_t dataSize);

	enum MappingType {
		ReadOnly,	//!< Only read operations
		WriteOnly,	//!< Only write operations
		ReadWrite	//!< Both read and write operations
	};

	/// Attempt to map the VBO memory into system memory for random access
	void* MapBuffer(MappingType type);

	/// Unmap the buffer
	void  UnmapBuffer();

	/// Binds the VBO/PBO
	void Bind();

	/// Unbinds the VBO/PBO (binds the target to 0)
	void Unbind();

	void Draw(uint32_t type, uint32_t start, uint32_t count);


private:
	BindMode mMode;
	uint32_t mVBO;

	int32_t _bindToGL(BindMode mode);
	int32_t _usageToGL(UsageType type);
	int32_t _mappingToGL(MappingType type);
};

#endif // VBO_H_INCLUDED
