#ifndef xpack_interface_can_compare
#define xpack_interface_can_compare
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::interface_can_compare::inc
#include"interface/can_callback.hpp"
#include"macro/xcmp.hpp"
#include"memop/cmp.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::interface_can_compare::origin{
    template<class item>
    using can_compare = inc::can_callback<ixx(item const &, item const &)>;

    template<class type>
    inline auto const & default_compare = 
        [] xcmp(type){
            return inc::cmp<type>(left, right);
        };

    template<class type>
    inline auto const & default_compare_neg = 
        [] xcmp(type){
            return inc::cmp<type>(right, left);
        };
}
#endif

xexport_space(mixc::interface_can_compare::origin)