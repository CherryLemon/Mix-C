#ifndef xpack_memop_swap
#define xpack_memop_swap
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::memop_swap::inc
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::memop_swap{
    template<class a>
    inline void swap(a * left, a * right){
        struct m{ char bytes[sizeof(a)]; };
        using mp = m *;
        m & l = mp(left)[0];
        m & r = mp(right)[0];
        m   t = l;
        l = r;
        r = t;
    }
}

#endif

xexport(mixc::memop_swap::swap)