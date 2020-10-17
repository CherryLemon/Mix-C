/* 模块：adapter_array_access
 * 类型：适配器
 * 功能：通过具有 ::operator[] 以及 ::length() 函数的结构，对外提供一致的访问功能
 * 用法：
 * TODO======================================================================================
 */

#ifndef xpack_docker_adapter_array_access
#define xpack_docker_adapter_array_access
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::docker_adapter_array_access
#include"interface/seqptr.hpp"
#include"interface/iterator.hpp"
#include"meta/is_integer.hpp"
#include"memop/swap.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::docker_adapter_array_access {
    /* - base_t 为被此结构继承的结构类型，要求 base_t 具有以下函数
     *   item_t & base_t::operator[](uxx) const;
     *   uxx      base_t::length() const;
     * - item_t 为 base_t 元素类型
     */
    template<class base_t, class item_t>
    struct adapter_array_access : base_t {
        using the_t             = base_t;
        using base_t::base_t;
        using base_t::operator[];
        using base_t::length;

        xseqptr(item_t);
    private:
        /* 函数：随机访问接口
         * 参数：
         * - index 为整数类型
         * 返回：
         * - 指定索引的元素
         * 注意：
         * - 该函数支持回绕索引，即索引 -1 表示最后一个元素
         */
        template<inc::is_integer number_t>
        auto & random_access(number_t const & index) const {
            if constexpr (number_t(-1) > 0) {
                return base_t::operator[](uxx(index));
            }
            else {
                return base_t::operator[](index >= 0 ? uxx(index) : uxx(length() + index));
            }
        }

        /* 函数：顺序访问模板
         * 参数：
         * - invoke 为元素访问回调，支持的签名如下
         *   void   invoke(item_t & value);
         *   void   invoke(item_t const & value);
         *   loop_t invoke(item_t & value);
         *   loop_t invoke(item_t const & value);
         *   void   invoke(uxx index, item_t & value);
         *   void   invoke(uxx index, item_t const & value);
         *   loop_t invoke(uxx index, item_t & value);
         *   loop_t invoke(uxx index, item_t const & value);
         * - itv 为访问区间
         */
        template<auto mode, class invoke_t>
        void foreach_template(invoke_t invoke, inc::iinterval itv = co{0, -1}) const {
            itv.normalize(the.length());

            uxx    l     = itv.left();
            uxx    r     = itv.right();
            uxx    step  = l <= r ? uxx(1) : uxx(-1);
            uxx    index = 0;
            loop_t state = loop_t::go_on;

            for(;; l += step){
                xitr_switch(mode, index, state, invoke, the[l]);
                
                if (l == r or state == loop_t::finish){
                    break;
                }
            }
        }
    public:
    
        /* 函数：下标随机访问
         * 参数：
         * - index 为整数类型
         * 返回：
         * - 指定索引的元素
         * 注意：
         * - 该函数支持回绕索引，即索引 -1 表示最后一个元素
         */
        template<inc::is_integer number_t>
        item_t & operator[] (number_t const & index) {
            return random_access(index);
        }

        /* 函数：下标随机访问（const 修饰）
         * 参数：
         * - index 为整数类型
         * 返回：
         * - 指定索引的元素
         * 注意：
         * - 该函数支持回绕索引，即索引 -1 表示最后一个元素
         */
        template<inc::is_integer number_t>
        item_t const & operator[] (number_t const & index) const {
            return random_access(index);
        }

        xitr_foreach (item_t &)
        xitr_foreachx(item_t &)
        xitr_foreach_const (item_t const &)
        xitr_foreachx_const(item_t const &)
    };
}

#endif

xexport(mixc::docker_adapter_array_access::adapter_array_access)