#ifndef xusing_lang_cxx
#include"lang/private/cxx.hpp"
#endif

#ifndef xpack_lang_cxx_ph
#define xpack_lang_cxx_ph
#pragma push_macro("xuser")
#pragma push_macro("xusing_lang_cxx")
#undef  xusing_lang_cxx
#undef  xuser
#define xuser mixc::lang_cxx_ph::inc
#include"define/base_type.hpp"
#include"interface/can_alloc.hpp"
#include"lang/cxx/strlize.hpp"
#include"lang/cxx.hpp"
#include"macro/xdebug_fail.hpp"
#include"macro/xexport.hpp"
#include"memop/cast.hpp"
#include"memop/copy.hpp"
#include"memop/fill.hpp"
#include"meta/has_cast.hpp"
#include"meta/is_based_on.hpp"
#include"meta/is_origin_array.hpp"
#include"meta/is_ptr.hpp"
#include"meta/item_origin_of.hpp"
#include"meta/remove_ptr.hpp"
#include"meta/unsigned_type.hpp"
#include"meta_ctr/cif.hpp"
#pragma pop_macro("xusing_lang_cxx")
#pragma pop_macro("xuser")

namespace mixc::lang_cxx_ph{
    /*
     * h{}  hex
     * H{}  upper hex 
     * zh{} hex with leading zero
     * zH{} upper hex with leading zero
     * x{}  hex with 0x prefix
     * X{}  upper hex with 0x prefix
     * zx{} hex with 0x prefix and leading zero
     * zX{} upper hex with 0x prefix and leading zero
     * 
     * v{}  normal multi-value
     * f{}  decimal(pending)
     * 
     * b{}  bin
     * zb{} bin with leading zero
     * 
     * .l() align left
     * .r() align right
     * .c() align center
     * 
     * more... to be continue
     */

    xstruct(
        xname(place_holder_group)
    ) $

    template<class final, class type = void> struct base_ph;
    template<class final>
    xstruct(
        xspec(base_ph, final, void),
        xpubb(place_holder_group)
    )
    protected:
        u08         align_mode          : 2  = 0;
        u08         numeration          : 6  = 10;
        char        left_padding_char        = ' ';
        char        right_padding_char       = ' ';
        u32         align_width              = 0;

        enum{
            align_center,
            align_left,
            align_right,
        };
    public:
        final & c(uxx align_center_width, char left_padding_char, char right_padding_char){
            the.align_mode              = u08(align_center);
            the.align_width             = u32(align_center_width);
            the.left_padding_char       = left_padding_char;
            the.right_padding_char      = right_padding_char;
            return thex;
        }

        final & c(uxx align_center_width, char padding_char = ' '){
            return c(align_center_width, padding_char, padding_char);
        }

        final & l(uxx align_left_width, char padding_char = ' '){
            the.align_mode              = u08(align_left);
            the.align_width             = u32(align_left_width);
            the.right_padding_char      = padding_char;
            return thex;
        }

        final & r(uxx align_right_width, char padding_char = ' '){
            the.align_mode              = u08(align_right);
            the.align_width             = u32(align_right_width);
            the.left_padding_char       = padding_char;
            return thex;
        }

        template<class item_t>
        item_t * align(uxx length, inc::ialloc<item_t> alloc){
            if (the_t::align_width == 0 or the_t::align_width <= length){
                return alloc(length);
            }

            auto mem       = alloc(the_t::align_width);
            auto pad_width = the_t::align_width - length;
            auto half      = pad_width / 2;

            switch(the_t::align_mode){
            case the_t::align_center:
                inc::fill_with_operator(mem, left_padding_char, half);
                inc::fill_with_operator(length + (mem += half), right_padding_char, pad_width - half);
                return mem;
            case the_t::align_left:
                inc::fill_with_operator(mem + length, right_padding_char, pad_width);
                return mem;
            default: // align_right
                inc::fill_with_operator(mem, left_padding_char, pad_width);
                return mem + pad_width;
            }
        }
    $

