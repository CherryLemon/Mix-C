#ifndef xpack_gc_ref
#define xpack_gc_ref
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::gc_ref::inc
#include"define/nullref.hpp"
#include"docker/hashmap.hpp"
#include"dumb/dummy_type.hpp"
#include"dumb/struct_type.hpp"
#include"gc/self_management.hpp"
#include"gc/private/make_guide.hpp"
#include"gc/private/token.hpp"
#include"gc/private/tuple.hpp"
#include"instruction/index_of_last_set.hpp"
#include"interface/can_callback.hpp"
#include"lock/atom_swap.hpp"
#include"macro/xdebug.hpp"
#include"macro/xnew.hpp"
#include"macro/xis_nullptr.hpp"
#include"memory/allocator.hpp"
#include"memop/addressof.hpp"
#include"memop/cast.hpp"
#include"meta/is_based_on.hpp"
#include"meta/is_class.hpp"
#include"meta/is_same.hpp"
#include"meta/has_cast.hpp"
#include"meta/has_constructor.hpp"
#include"meta_ctr/cif.hpp"
#include"meta_seq/tlist.hpp"
#include"meta_seq/tin.hpp"
#include"meta_seq/vlist.hpp"
#include"mixc.hpp"
#pragma pop_macro("xuser")

namespace mixc::gc_ref{
    using namespace inc;
    using visited_ptr_t = voidp;

    xstruct(
        xname(info_t)
    )
        uxx can_arrive_root : 1;
        uxx visited         : sizeof(uxx) * 8 - 1;

        info_t() : 
            can_arrive_root(0), visited(0){}

        operator uxx (){
            return uxxp(this)[0];
        }
    $

    extern hashmap<visited_ptr_t, info_t>    gc_map;
    extern uxx                               degree_dvalue;
    extern visited_ptr_t                     root;
    extern bool                              can_free_whole_ring;
    static inline uxx                        empty_mem[32];
    static inline voidp                      empty_mem_ptr   = empty_mem;

    template<class final, class item_t, class attribute_t, bool is_array, bool is_binary_aligned_alloc>
    xstruct(
        xtmpl(meta, final, item_t, attribute_t, is_array, is_binary_aligned_alloc),
        xpubb(self_management),
        xasso(attribute_t),
        xasso(item_t)
    )
    private:
        using the_length =
            typename cif<
                is_array
            >::template select<
                token_plus
            >::template ces<
                token
            >;

        using the_item_t = 
            typename cif<
                is_array
            >::template select<
                item_t
            >::template ces<
                dummy_type
            >;

        using token_mix_t = token_mix<item_t, attribute_t, the_length>;

        static token_mix_t * null(){
            return (token_mix_t *)empty_mem_ptr;
        }

        template<class guide>
        bool routing() {
            using tuplep = tuple<attribute_t> *;

            bool can_arrive_root = false;

            // 无法通向 root 的死路
            if (mem == null()){
                return false;
            }

            xdebug(im_gc_meta_routing, mem, xtypeid(attribute_t).name, mem->owners(), the.length());

            // 我们把经过的节点存下来
            // 如果是首次经过就让它遍历成员节点
            // 如果该节点可以通往 root，那么曾经拜访过该节点的附和节点也可以通往根节点
            // 实际过程如下：
            // root --> 此节点 --> 附和节点 -> 此节点
            //             |   
            //             +-----> 其他节点 -> root
            // 在此时附和节点不能确定此节点是否还存在可以通往 root 的路径，所以指示暂时的让此节点的 visited 访问计数器加一
            // 而计数汇总的工作则是交给此节点来完成
            if (info_t & info = gc_map.get(mem); info == nullref){
                info_t        this_node;
                this_node.can_arrive_root       = mem == root;
                this_node.visited               = mem != root; // 除了根节点，其他节点都有直接的入边（表示从前一个节点到此节点）
                gc_map.set(mem, this_node);
                xdebug(im_gc_meta_routing, mem, "set to gc_map");

                // 如果数组元素 item_t 属于 guide 类型集合，那么就遍历数组元素
                if constexpr (tin<guide, item_t>){
                    can_arrive_root            |= tuple<void>::template routing<guide>(the, the.length());
                }
                
                // 如果 attribute_t 属于 guide 类型集合，就遍历该对象的字段
                if constexpr (tin<guide, attribute_t>){
                    attribute_t * ptr           = mem; // 李氏转换
                    can_arrive_root            |= tuplep(ptr)->template routing<guide>();
                }

                if (can_arrive_root){
                    info_t & this_node          = gc_map.get(mem);
                    this_node.can_arrive_root   = true;
                    degree_dvalue              += mem->owners() - this_node.visited;
                }
            }
            else if (info.can_arrive_root){
                xdebug(im_gc_meta_routing, "can_arrive_root");
                degree_dvalue                  -= 1;
                can_arrive_root                 = true;
            }
            else{
                info.visited                   += 1;
                xdebug(im_gc_meta_routing, info.visited);
            }
            return can_arrive_root;
        }

