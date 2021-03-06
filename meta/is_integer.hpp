#ifndef xpack_meta_is_integer
#define xpack_meta_is_integer
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_is_integer::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#include"meta/is_unsigned.hpp"
#include"meta/is_signed.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_is_integer{
    template<class a>
    struct meta {
        static constexpr bool result = inc::is_signed<a> or inc::is_unsigned<a>;
    };

    template<class a>
    concept is_integer = meta<a>::result;
}

#endif

xexport(mixc::meta_is_integer::is_integer)