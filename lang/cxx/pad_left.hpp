#ifndef xusing_lang_cxx
#include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_pad_left
#define xpack_lang_cxx_pad_left
#pragma push_macro("xuser")
#pragma push_macro("xusing_lang_cxx")
#undef  xusing_lang_cxx
#undef  xuser
#define xuser mixc::lang_cxx_pad_left::inc
#include"define/base_type.hpp"
#include"interface/can_alloc.hpp"
#include"lang/cxx.hpp"
#include"memop/copy.hpp"
#include"memop/fill.hpp"
#pragma pop_macro("xusing_lang_cxx")
#pragma pop_macro("xuser")

namespace mixc::lang_cxx_pad_left{
    template<class item_t>
    struct core : inc::cxx<item_t> {
        using base_t = inc::cxx<item_t>;
        using base_t::base_t;
        using the_t = core<item_t>;

        core(base_t const & self) : 
            base_t(self){}

        template<class alloc_t>
        requires(
            inc::can_alloc<alloc_t, item_t>
        )
        auto pad_left(uxx count, item_t value, alloc_t const & alloc) const {
            uxx                     length = the.length() + count;
            the_t                   r(alloc(length), length);
            inc::fill_with_operator(r, value, count);
            inc::copy_with_operator(r.backward(count), the, the.length());
            return r;
        }
    };

    template<class final, class base, class item_t>
    struct meta : base {
        using base::base;
        using the_t = core<item_t>;

        template<class alloc_t>
        requires(
            inc::can_alloc<alloc_t, item_t>
        )
        final pad_left(uxx count, item_t value, alloc_t const & alloc) const {
            return the.pad_left(count, value, alloc);
        }
    };
}

#endif

namespace mixc::lang_cxx_pad_left::xuser {
    template<class final, class item_t>
    using cxx = meta<final, xusing_lang_cxx::cxx<final, item_t>, item_t>;
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_pad_left::xuser
