#ifndef xpack_meta_seq_tpop
#define xpack_meta_seq_tpop
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_seq_tpop::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#include"meta_seq/tlist.hpp"
#include"meta_seq/tnull.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_seq_tpop{
    using namespace inc;
    // 本来这样写挺好的
    // 但目前C++不准这样做
    // error: class template partial specialization contains template parameters that cannot be deduced
    // this partial specialization will never be used

    // template<class list> struct tpop;
    // template<class last, class ... args>
    // struct tpop<tlist<args..., last>>{
    //     using item_t = last;
    //     using new_tlist = tlist<args...>;
    // };

    // template<>
    // struct tpop<tlist<>>{
    //     using item_t = tnull;
    //     using new_tlist = tlist<>;
    // };

    template<class list>
    struct tpop{
    private:
        template<class first, class second, class ... args, class ... result_args>
        static auto invoke(tlist<first, second, args...>, tlist<result_args...>){
            return invoke(
                tlist<second, args...>(),
                tlist<result_args..., first>()
            );
        }

        template<class last, class ... result_args>
        static auto invoke(tlist<last>, tlist<result_args...>){
            struct pair{
                using item_t = last;
                using new_list = tlist<result_args...>;
            };
            return pair();
        }

        template<class ... result_args>
        static auto invoke(tlist<>, tlist<result_args...>){
            struct pair{
                using item_t = tnull;
                using new_list = tlist<result_args...>;
            };
            return pair();
        }
        using pair = decltype(
            invoke(list(), tlist<>())
        );
    public:
        using item_t = typename pair::item_t;
        using new_list = typename pair::new_list;
    };
}

#endif

xexport(mixc::meta_seq_tpop::tpop)