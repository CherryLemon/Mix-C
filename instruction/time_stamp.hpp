#ifndef xpack_instruction_time_stamp
#define xpack_instruction_time_stamp
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::instruction_time_stamp::inc
#include"configure.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::instruction_time_stamp{
    inline u64 time_stamp(){
        #if xis_msvc
            extern u64 rdtsc();
            return rdtsc();
        #elif xis_x86
            return __builtin_ia32_rdtsc();
        #endif
    }
}

#endif

xexport(mixc::instruction_time_stamp::time_stamp)