/*
用作将指定类型b隐式转换成类型a
场景：
template<class ... args>
auto function(args const & ... list){
    implicit<int &> seq[] = { list... };
    ...
}
*/
#ifndef xpack_dumb_implicit
#define xpack_dumb_implicit
    #pragma push_macro("xuser")
    #undef  xuser
    #define xuser mixc::dumb_implicit
    #include"mixc.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::dumb_implicit{
        template<class a>
        xstruct(
            xiam(implicit),
            xitm(value, a)
        )
            template<class b>
            implicit(b const & value) : 
                value((a)(b &)value) {}

            operator a () const {
                return value;
            }

            auto operator -> () const {
                return & value;
            }
        };
    }

#endif

namespace xuser::inc{
    using ::mixc::dumb_implicit::implicit;
}
