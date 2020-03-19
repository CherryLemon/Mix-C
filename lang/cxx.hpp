#pragma once
#include"define/base_type.hpp"

namespace mixc{
    template<class item>
    struct cxx{
    private:
        inline static item empty = item(0);
        item *  ptr;
    public:
        uxx     length;

        cxx() : cxx(& empty, 0) {}
        cxx(item const * ptr, uxx length) : 
            ptr((item *)ptr), length(length) {
        }

        operator item *(){
            return ptr;
        }

        cxx backward(uxx value){
            cxx tmp = this[0];
            tmp.ptr += value;
            tmp.length -= uxx(value);
            return tmp;
        }

        cxx forward(uxx value){
            return backward(
                uxx(-ixx(value))
            );
        }

        cxx shorten(uxx length){
            cxx tmp = this[0];
            tmp.length -= length;
            return tmp;
        }
    };
}