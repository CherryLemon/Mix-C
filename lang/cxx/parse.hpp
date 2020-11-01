#ifndef xusing_lang_cxx
#include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_parse
#define xpack_lang_cxx_parse
#pragma push_macro("xuser")
#pragma push_macro("xusing_lang_cxx")
#undef  xusing_lang_cxx
#undef  xuser
#define xuser mixc::lang_cxx_parse::inc
#include"configure.hpp"
#include"define/base_type.hpp"
#include"define/nan.hpp"
#include"define/inf.hpp"
#include"docker/transmitter.hpp"
#include"lang/cxx/compare.hpp"
#include"lang/cxx.hpp"
#include"math/numeration_t.hpp"
#include"math/exp10.hpp"
#include"math/expr10.hpp"
#include"meta/is_float.hpp"
#include"meta/unsigned_type.hpp"
#pragma pop_macro("xusing_lang_cxx")
#pragma pop_macro("xuser")

namespace mixc::lang_cxx_parse{
    constexpr u08 lut_error = 0xff;
    constexpr u08 lut[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, lut_error, lut_error, lut_error, lut_error, lut_error, lut_error, lut_error, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, lut_error, lut_error, lut_error, lut_error, lut_error, lut_error, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, lut_error, lut_error, lut_error, lut_error, lut_error, };

    template<class target>
    struct parse_result{
        template<class a>
        parse_result(parse_result<a> self) : 
            parse_result(target(self.value), self.error_index) {}

        parse_result(target v, uxx i) : 
            value(v), error_index(i){}

        parse_result(target v) : 
            value(v), error_index(not_exist){}

        operator target & (){
            return value;
        }

        operator const target & () const {
            return value;
        }

        bool is_parse_error() const {
            return error_index != not_exist;
        }

        uxx index_of_error() const {
            return error_index;
        }
    private:
        template<class a> friend struct parse_result;
        target value; 
        uxx    error_index;
    };

    // using item = char;
    // template<class item> struct core;
    // template<>
    // struct core<item> : inc::cxx<item> {

    template<class item>
    struct core : inc::cxx<item> {
        using inc::cxx<item>::cxx;
        using the_t = core<item>;

        template<class target>
        parse_result<target> parse(uxx base) const {
            bool   is_neg = false;
            target value  = 0;
            item * cur    = the;
            item * begin  = the;
            item * end    = cur + the.length();

            if (begin >= end) {
                return parse_result<target>(value, 0);
            }
            if (cur[0] == '+'){
                cur++;
            }
            else if (cur[0] == '-'){
                cur++;
                is_neg = true;
            }

            if constexpr (inc::is_float<target>){
                // 浮点目前只有 10 进制表示
                // inf
                // nan
                // [+-]{0,1}/d*(/./d+){0,1}([eE][+-]/d+){0,1}
                if (the_t("nan").compare({ cur, 3 }) == 0){
                    return is_neg ? -target(inc::nan) : target(inc::nan);
                }
                if (the_t("inf").compare({ cur, 3 }) == 0){
                    return target(is_neg ? inc::inf_neg : inc::inf_pos);
                }

                auto   token        = cur;
                auto   token_tmp    = cur;
                auto   miss_digital = false;
                auto   miss_decimal = true;
                auto   is_neg_exp   = false;
                target result       = 0;
                target mul          = 0.1;
                u32    exp          = 0;

                auto part = [&](auto value, auto * ptr){
                    auto & cur = ptr[0];
                    while('0' <= cur[0] and cur[0] <= '9'){
                        value  = value * 10 + cur[0] - '0';
                        cur    += 1;
                    };
                    return value;
                };

                // skip 0
                while(cur[0] == '0'){
                    cur += 1;
                }

                // 得到整数部分
                result          = part(result, xref cur);
                miss_digital    = cur == token;

                // 得到小数部分
                if (cur[0] == '.'){
                    cur     += 1;
                    token    = cur;
                    target s = 0.1;

                    while('0' <= cur[0] and cur[0] <= '9'){
                        result  += s * (cur[0] - '0');
                        s       *= mul;
                        cur     += 1;
                    }
                }

                if (is_neg){
                    result = -result;
                }

                if (miss_decimal = token == cur; not miss_digital or not miss_decimal){
                    // 指数部分
                    if (cur[0] != 'e' and cur[0] != 'E'){
                        return result;
                    }

                    cur         += 1;
                    token_tmp    = token = cur;

                    if (cur[0] == '-'){
                        cur     += 1;
                        token   += 1;
                        is_neg_exp = true;
                    }
                    else if (cur[0] == '+'){
                        cur     += 1;
                        token   += 1;
                    }

                    exp = part(exp, xref cur);

                    if (token == cur){
                        cur = token_tmp - 1; // 回滚到字符 'e' or 'E' 之前一个字符
                    }
                    else if (is_neg_exp){
                        result *= inc::expr10(exp);
                    }
                    else{
                        result *= inc::exp10(exp);
                    }

                    if (cur == end){
                        return result;
                    }
                }
                // 如果既没有整数部分，也没有小数部分则表示该字符串不是正确的浮点格式
                else{
                    cur = begin;
                }
                return parse_result<target>(result, cur - begin);
            }
            else{
                for(; cur < end; cur++){
                    constexpr uxx mask = 0x4f; // mask 要大于 'z' - '0'
                    static_assert(mask <= sizeof(lut) / sizeof(lut[0]));
                    static_assert(mask > 'z' - '0');

                    uxx dis = uxx(cur[0] - '0');
                    uxx v   = lut[dis & mask];

                    if (dis >= base or v == lut_error){
                        return parse_result<target>(value, cur - begin);
                    }
                    else{
                        value = value * base + v;
                    }
                }

                if (is_neg){
                    value = target(0) - value;
                }
                return value;
            }
        }
    };

    template<class final, class base, class item>
    struct meta : base{
        using base::base;
        using the_t = core<item>;

        template<class target>
        parse_result<target> parse() const {
            return parse<target>(inc::numeration_t::dec);
        }

        template<class target>
        parse_result<target> parse(inc::numeration_t raidx) const {
            if constexpr (inc::is_float<target>){
                return the.template parse<target>(10);
            }
            if constexpr (sizeof(target) <= sizeof(uxx)){
                return the.template parse<uxx>(uxx(raidx));
            }
            else{
                return the.template parse<inc::unsigned_type<target>>(uxx(raidx));
            }
        }
    };
}

#endif

namespace mixc::lang_cxx_parse::xuser{
    template<class final, class item>
    using cxx = meta<final, xusing_lang_cxx::cxx<final, item>, item>;
}

#include"math/numeration_t.hpp"

#undef  xusing_lang_cxx
#define xusing_lang_cxx ::mixc::lang_cxx_parse::xuser
