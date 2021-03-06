#ifndef xpack_define_bitbind
#define xpack_define_bitbind
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::utils_bitbind::inc
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::utils_bitbind{
    template<class type, class bit_type = bool>
    xstruct(
        xtmpl(bitbind, type, bit_type),
        xprif(ptr,  type *),
        xprif(mask, type)
    )
        bitbind() : bitbind(nullptr, 0) {}
        bitbind(type * bits, uxx index){
            the.bind(bits, index);
        }

        bit_type operator = (bit_type value){
            ptr[0]      = value ? ptr[0] | mask : ptr[0] & ~mask;
            return value;
        }

        void bind(type * bits, uxx index){
            ptr         = bits;
            mask        = type(1) << index;
        }

        void swap_value(bitbind value){
            bit_type a  = the;
            bit_type b  = value;
            the         = b;
            value       = a;
        }

        operator bit_type(){
            return bit_type((ptr[0] & mask) != 0);
        }
    $
}

#endif

xexport(mixc::utils_bitbind::bitbind)