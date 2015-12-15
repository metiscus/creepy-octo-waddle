#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include "../global.h"

class Uniform;
class Shader;

class Program
{
public:
    Program();
    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    ~Program();
    
    void AddShader(std::shared_ptr<Shader> ptr);
    void AddUniform(std::shared_ptr<Uniform> ptr);
    
    bool Link();
    void Use();
    
    const std::string GetLinkErrors() const;
    uint32_t GetProgram() { return program_; }

private:
    unsigned int program_;                              //!< OpenGL program
    std::string error_string_;                          //!< Link error string
    std::vector< std::shared_ptr<Shader> > shaders_;    //!< Shaders to be linked in
    std::vector< std::shared_ptr<Uniform> > uniforms_;  //!< Uniforms to be linked in
};

#endif /* PROGRAM_H_INCLUDED */