    template<class final, class type>
    xstruct(
        xtmpl(base_ph, final, type),
        xpubb(base_ph<final, void>),
        xprof(value, type)
    )
    public:
        constexpr base_ph(type const & value) : 
            value(value){}
    $

    #define xopt                                                                            \
        inc::c08 operator >> (inc::ialloc<char> alloc) { return output(alloc); }            \
        inc::c16 operator >> (inc::ialloc<char16_t> alloc) { return output(alloc); }        \
        template<class item_t>                                                              \
        inc::cxx<item_t> output(inc::ialloc<item_t> alloc)

    template<
        class             final, 
        class             type, 
        inc::numeration_t n,
        bool              with_prefix, 
        bool              keep_leading_zero, 
        auto              lut>
    struct num : base_ph<final, type>{
        using the_t = base_ph<final, type>;
        using the_t::the_t;
        num(){}

        xopt{
            auto deformation = [this](){
                if constexpr (inc::is_ptr<type>){
                    return uxx(the_t::value);
                }
                else{
                    return the_t::value;
                }
            };
            return inc::cxx<item_t>(deformation(), n, lut, [this, alloc](uxx length){
                auto klz_length = sizeof(type) * 8; // keep leading zero length

                if constexpr (n == inc::numeration_t::hex){
                    klz_length /= 4;
                }
                else if constexpr (n == inc::numeration_t::oct){
                    klz_length = klz_length / 3 + (klz_length % 3 != 0);
                }
                else if constexpr (n == inc::numeration_t::bin){
                    ; // klz_length = klz_length;
                }

                auto new_length = (keep_leading_zero ? klz_length : length);
                auto zero_count = new_length - length;
                auto mem        = the.template align<item_t>(
                    new_length += (with_prefix ? 2 : 0), 
                    alloc
                );

                if constexpr (with_prefix){ // only in hex
                    inc::copy_with_operator(mem, "0x", 2);
                    mem += 2;
                }
                if (zero_count){
                    inc::fill_with_operator(mem, '0', zero_count);
                    mem += zero_count;
                }
                return mem;
            });
        }
    };

    template<class final, class ... args> struct v;
    template<class final, class a0, class ... args>
    struct v<final, a0, args...> : v<final, args...> {
        using base_t = v<final, args...>;

        constexpr v(a0 const & first, args const & ... rest) : 
            base_t(rest...), item(first) {
        }

        template<class item_t>
        inc::cxx<item_t> output(uxx old_length){
            inc::cxx<item_t> buf;

            auto link = [&](uxx this_length){
                base_t * base = this;
                buf = base->template output<item_t>(old_length + this_length);
                buf = buf.forward(this_length);
                return (item_t *)buf;
            };

            if constexpr (inc::is_based_on<place_holder_group, a0>){
                item.template output<item_t>(link);
            }
            else{
                inc::cxx<item_t>(item, link);
            }
            return buf;
        }
    private:
        static auto invoke(){
            if constexpr (inc::is_origin_array<a0>){
                return (const inc::item_origin_of<a0> **)nullptr;
            }
            else{
                return (a0 *)nullptr;
            }
        }

        inc::remove_ptr< decltype(invoke()) > item;
    };

    template<class final>
    struct v<final> : base_ph<final> {
        using the_t = base_ph<final>;

        template<class item_t>
        inc::cxx<item_t> output(uxx length){
            return { 
                the.template align<item_t>(
                    length, 
                    inc::cast<inc::ialloc<item_t>>(alloc)
                ) + length, 
                0
            };
        }
    protected:
        inc::ialloc<void> alloc;
    };

    constexpr bool with_prefix       = true;
    constexpr bool keep_leading_zero = true;

    #define xnum(name,equivalent_type_t,numeration,prefix,leading_zero,lut)                             \
        template<class type>                                                                            \
        struct name : base_ph<name<type>, equivalent_type_t>{                                           \
            using base_t = base_ph<name<type>, equivalent_type_t>;                                      \
            using final  = num<name<type>, equivalent_type_t, numeration, prefix, leading_zero, lut>;   \
            name(){}                                                                                    \
            name(type const & value) :                                                                  \
                base_t(equivalent_type_t(value)){                                                       \
            }                                                                                           \
            xopt{                                                                                       \
                return thex.template output<item_t>(alloc);                                             \
            }                                                                                           \
        }
    
