#ifndef xpack_define_mfxx
#define xpack_define_mfxx
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::define_mfxx
#include"define/base_type.hpp"
#pragma pop_macro("xuser")

namespace mixc::define_mfxx{
    template<
        class   float_type, 
        class   equivalent_type, 
        uxx     decimal_bits, 
        uxx     exp_bits, 
        uxx     exp_offset,
        uxx     precious_bits>
    union mfxx{
        using the_t = mfxx<
            float_type,
            equivalent_type,
            decimal_bits,
            exp_bits,
            exp_offset,
            precious_bits
        >;

        struct {
            equivalent_type decimal : decimal_bits;
            equivalent_type exp     : exp_bits;
            equivalent_type sign    : 1;
        };

        float_type value;

        the_t & real_exp(ixx value){
            the.exp = value + exp_offset;
            return the;
        }

        ixx real_exp() const {
            return ixx(the.exp) - exp_offset;
        }

        u64 real_dec() const {
            return u64(u64(1) << decimal_bits | the.decimal);
        }

        mfxx() : value(0) { }
        mfxx(float_type value) : value(value) { }

        constexpr mfxx(equivalent_type sign, equivalent_type exp, equivalent_type decimal) : 
            decimal(decimal), exp(exp), sign(sign) {}

        constexpr uxx precious(){
            return precious_bits;
        }

        operator float_type & () {
            return value;
        }

        operator const float_type & () const {
            return value;
        }
    };
}

namespace mixc::define_mfxx::origin{
    using mf32 = mfxx<f32, u32, 23, 8 , (1 <<  8) - 1, 7>;
    using mf64 = mfxx<f64, u64, 52, 11, (1 << 10) - 1, 16>;
    using mf80 = mfxx<f80, u64, 64, 15, (1 << 14) - 1, 18>;
}

#endif

namespace xuser::inc{
    using namespace ::mixc::define_mfxx::origin;
}
