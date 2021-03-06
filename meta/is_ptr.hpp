#ifndef xpack_meta_is_ptr
#define xpack_meta_is_ptr
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_is_ptr::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_is_ptr{
    template<class a> struct meta {
        static constexpr bool result = false;
    };
    
    template<class a> struct meta<a *> {
        static constexpr bool result = true;
    };
    
    template<class a> struct meta<a const *> {
        static constexpr bool result = true;
    };

    template<class a> struct meta<a * const> {
        static constexpr bool result = true;
    };

    template<class a> struct meta<const a * const> {
        static constexpr bool result = true;
    };

    template<class a>
    concept is_ptr = meta<a>::result;
}

#endif

xexport(mixc::meta_is_ptr::is_ptr)