        template<class guide>
        bool can_release(){
            bool    state;
            root            = mem;

            // not can_arrive_root
            if (not the.template routing<guide>()){
                return false;
            }

            state           = degree_dvalue == 0;
            degree_dvalue   = 0;
            return state;
        }
    public:
        meta() : mem(null()) { }

        meta(the_t const & value){
            if (mem = value.mem; mem != null()) {
                mem->owners_inc();
            }
        }

        meta(the_t && object){
            the.mem = atom_swap(& object.mem, null());
        }
    protected:
        using item_initial_invoke   = inc::icallback<void(the_item_t * item_ptr)>;
        using item_initial_invokex  = inc::icallback<void(uxx i, the_item_t * item_ptr)>;

        template<class initial_invoke>
        requires(
            inc::has_cast<item_initial_invoke , initial_invoke> or 
            inc::has_cast<item_initial_invokex, initial_invoke>
        )
        meta(::length length, initial_invoke const & initial) {
            mem = alloc(length);

            for(uxx i = 0; i < length; i++) {
                if constexpr (inc::has_cast<item_initial_invoke, initial_invoke>){
                    initial(mem->item_ptr(i));
                }
                else{
                    initial(i, mem->item_ptr(i));
                }
            }
        }

        template<class ... args>
        requires(inc::has_constructor<item_t, void(args const & ...)>)
        meta(::length length, args const & ... list):
            meta(length, [&](the_item_t * item_ptr){
                xnew(item_ptr) the_item_t(list...);
            }) {
        }

        template<class ... args>
        requires(... && inc::has_cast<the_item_t, args>)
        meta(the_item_t const & first, args const & ... rest) {
            struct item_ref{
                the_item_t const & value;
                item_ref(the_item_t const & value) : value(value){}
            } items[] = {first, rest...};

            uxx count                            = 1 + sizeof...(args);
            mem                                  = alloc(count);

            for(uxx i = 0; i < count; i++) {
                xnew(mem->item_ptr(i)) the_item_t(items[i].value);
            }
        }

        template<class ... args>
        meta(::init_t, args const & ... list) {
            mem = alloc(::length(0), list...);
        }

        ~meta(){
            the = nullptr;
        }
    public:
        final & operator = (the_t const & object){
            /* 当 object == nullptr 时，实际上指向的是 the_t::null()
             * 对外而言依旧与 nullptr 比较判断是否是空对象
             * the_t::null() 是一块不为 nullptr 可用的内存，只是它不能当作对象实例使用
             * 具体情况：
             * 对于该函数 operator=(the_t const & object)
             * 假如 object.mem 为空时指向的是 nullptr
             * 那么在增加计数器时我们需要额外判断它是否为 nullptr
             * 此外下列步骤在多线程环境并不安全：
             * if (object.mem != nullptr){      // 前一刻不为 nullptr
             *     object.mem->owners_inc();    // 后一刻为 nullptr
             * }
             * 
             * 所以我们用静态的空对象 null() 代替 nullptr
             * 这样我们我们可以放心的直接增加计数器并且消除了线程不一致问题
             */
            object.mem->owners_inc();

            // 当有多个线程对该对象赋值时，该原子操作可以保证正确性
            the_t         old;
            token_mix_t * m     = atom_swap(& the.mem, object.mem);
            old.mem             = m;
            return thex;
        }

