#ifndef xpack_meta_seq_tdistinct_append
#define xpack_meta_seq_tdistinct_append
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::meta_seq_tdistinct_append::inc
#include"define/base_type.hpp"
#include"macro/xexport.hpp"
#include"meta_seq/tlist.hpp"
#include"meta_seq/tin.hpp"
#include"meta_ctr/cif.hpp"
#pragma pop_macro("xuser")

namespace mixc::meta_seq_tdistinct_append{
    using namespace inc;

    template<class tlist, class item_t> struct tdistinct_append;
    template<class item_t, class ... args>
    struct tdistinct_append<tlist<args...>, item_t>{
        using new_list = 
            typename cif< 
                tin< tlist<args...>, item_t > 
            >::template select<
                tlist<args...>
            >::template ces<
                tlist<args..., item_t>
            >;
    };
}

#endif

xexport(mixc::meta_seq_tdistinct_append::tdistinct_append)
