#ifndef xusing_lang_cxx
    #include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_trim_start
#define xpack_lang_cxx_trim_start
    #pragma push_macro("xuser")
    #pragma push_macro("xusing_lang_cxx")
        #undef  xusing_lang_cxx
        #undef  xuser
        #define xuser mixc::lang_cxx_trim_start
        #include"define/base_type.hpp"
        #include"dumb/implicit.hpp"
        #include"lang/cxx/clone.hpp"
        #include"lang/cxx/index_of_first_miss.hpp"
        #include"lang/cxx.hpp"
        #include"lang/private/layout_args.hpp"
        #include"memory/alloc_callback.hpp"
        #include"meta/is_same.hpp"
    #pragma pop_macro("xusing_lang_cxx")
    #pragma pop_macro("xuser")

    namespace mixc::lang_cxx_trim_start{
        template<class item>
        xgc(core,
            xtmpl(item),
            xpub(inc::cxx<item>)
        )
            using inc::cxx<item>::cxx;
            using the_t = __self__;

            template<class ... args>
            auto trim_start(item value, args const & ... list) const {
                item             group[sizeof...(args) + 1]; // 包含'\0'
                auto             may_alloc  = inc::layout_args(group, value, list...);
                constexpr auto   need_alloc = inc::is_same<decltype(may_alloc), inc::alloc_callback<item>>;
                auto             token      = the_t(group, sizeof...(args) + 1 - need_alloc);
                auto             offset     = the.index_of_first_miss(token, token.length);

                if constexpr (need_alloc){
                    if (offset == not_exist){
                        return the_t();
                    }
                    else{
                        return the.backward(offset).clone(may_alloc);
                    }
                }
                else {
                    return the.backward(offset);
                }
            }
        xgc_end();
    }
#endif

namespace xuser::lang_cxx_trim_start{
    namespace cur{
        using namespace mixc::lang_cxx_trim_start;
    }
    namespace inc{
        using namespace cur::inc;
    }

    template<class item, class final>
    xgc(cxx,  
        xtmpl(item, final),
        xpub(xusing_lang_cxx::cxx<item, final>)
    )
        using xusing_lang_cxx::cxx<item, final>::cxx;
        using the_t = cur::core<item>;

        template<class ... args>
        final trim_start(item value, args const & ... list) const {
            return the.trim_start(value, list...);
        }
    xgc_end();
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx xuser::lang_cxx_trim_start
