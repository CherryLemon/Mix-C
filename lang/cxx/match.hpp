// TO BE CONTINUE

#ifndef xusing_lang_cxx
#include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_match
#define xpack_lang_cxx_match
#pragma push_macro("xuser")
#pragma push_macro("xusing_lang_cxx")
#undef  xusing_lang_cxx
#undef  xuser
#define xuser mixc::lang_cxx_match::inc
#include"define/base_type.hpp"
#include"lang/wxx/+.hpp"
#include"lang/wxx.hpp"
#include"lang/cxx/parse.hpp"
#include"lang/cxx.hpp"
#pragma pop_macro("xusing_lang_cxx")
#pragma pop_macro("xuser")

namespace mixc::lang_cxx_match{
    template<class unsigned_t = uxx>
    struct pair {
        unsigned_t offset;
        unsigned_t length;
    };

    template<class unsigned_t = uxx>
    struct context{
        struct{
            uxx left_range;
            uxx right_range;
        } match_count;

        pair<unsigned_t> point;
    };

    template<class item_t> struct core;
    using item_t = char;
    template<>
    struct core<item_t> : inc::cxx<item_t> {

    // template<class item_t>
    // struct core : inc::cxx<item_t> {
        using base_t = inc::cxx<item_t>;
        using base_t::base_t;
        using the_t = core<item_t>;

        core(base_t const & self) : 
            base_t(self){}

        auto match(the_t pattern) const {
            /* []
                * [^]
                * /w
                * +x
                * *x
                * -x
                * +x
                * /
                * /w  n~1
                * /w  n~0
                * /w  0~n
                * w
                * 
                */

            
        }
        
        bool middle(the_t special, the_t pattern) {
            auto c = special[0];
            special = special.backward(1);

            switch(c){
            case '/': return base(special[0], pattern[0]);
            case '{': 
                auto r = special.parse<uxx>();
                if (not r.is_parse_error()){
                    // error 
                }
            }
            return false;
        }

        bool base(item_t special, inc::wxx<item_t> pattern) {
            switch(special){
            case 'w': return pattern.is_alpha();
            case 'W': return not pattern.is_alpha();
            case 's': return pattern.is_whitespace();
            case 'S': return not pattern.is_whitespace();
            case 'd': return pattern.is_digital();
            case 'D': return not pattern.is_digital();
            case '/': return pattern == '/';
            }
            return false;
        }
    };
}

#endif

namespace mixc::lang_cxx_match::xuser{
    template<class final, class item_t>
    struct cxx : xusing_lang_cxx::cxx<final, item_t>{
        using xusing_lang_cxx::cxx<final, item_t>::cxx;
        using the_t = core<item_t>;

        auto match(final pattern) const {
            return the.match(pattern);
        }
    };
}

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_match::xuser
