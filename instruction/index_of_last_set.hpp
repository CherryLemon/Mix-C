#ifndef xpack_instruction_index_of_last_set
#define xpack_instruction_index_of_last_set
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::instruction_index_of_last_set::inc
#include"configure.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::instruction_index_of_last_set{
    template<class type>
    inline uxx index_of_last_set(type v){
        uxx i;
        #if xis_x86
            #if xis_os64
                i = 63 - __builtin_clzll(v);
            #else
                if constexpr (sizeof(v) == 8){
                    i = u64(v) >> 32 ? 
                        31 - __builtin_clz(u64(v) >> 32) + 32:
                        31 - __builtin_clz(u32(v));
                }
                else {
                    i = 31 - __builtin_clz(v);
                }
            #endif
        #endif
        return v == 0 ? not_exist : i;
    }
}

#endif

xexport(mixc::instruction_index_of_last_set::index_of_last_set)