        final & operator = (the_t && object){
            the_t         old;
            token_mix_t * m     = atom_swap(& the.mem, object.mem);
            old.mem             = m;

            // 移除 object 对当前内存的所有权(右值移动)
            atom_swap(& object.mem, null());
            return thex;
        }

        xis_nullptr(mem == null());

        final & operator=(decltype(nullptr)){
            using guide = decltype(make_guide<final>());
            constexpr bool need_gc = guide::length != 0;
            token_mix_t *  ptr = null();
            uxx            cnt;

            if (ptr = atom_swap(& mem, ptr); ptr == null()) { // enter only once
                return thex;
            }

            // 后面的代码可以推送给后台 gc 线程
            auto old = (the_t *)& ptr;

            if (can_free_whole_ring){
                if constexpr (not need_gc){
                    if (ptr->owners_dec() == 0){
                        old->free();
                    }
                }
                else if (auto && i = gc_map.take_out(ptr); i.has_hold_value()){
                    if (i.can_arrive_root){
                        old->free();
                    }
                }
                return thex;
            }

            cnt = ptr->owners_dec();
            xdebug(im_gc__meta, xtypeid(attribute_t).name, cnt, ptr);

            if (cnt == 0){
                old->free();
            }
            else if constexpr (need_gc){
                if (old->template can_release<guide>()){
                    can_free_whole_ring = true;
                    gc_map.take_out(ptr);
                    old->free();
                    can_free_whole_ring = false;
                }
                gc_map.clear();
            }
            return thex;
        }

        bool operator == (the_t const & object) const {
            return mem == object.mem;
        }

        bool operator != (the_t const & object) const {
            return mem != object.mem;
        }

        void swap(the_t * object) {
            object->mem = atom_swap(& mem, object->mem);
        }

    protected:
        operator item_t * () const {
            return mem[0].item_ptr(0);
        }

        attribute_t * operator->() const {
            if constexpr (is_same<void, attribute_t>){
                return nullptr;
            }
            else{
                return mem->attribute_ptr();
            }
        }

        uxx length() const {
            return mem->this_length();
        }

        void length(uxx value) const {
            mem->this_length(value);
        }

        constexpr static uxx header_size(){
            return sizeof(token_mix_t);
        }

        uxx capacity() const {
            return real(mem->this_length());
        }
    private:
        mutable token_mix_t * mem;

        static uxx real(uxx length) {
            if constexpr (is_binary_aligned_alloc){
                length = uxx(1) << (index_of_last_set(length - 1) + 1);
            }
            return length;
        }

        template<class ... args> auto alloc(uxx length, args const & ... list) const {
            uxx real_length = real(length);
            return alloc_with_initial<token_mix_t>(size(real_length), length, list...);
        }

        void free() const {
            uxx length = capacity();
            free_with_destroy(mem, size(length));
        }

        memory_size size(uxx length) const {
            if constexpr (is_same<void, item_t>){
                return memory_size(
                    sizeof(token_mix_t)
                );
            }
            else{
                return memory_size(
                    sizeof(token_mix_t) + length * sizeof(item_t)
                );
            }
        }
    $
}

namespace mixc::gc_ref::origin{
    template<class final, class type>
    using ref_ptr = meta<final, void, type, false, false>;

    template<class final, class item_t, class attribute_t = void, bool is_binary_aligned_alloc = false>
    using ref_array = meta<final, item_t, attribute_t, true, is_binary_aligned_alloc>;
}

#endif

xexport_space(mixc::gc_ref::origin)