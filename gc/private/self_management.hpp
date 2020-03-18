/*
在 GC 组件中，self_management用于判定一个类是否带有 GC 成分
判定方法 is_based_on：
    我们定义：只要是继承了 self_management 的类都应该具有以下私有方法
        - routing
        - clear_footmark
    目前版本的 GC 尚处于完善与发展阶段，以上两个方法的接口签名有待商榷，
    暂时未显式申明在 self_management 中
*/

#pragma once
#include"define/base_type.hpp"

namespace mixc{
    struct self_management{};
}