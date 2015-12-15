#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include "../global.h"

class Shader
{
public:
    enum Type {
        Vertex,     //!< Vertex shader
        Fragment,   //!< Fragment shader
        Geometry    //!< Geometry shader
    };

    Shader(Type type);
    Shader(const Shader&) = delete;
    ~Shader();
    
    Shader& operator=(const Shader&) = delete;

    void LoadFile(const char* filename);
    
    void SetText(const char* text);
    
    bool Compile();
        
    const std::string& GetCompileErrors();

    friend class Program;
    
protected:
    unsigned int Get();

private:
    unsigned int shader_;       //!< OpenGL shader object
    std::string text_;    //!< Text of the shader
    std::string errors_; //!< Text of any compile errors
};

#endif /* SHADER_H_INCLUDED */
