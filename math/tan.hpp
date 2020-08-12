#ifndef xpack_math_tan
#define xpack_math_tan
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::math_tan
#include"define/base_type.hpp"
#pragma pop_macro("xuser")

namespace mixc::math_tan{
    f64 tan_unsafe(f64 x);
    f64 tan(f64 x);
}

#endif

namespace xuser::inc{
    using ::mixc::math_tan::tan;
}

namespace xuser::adv{
    using ::mixc::math_tan::tan_unsafe;
}
