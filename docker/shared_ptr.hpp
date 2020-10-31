#ifndef xpack_docker_shared_ptr
#define xpack_docker_shared_ptr
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::docker_shared_ptr
#include"gc/ref.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::docker_shared_ptr{
    template<class type> struct shared_ptr;
    template<class type>
    struct shared_ptr : inc::ref_ptr<shared_ptr<type>, type>{
        using the_t  = shared_ptr<type>;
        using base_t = inc::ref_ptr<shared_ptr<type>, type>;
        using base_t::operator=;
        using base_t::operator==;
        using base_t::operator!=;
    public:
        shared_ptr() = default;

        shared_ptr(type const & value) : 
            base_t(::ini_now, value){
        }

        explicit shared_ptr(::ini) : 
            base_t(::ini_now) {}

        template<class ... args>
        explicit shared_ptr(::ini, args const & ... list) : 
            base_t(::ini_now, list...) {}

        template<class ... args>
        shared_ptr<type> & operator()(::ini, args const & ... list){
            base_t::operator=(nullptr);
            new (this) base_t(::length(0), list...);
            return the;
        }

        operator type & () {
            return * base_t::operator->();
        }

        operator type const & () const {
            return * base_t::operator->();
        }

        type const * operator->() const {
            return base_t::operator->();
        }

        type * operator->() {
            return base_t::operator->();
        }

        type const & operator= (type const & value){
            if (the != nullptr){
                operator type & () = value;
            }
            else{
                new (this) the_t(value);
            }
            return value;
        }
    };
}

#endif

xexport(mixc::docker_shared_ptr::shared_ptr)
