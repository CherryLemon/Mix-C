#ifndef xpack_macro_xdefer
#define xpack_macro_xdefer
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::macro_xdefer::inc
#include"mixc.hpp"
#include"macro/xlink.hpp"
#pragma pop_macro("xuser")

namespace mixc::macro_xdefer {
    template<class lambda>
    struct defer : lambda{
        defer(lambda const & call) : 
            lambda(call){
        }
        ~defer(){
            lambda::operator()();
        }
    };

    struct sugar{
        template<class lambda>
        auto operator * (lambda const & relase){
            return defer{ relase };
        }
    };
}

#define xdefer      [[maybe_unused]] auto && xlink2(__mixc_defer, __LINE__) = ::mixc::macro_xdefer::sugar() * [&]()
#endif
