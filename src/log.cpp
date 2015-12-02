#include "log.h"
#include <cstdint>

namespace Log
{
    static uint64_t active_groups = (uint64_t)-1U;

    static const char* log_group_text [] =
    {
        "Debug",
        "Warn",
        "Error",
        "Render",
        "AI"
    };


    inline int uint64_log2(uint64_t n)
    {
      #define S(k) if (n >= (UINT64_C(1) << k)) { i += k; n >>= k; }

      int i = -(n == 0); S(32); S(16); S(8); S(4); S(2); S(1); return i;

      #undef S
    }

    void EnableGroup(enum LogGroup group)
    {
        active_groups |= group;
    }

    void DisableGroup(enum LogGroup group)
    {
        active_groups &= !group;
    }

    void Write(enum LogGroup group, const char* str, ...)
    {
        if(active_groups & group)
        {
            va_list ap;
            va_start(ap, str);
            fprintf(stderr, "[%s] : ", log_group_text[uint64_log2(group)]);
            vfprintf(stderr, str, ap);
            fprintf(stderr, "\n");
            va_end(ap);
        }
    }

    void Write(enum LogGroup group, const std::string& str, ...)
    {
        if(active_groups & group)
        {
            va_list ap;
            va_start(ap, str);
            fprintf(stderr, "[%s] : ", log_group_text[uint64_log2(group)]);
            vfprintf(stderr, str.c_str(), ap);
            fprintf(stderr, "\n");
            va_end(ap);
        }
    }

}
