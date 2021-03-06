#ifndef xpack_meta_is_union
#define xpack_meta_is_union
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_is_union::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_is_union{
    template<class a>
    concept is_union = __is_union(a);
}

#endif

xexport(mixc::meta_is_union::is_union)