    #define xhex(name,prefix,leading_zero,lut)      \
        xnum(name,inc::unsigned_type<type>,inc::numeration_t::hex,prefix,leading_zero,lut)

    #define xbin(name,prefix,leading_zero,lut)      \
        xnum(name,inc::unsigned_type<type>,inc::numeration_t::bin,prefix,leading_zero,lut)

    #define xoct(name,prefix,leading_zero,lut)      \
        xnum(name,inc::unsigned_type<type>,inc::numeration_t::oct,prefix,leading_zero,lut)
}

namespace mixc::lang_cxx_ph::origin::ph{
    using mixc::lang_cxx_ph::place_holder_group;

    xhex(h , not with_prefix, not keep_leading_zero, inc::lower);
    xhex(H , not with_prefix, not keep_leading_zero, inc::upper);
    xhex(zh, not with_prefix,     keep_leading_zero, inc::lower);
    xhex(zH, not with_prefix,     keep_leading_zero, inc::upper);

    xhex(x ,     with_prefix, not keep_leading_zero, inc::lower);
    xhex(X ,     with_prefix, not keep_leading_zero, inc::upper);
    xhex(zx,     with_prefix,     keep_leading_zero, inc::lower);
    xhex(zX,     with_prefix,     keep_leading_zero, inc::upper);

    xoct(o , not with_prefix, not keep_leading_zero, inc::lower);
    xoct(zo, not with_prefix,     keep_leading_zero, inc::lower);

    xbin(b , not with_prefix, not keep_leading_zero, inc::lower);
    xbin(zb, not with_prefix,     keep_leading_zero, inc::lower);

    template<class a0, class ... args>
    struct v : mixc::lang_cxx_ph::v<v<a0, args...>, a0, args...>{
        using base_t = mixc::lang_cxx_ph::v<v<a0, args...>, a0, args...>;

        v(a0 const & first, args const & ... rest) : 
            base_t(first, rest...){}

        xopt {
            inc::copy(xref base_t::alloc, alloc);
            return base_t::template output<item_t>(0);
        }
    };
}

namespace mixc::lang_cxx_ph{
    using namespace origin;

    template<class ... args> struct phg_core;
    template<class a0, class ... args>
    struct phg_core<a0, args...> : phg_core<args...>{
    private:
        typename inc::cif<
            inc::is_based_on<place_holder_group, a0>
        >::template select<
            a0
        >::template cei<
            inc::has_cast<asciis, a0> or not inc::is_ptr<a0>
        >::template select<
            ph::v<a0>
        >::template ces<
            ph::zX<a0>
        > item;

        using base_t = phg_core<args...>;
    public:
        phg_core(a0 const & first, args const & ... list) : 
            base_t(list...), item(first) {
        }

        template<class item_t>
        inc::cxx<item_t> output(uxx old_length){
            inc::cxx<item_t> ret;
            item.template output<item_t>([&](uxx length) -> item_t * {
                base_t * base = this;
                ret = base->template output<item_t>(old_length + length);
                ret = ret.forward(length);
                return ret;
            });
            return ret;
        }
    };

    template<> struct phg_core<>{
        inc::ialloc<void> alloc;

        template<class item_t>
        inc::cxx<item_t> output(uxx length){
            return { (item_t *)alloc(length) + length, 0 };
        }
    };
}

namespace mixc::lang_cxx_ph::origin::ph{ // place_holder
    template<class a0, class ... args>
    struct phg{ // place_holder group
        phg(a0 const & first, args const & ... list)
            : items(first, list...){
        }

        xopt {
            inc::copy(xref items.alloc, alloc);
            return items.template output<item_t>(0);
        }
    private:
        phg_core<a0, args...> items;
    };
}

#undef  xbin
#undef  xoct
#undef  xhex
#undef  xnum
#undef  xopt 
#undef  xmate
#endif

xexport_space(mixc::lang_cxx_ph::origin)