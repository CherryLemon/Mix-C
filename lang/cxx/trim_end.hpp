#ifndef xusing_lang_cxx
#include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_trim_end
#define xpack_lang_cxx_trim_end
#pragma push_macro("xuser")
#pragma push_macro("xusing_lang_cxx")
#undef  xusing_lang_cxx
#undef  xuser
#define xuser mixc::lang_cxx_trim_end::inc
#include"define/base_type.hpp"
#include"interface/can_alloc.hpp"
#include"interface/initializer_list.hpp"
#include"lang/cxx/clone.hpp"
#include"lang/cxx/index_of_last_miss.hpp"
#include"lang/cxx.hpp"
#include"meta/is_same.hpp"
#pragma pop_macro("xusing_lang_cxx")
#pragma pop_macro("xuser")

namespace mixc::lang_cxx_trim_end{
    template<class item_t>
    struct core {
        using the_t = inc::cxx<item_t>;

        template<class alloc_t>
        auto trim_end(inc::initializer_list<item_t> values, alloc_t const & alloc) {
            auto token  = the_t(values.begin(), values.size());
            auto r      = the;

            if (auto index = r.index_of_last_miss(values); index != not_exist){
                r       = r.length(index + 1);
            }
            if constexpr (inc::is_same<alloc, decltype(nullptr)>){
                r       = r.clone(alloc);
            }
            return r;
        }
    };

    template<class final, class base, class item_t>
    struct meta : base{
        using base::base;
        using the_t = core<item_t>;

        final trim_end(item_t value) {
            return the.trim_end({ value }, nullptr);
        }

        final trim_end(inc::initializer_list<item_t> values) {
            return the.trim_end(values, alloc);
        }

        template<class alloc_t>
        requires(
            inc::can_alloc<alloc_t, item_t>
        )
        final trim_end(item_t value, alloc_t const & alloc) {
            return the.trim_end({ value }, alloc);
        }

        template<class alloc_t>
        requires(
            inc::can_alloc<alloc_t, item_t>
        )
        final trim_end(inc::initializer_list<item_t> values, alloc_t const & alloc) {
            return the.trim_end(values, alloc);
        }
    };
}

#endif

namespace mixc::lang_cxx_trim_end::xuser{
    template<class final, class item_t>
    using cxx = meta<final, xusing_lang_cxx::cxx<final, item_t>, item_t>;
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_trim_end::xuser
