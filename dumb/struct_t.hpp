#ifndef xpack_dumb_struct_t
#define xpack_dumb_struct_t
    #pragma push_macro("xuser")
    #undef  xuser
    #define xuser mixc::dumb_struct_t
    #include"define/base_type.hpp"
    #include"macro/xstruct.hpp"
    #include"meta/is_class.hpp"
    #pragma pop_macro("xuser")

    namespace mixc::dumb_struct_t{
        template<class type, bool is_class> struct struct_t;
        template<class type>
        xstruct(
            ximx(struct_t<type, true>),
            xpub(type)
        )
            using type::type;
        $

        template<class type>
        xstruct(
            ximx(struct_t<type, false>),
            xitm(data, type)
        )
            template<class ... args>
            struct_t(args const & ... list) : 
                data(list...){
            }

            operator type & (){
                return data;
            }

            operator const type & () const {
                return data;
            }
        $

        template<>
        xstruct(
            ximx(struct_t<void, false>)
        ) $
    }

    namespace mixc::dumb_struct_t::origin{
        template<class type>
        using struct_t = mixc::dumb_struct_t::struct_t<type, inc::is_class<type>>;
    }

#endif

namespace xuser::inc{
    using ::mixc::dumb_struct_t::origin::struct_t;
}
