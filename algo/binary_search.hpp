/* 模块：binary_search
 * 类型：函数单体
 * 功能：通过二分搜索指定元素在序列中的索引
 * 用法：
 * TODO ===========================================================
 * 
 * 注意：
 * - 被搜索的序列必须是升序的
 * - 搜索到的元素不一定是第一个匹配的元素，所以和遍历序列得到的索引可能不一样
 */

#ifndef xpack_algo_binary_search
#define xpack_algo_binary_search
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::algo_binary_search::inc
#include"interface/can_callback.hpp"
#include"interface/can_compare.hpp"
#include"interface/unified_seq.hpp"
#include"macro/xexport.hpp"
#include"meta/item_origin_of.hpp"
#pragma pop_macro("xuser")

namespace mixc::algo_binary_search{
    /* 函数：二分匹配模板
     * 参数：
     * - length 为被搜索序列的长度
     * - compare 为参与匹配的回调函数，期望签名如下：
     *      ixx compare(uxx index)
     *   其中 index 为当前参与比较的元素的索引
     *   如果参与比较的元素大于目标值则返回正数，若小于则返回负数，相等则返回零
     * 返回：
     * - result_t 结构
     */
    template<class compare_invoke>
    inline auto match_core(uxx length, compare_invoke const & compare) {
        struct result_t {
            // 刚好匹配的索引
            uxx match;

            // 小于期望值的索引
            uxx less_then_target;

            // 大于期望值的索引
            uxx grater_then_target;

            result_t() {
                match               = not_exist;
                less_then_target    = not_exist;
                grater_then_target  = not_exist;
            }
        };

        result_t result;
        i64      left   = 0;
        i64      center = i64(length >> 1);
        i64      right  = i64(length - 1);
        i64      backup = 0;
        ixx      cmp    = 0;

        for (; left <= right; center = (left + right) >> 1) {
            if (backup = center, cmp = compare(uxx(center)); cmp > 0) {
                right = center - 1;
            }
            else if (cmp < 0) {
                left = center + 1;
            }
            else {
                result.match = uxx(center);
                return result;
            }
        }

        if (cmp > 0) {
            result.grater_then_target = uxx(backup);

            if (backup > 0) {
                result.less_then_target = uxx(backup - 1);
            }
        }
        else {
            result.less_then_target = uxx(backup);

            if (u64(backup + 1) < u64(length)) {
                result.grater_then_target = uxx(backup + 1);
            }
        }
        return result;
    }

    #define xheader(ret,name)                                                           \
        template<                                                                       \
            inc::can_unified_seqlize seq_t,                                             \
            class                    item_t  = inc::item_origin_of<seq_t>,              \
            class                    cmp_t   = decltype(inc::default_compare<item_t>)   \
        >                                                                               \
        requires(                                                                       \
            inc::can_compare<cmp_t, item_t>                                             \
        )                                                                               \
        inline ret name(                                                                \
            seq_t   const & seq,                                                        \
            item_t  const & value,                                                      \
            cmp_t   const & compare = inc::default_compare<item_t>)

    /* 函数：二分匹配模板
     * 参数：
     * - length 为被搜索序列的长度
     * - compare 为参与匹配的回调函数，期望签名如下：
     *      ixx compare(uxx index)
     *   其中 index 为当前参与比较的元素的索引
     *   如果参与比较的元素大于目标值则返回正数，若小于则返回负数，相等则返回零
     * 返回：
     * - result_t 结构
     */
    xheader(auto, match_template) {
        inc::unified_seq<seq_t> list(seq);

        return match_core(list.length(), [&](uxx current){
            return compare(list[current], value);
        });
    }
}

namespace mixc::algo_binary_search::origin::binary_search{
    // using can_search = inc::can_callback<ixx(uxx)>;

    // 说明：在升序序列中寻找刚好匹配搜索值的索引，如果不匹配则返回 not_exist
    xheader(uxx, match) {
        return match_template(seq, value, compare).match;
    }

    // 说明：在升序序列中寻找不小于搜索值的索引，如果不匹配则返回 not_exist
    xheader(uxx, greater_equals) {
        auto result = match_template(seq, value, compare);
        return result.match == not_exist ? result.grater_then_target : result.match;
    }

    // 说明：在升序序列中寻找不大于搜索值的索引，如果不匹配则返回 not_exist
    xheader(uxx, less_equals){
        auto result = match_template(seq, value, compare);
        return result.match == not_exist ? result.less_then_target : result.match;
    }

    #undef  xheader

    #define xheader(name)                                                       \
        template<class callback_t>                                              \
        requires(                                                               \
            inc::can_callback<callback_t, ixx(uxx)>                             \
        )                                                                       \
        inline uxx name(uxx length, callback_t const & compare)

    // 说明：在升序序列中寻找刚好匹配搜索值的索引，如果不匹配则返回 not_exist
    xheader(match) {
        return match_core(length, compare).match;
    }

    // 说明：在升序序列中寻找不小于搜索值的索引，如果不匹配则返回 not_exist
    xheader(greater_equals) {
        auto result = match_core(length, compare);
        return result.match == not_exist ? result.grater_then_target : result.match;
    }

    // 说明：在升序序列中寻找不大于搜索值的索引，如果不匹配则返回 not_exist
    xheader(less_equals) {
        auto result = match_core(length, compare);
        return result.match == not_exist ? result.less_then_target : result.match;
    }

    #undef  xheader
}

#endif

xexport_space(mixc::algo_binary_search::origin)