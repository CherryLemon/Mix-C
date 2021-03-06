#ifndef xpack_meta_seq_tsub
#define xpack_meta_seq_tsub
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_seq_tsub::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#include"meta_seq/tlist.hpp"
#include"meta_seq/tin.hpp"
#include"meta_seq/tmerge.hpp"
#include"meta_ctr/cif.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_seq_tsub{
    using namespace inc;

    template<class tlist_a, class tlist_b> struct tsub;
    template<class minus, class first, class ... args>
    struct tsub<tlist<first, args...>, minus>{
    private:
        using item_t = cif<
            tin<minus, first>,
            tlist<>,
            tlist<first>
        >;

        using next = 
            typename tsub<tlist<args...>, minus>::new_list;
    public:
        using new_list = 
            typename tmerge<item_t, next>::new_list;
    };

    template<class minus>
    struct tsub<tlist<>, minus>{
        using new_list = tlist<>;
    };        
}

#endif

xexport(mixc::meta_seq_tsub::tsub)