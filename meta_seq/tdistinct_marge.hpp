#ifndef xpack_meta_seq_tdistinct_merge
#define xpack_meta_seq_tdistinct_merge
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_seq_tdistinct_merge::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#include"meta_seq/tlist.hpp"
#include"meta_seq/tin.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_seq_tdistinct_merge{
    using namespace inc;

    template<class list_a, class list_b>
    struct tdistinct_merge{
    private:
        template<class first, class ... args, class ... result_args>
        static auto invoke(tlist<first, args...>, tlist<result_args...>){
            if constexpr (tin<tlist<result_args...>, first>){
                return invoke(
                    tlist<args...>(), 
                    tlist<result_args...>()
                );
            }
            else{
                return invoke(
                    tlist<args...>(), 
                    tlist<result_args..., first>()
                );
            }
        }

        template<class result_list>
        static auto invoke(tlist<>, result_list r){
            return r;
        }
    public:
        using new_list = decltype(
            invoke(list_b(), list_a())
        );
    };
}

#endif

xexport(mixc::meta_seq_tdistinct_merge::tdistinct_marge)