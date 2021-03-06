#ifndef xpack_meta_is_enum
#define xpack_meta_is_enum
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_is_enum::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_is_enum{
    template<class a>
    concept is_enum = __is_enum(a);
}

#endif

xexport(mixc::meta_is_enum::is_enum)