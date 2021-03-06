#ifndef xpack_meta_remove_ptr
#define xpack_meta_remove_ptr
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_remove_ptr::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_remove_ptr{
    template<class a>
    struct meta {
        using result = a;
    };

    template<class a>
    struct meta<a *> {
        using result = a;
    };

    template<class a>
    struct meta<a * const> {
        using result = a;
    };

    template<class type>
    using remove_ptr = typename meta<type>::result;
}

#endif

xexport(mixc::meta_remove_ptr::remove_ptr)