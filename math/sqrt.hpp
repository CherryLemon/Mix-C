#ifndef xpack_math_sqrt
#define xpack_math_sqrt
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::math_sqrt
#include"define/base_type.hpp"
#include"define/nan.hpp"
#pragma pop_macro("xuser")

namespace mixc::math_sqrt{
    extern f64 sqrt_unsafe(f64 x);

    inline f64 sqrt(f64 x){
        if (x < 0){
            return inc::nan;
        }
        return sqrt_unsafe(x);
    }
}

#endif

namespace xuser::adv{
    using ::mixc::math_sqrt::sqrt_unsafe;
}

namespace xuser::inc{
    using ::mixc::math_sqrt::sqrt_unsafe;
}