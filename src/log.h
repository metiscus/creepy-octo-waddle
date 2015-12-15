#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

#include "global.h"

namespace Log
{
    enum LogGroup
    {
        DefaultGroup = 0x1,
        DebugGroup   = DefaultGroup,
        WarnGroup    = DefaultGroup<<1,
        ErrorGroup   = DefaultGroup<<2,
        RenderGroup  = DefaultGroup<<3,
        AIGroup      = DefaultGroup<<4
    };

    void EnableGroup(enum LogGroup group);
    void DisableGroup(enum LogGroup group);

    void Write(enum LogGroup group, const char* str, ...);
    void Write(enum LogGroup group, const std::string& str, ...);
}

#define Assert(test)                                                \
if(!(test))                                                         \
{                                                                   \
    fprintf(stderr, "[Assert] : Condition '%s' false.\n", #test);   \
    abort();                                                        \
}

#define AssertMessage(test, msg)                                    \
if(!(test))                                                         \
{                                                                   \
    fprintf(stderr, "[Assert] : Condition '%s' false. %s\n", #test, msg);\
    abort();                                                        \
}

#endif // LOGGING_H_INCLUDED
