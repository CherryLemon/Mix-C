#ifndef xpack_meta_is_same
#define xpack_meta_is_same
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_is_same::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_is_same{
    template<class a, class b> 
    struct meta {
        static constexpr bool result = false;
    };

    template<class a>
    struct meta<a, a> {
        static constexpr bool result = true;
    };

    template<class a, class b>
    constexpr bool is_same = meta<a, b>::result;
}

#endif

xexport(mixc::meta_is_same::is_same)