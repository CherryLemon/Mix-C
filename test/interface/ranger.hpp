#ifndef xpack_test_interface_ranger
#define xpack_test_interface_ranger
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::test_interface_ranger::inc
#include"algo/insert.hpp"
#include"docker/array.hpp"
#include"interface/ranger.hpp"
#include"macro/xassert.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::test_interface_ranger{
    xtest(ranger){
        inc::array<u32, 32> x { 1u, 2u, 3u, 4u };
        inc::ranger<u32> a = x, b = x;

        // 误用：右边数组在赋值后就析构了，而 a 却指向该数组首地址
        // a = { 1u, 2u, 3u, 4u };
        xassert_eq(1, a[0]);
        xassert_eq(2, a[1]);
        xassert_eq(3, a[2]);
        xassert_eq(4, a[3]);

        a = x.range(co{0});
        xassert_eq(x.length(), a.length());

        for(uxx i = 0; i < a.length(); i++){
            xassert_eq(& x[i], & a[i]);
        }

        b = a.subseq(cc{1, 2});
        xassert_eq(2, b.length());
        xassert_eq(x[1], b[0]);
        xassert_eq(x[2], b[1]);

        b = a.subseq(cc{2, 1});
        xassert_eq(2, b.length());
        xassert_eq(x[1], b[1]);
        xassert_eq(x[2], b[0]);

        a = x.range(oc{-1, 0});
        xassert_eq(x.length(), a.length());

        for(uxx i = 0; i < a.length(); i++){
            xassert_eq(& x[a.length() - i - 1], & a[i]);
        }

        b = a.subseq(cc{3, 2});
        xassert_eq(2, b.length());
        xassert_eq(& a[3], & b[0]);
        xassert_eq(& a[2], & b[1]);

        b = a.subseq(cc{1, 1});
        xassert_eq(1, b.length());
        xassert_eq(& a[1], & b[0]);

        a = x.range(co{0, -2});
        xassert_eq(x.length(), a.length() + 1);

        for(uxx i = 0; i < a.length(); i++){
            xassert_eq(& x[i], & a[i]);
        }

        a = x.range(co{0, -3});
        xassert_eq(x.length(), a.length() + 2);

        for(uxx i = 0; i < a.length(); i++){
            xassert_eq(& x[i], & a[i]);
        }

        a = x.range(oo{0});
        xassert_eq(x.length(), a.length() + 1);

        for(uxx i = 0; i < a.length(); i++){
            xassert_eq(& x[i + 1], & a[i]);
        }
    };
}

#endif
