﻿#pragma once
#include"基本定义/迷你.h"

符号常量 自然数 引用标记 = 1;
符号常量 自然数 常量标记 = 2;

命名空间 元编程空间{
    模板<类 甲> 结构体 是枚举{
        静态 符号常量 布尔 结果 = __is_enum(甲);
    };
    模板<类 甲> 结构体 是指针{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<类 甲> 结构体 是指针<甲 *>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是引用{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<类 甲> 结构体 是引用<甲 &>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是非寄{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<类 甲> 结构体 是非寄<非寄 甲>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是常量{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<类 甲> 结构体 是常量<常量 甲>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是整数{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<> 结构体 是整数<I08>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是整数<I16>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是整数<I32>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是整数<I64>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是整型{
        静态 符号常量 布尔 结果 = 是整数<甲>::结果 || 是自然数<甲>::结果;
    };
    模板<类 甲> 结构体 是数值{
        静态 符号常量 布尔 结果 = 是整型<甲>::结果 || 是浮点数<甲>::结果 || 是枚举<甲>::结果;
    };
    模板<类 甲> 结构体 是联合体{
        静态 符号常量 布尔 结果 = __is_union(甲);
    };
    模板<类 甲> 结构体 是结构体{
        静态 符号常量 布尔 结果 = __is_class(甲);
    };
    模板<类 甲> 结构体 是自然数{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<> 结构体 是自然数<U08>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是自然数<U16>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是自然数<U32>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是自然数<U64>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是浮点数{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<> 结构体 是浮点数<F32>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<> 结构体 是浮点数<F64>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<类 甲> 结构体 是不可继承{
        静态 符号常量 布尔 结果 = 
            是引用<甲>::结果 || 是指针<甲>::结果 || 是非寄<甲>::结果 ||
            是数值<甲>::结果 || 是联合体<甲>::结果;
    };
    模板<类 甲, 类 乙> 结构体 类型相同{
        静态 符号常量 布尔 结果 = 否;
    };
    模板<类 甲> 结构体 类型相同<甲, 甲>{
        静态 符号常量 布尔 结果 = 是;
    };
    模板<布尔 选择甲, 类 甲, 类 乙>
    结构体 选择{
        定义 甲 结果;
    };
    模板<类 甲, 类 乙>
    结构体 选择<否, 甲, 乙>{
        定义 乙 结果;
    };
    模板<布尔 选择甲, 类 类型, 类型 甲, 类型 乙>
    结构体 选择值{
        静态 符号常量 类型 结果 = 甲;
    };
    模板<类 类型, 类型 甲, 类型 乙>
    结构体 选择值<否, 类型, 甲, 乙>{
        静态 符号常量 类型 结果 = 乙;
    };

    模板<类 甲>
    结构体 移除引用标记{
        定义 甲 结果;
    };
    模板<类 甲>
    结构体 移除引用标记<甲 &>{
        定义 甲 结果;
    };

    模板<类 甲>
    结构体 移除常量标记{
        定义 甲 结果;
    };
    模板<类 甲>
    结构体 移除常量标记<常量 甲>{
        定义 甲 结果;
    };

    模板<类 甲, 自然数 标记 = 0>
    结构体 移除{
    私有
        定义 类型名称 选择<(标记 & 引用标记) != 0, 类型名称 移除引用标记<甲>::结果, 甲>::结果 R0;
        定义 类型名称 选择<(标记 & 常量标记) != 0, 类型名称 移除常量标记<R0>::结果, R0>::结果 R1;
    公有
        定义 R1 作为结果;
    };

    模板<类 甲>
    结构体 类型{
        模板<类 乙>
        结构体 和类型{
            静态 符号常量 布尔 相同 = 元编程空间::类型相同<甲, 乙>::结果;
            静态 符号常量 布尔 不同 = 元编程空间::类型相同<甲, 乙>::结果 == 否;
        };

        静态 符号常量 布尔 是枚举     = 元编程空间::是枚举<甲>::结果;
        静态 符号常量 布尔 是指针     = 元编程空间::是指针<甲>::结果;
        静态 符号常量 布尔 是引用     = 元编程空间::是引用<甲>::结果;
        静态 符号常量 布尔 是非寄     = 元编程空间::是非寄<甲>::结果;
        静态 符号常量 布尔 是常量     = 元编程空间::是常量<甲>::结果;
        静态 符号常量 布尔 是整数     = 元编程空间::是整数<甲>::结果;
        静态 符号常量 布尔 是整型     = 元编程空间::是整型<甲>::结果;
        静态 符号常量 布尔 是数值     = 元编程空间::是数值<甲>::结果;
        静态 符号常量 布尔 是联合体   = 元编程空间::是联合体<甲>::结果;
        静态 符号常量 布尔 是结构体   = 元编程空间::是结构体<甲>::结果;
        静态 符号常量 布尔 是自然数   = 元编程空间::是自然数<甲>::结果;
        静态 符号常量 布尔 是浮点数   = 元编程空间::是浮点数<甲>::结果;
        静态 符号常量 布尔 不可继承   = 元编程空间::是不可继承<甲>::结果;

        静态 符号常量 布尔 不是枚举   = !是枚举     ;
        静态 符号常量 布尔 不是指针   = !是指针     ;
        静态 符号常量 布尔 不是引用   = !是引用     ;
        静态 符号常量 布尔 不是非寄   = !是非寄     ;
        静态 符号常量 布尔 不是常量   = !是常量     ;
        静态 符号常量 布尔 不是整数   = !是整数     ;
        静态 符号常量 布尔 不是整型   = !是整型     ;
        静态 符号常量 布尔 不是数值   = !是数值     ;
        静态 符号常量 布尔 不是联合体 = !是联合体   ;
        静态 符号常量 布尔 不是结构体 = !是结构体   ;
        静态 符号常量 布尔 不是自然数 = !是自然数   ;
        静态 符号常量 布尔 不是浮点数 = !是浮点数   ;
        静态 符号常量 布尔 可继承     = !不可继承   ;

        模板<类 乙>
        结构体 是{
        私有
            静态 符号常量 布尔 检测(乙 *){
                回递 ::是;
            }
            静态 符号常量 布尔 检测(空指针){
                回递 ::否;
            }
        公有
            静态 符号常量 布尔 的子类 = 检测((甲 *)0) && 和类型<乙>::不同;
        };

        模板<自然数 标记> 引用 移除 = 元编程空间::移除<甲, 标记>;
    };
    模板<类 函数类型> 结构体 函数参数个数;
    模板<类 返回值类型, 类 ... 剩余参数> 
    结构体 函数参数个数<返回值类型(剩余参数...)>{
        静态 符号常量 自然数 结果 = 参数数(剩余参数);
    };
    模板<类 函数类型> 结构体 函数返回值;
    模板<类 返回值类型, 类 ... 剩余参数> 
    结构体 函数返回值<返回值类型(剩余参数...)>{
        定义 返回值类型 类型;
    };
    模板<类 返回值类型, 类 对象, 类 ... 剩余参数> 
    结构体 函数返回值<返回值类型 (对象::*)(剩余参数...)>{
        定义 返回值类型 类型;
    };
    模板<类 函数类型, 整数 下标> 结构体 函数参数;
    模板<类 返回值类型, 类 参数, 类 ... 剩余参数> 
    结构体 函数参数<返回值类型(参数, 剩余参数...), 0>{
        定义 参数 类型;
    };
    模板<整数 下标, 类 返回值类型, 类 参数, 类 ... 剩余参数>
    结构体 函数参数<返回值类型(参数, 剩余参数...), 下标>{
        定义 类型名称 函数参数<
            返回值类型(剩余参数...), (
                下标 > 0 ? 下标 - 1 : -下标 == 参数数(剩余参数) ? 0 : 下标
            )
        >::类型 类型;
    };
    模板<自然数 下标, 类 甲, 类 乙, 类 ... 参数列表>
    结构体 参数{
        定义 类型名称 选择<下标 == 0, 甲, 类 参数<下标 - 1, 乙, 参数列表...>::类型>::结果 类型;
    };
    模板<自然数 下标, 类 甲, 类 乙>
    结构体 参数<下标, 甲, 乙>{
        定义 类型名称 选择<下标 == 0, 甲, 乙>::结果 类型;
    };
    模板<自然数 下标, 类 类型, 类型 甲, 类型 ... 乙>
    结构体 列表{
        静态 符号常量 
        类型 作为结果 = 选择值<下标 == 0, 类型, 甲, 列表<自然数(下标 - 1), 类型, 乙...>::作为结果>::结果;
    };
    模板<U32 下标, 类 类型, 类型 甲>
    结构体 列表<下标, 类型, 甲>{
        静态 符号常量 类型 作为结果 = 甲;
    };
    模板<类 返回值类型, 类 对象, 类 参数, 类 ... 剩余参数> 
    结构体 函数参数<返回值类型(对象::*)(参数, 剩余参数...), 0>{
        定义 参数 类型;
    };
    模板<U32 下标, 类 对象, 类 返回值类型, 类 参数, 类 ... 剩余参数> 
    结构体 函数参数<返回值类型 (对象::*)(参数, 剩余参数...), 下标>{
        定义 类型名称 函数参数<返回值类型(对象::*)(剩余参数...), 下标 - 1>::类型 类型;
    };

}

模板<类 甲>
结构体 类型 : 元编程空间::类型<甲>{};
模板<> 结构体 类型<I08> : 元编程空间::类型<I08>{
    静态 符号常量 I08 最大值 = I08(0x7f);
    静态 符号常量 I08 最小值 = I08(0x80);
};
模板<> 结构体 类型<I16> : 元编程空间::类型<I16>{
    静态 符号常量 I16 最大值 = I16(0x7fff);
    静态 符号常量 I16 最小值 = I16(0x8000);
};
模板<> 结构体 类型<I32> : 元编程空间::类型<I32>{
    静态 符号常量 I32 最大值 = I32(0x7fffffff);
    静态 符号常量 I32 最小值 = I32(0x80000000);
};
模板<> 结构体 类型<I64> : 元编程空间::类型<I64>{
    静态 符号常量 I64 最大值 = I64(0x7fffffffffffffff);
    静态 符号常量 I64 最小值 = I64(0x8000000000000000);
};
模板<> 结构体 类型<U08> : 元编程空间::类型<U08>{
    静态 符号常量 U08 最大值 = U08(0xff);
    静态 符号常量 U08 最小值 = U08(0);
};
模板<> 结构体 类型<U16> : 元编程空间::类型<U16>{
    静态 符号常量 U16 最大值 = U16(0xffff);
    静态 符号常量 U16 最小值 = U16(0);
};
模板<> 结构体 类型<U32> : 元编程空间::类型<U32>{
    静态 符号常量 U32 最大值 = U32(0xffffffff);
    静态 符号常量 U32 最小值 = U32(0);
};
模板<> 结构体 类型<U64> : 元编程空间::类型<U64>{
    静态 符号常量 U64 最大值 = U64(0xffffffffffffffff);
    静态 符号常量 U64 最小值 = U64(0);
};
模板<> 结构体 类型<F32>{
    静态 符号常量 F32 最大值 = (F32)3.40282347e+38;
    静态 符号常量 F32 最小值 = (F32)-3.40282347e+38;
};
模板<> 结构体 类型<F64>{
    静态 符号常量 F64 最大值 = 1.7976931348623157e+308;
    静态 符号常量 F64 最小值 = -1.7976931348623157e+308;
};

模板<自然数> 结构体 无符号{};
模板<> 结构体 无符号<1>{ 定义 U08 类型; };
模板<> 结构体 无符号<2>{ 定义 U16 类型; };
模板<> 结构体 无符号<4>{ 定义 U32 类型; };
模板<> 结构体 无符号<8>{ 定义 U64 类型; };

模板<布尔 条件> 结构体 假如{
    模板<类 甲>
    结构体 选{
        模板<类 乙>
        结构体 否则选{
            定义 类型名称 元编程空间::选择<条件, 甲, 乙>::结果 作为结果;
        };
    };
    模板<类 类型>
    结构体 取{
        模板<类型 甲>
        结构体 值{
            模板<类型 乙>
            结构体 否则取{
                静态 符号常量 类型 作为结果 = 元编程空间::选择值<条件, 类型, 甲, 乙>::结果;
            };
        };
    };
};
模板<类 甲>
结构体 函数{
    定义 类型名称 元编程空间::函数返回值<甲>::类型 返回值类型;
    模板<整数 下标>
    结构体 参数{
        定义 类型名称 元编程空间::函数参数<甲, 下标>::类型 类型;
    };
    静态 符号常量 自然数 参数个数 = 元编程空间::函数参数个数<甲>::结果;
};
模板<类 甲, 类 ... 剩余参数>
结构体 从{
    模板<自然数 下标>
    结构体 选择类型{
        定义 类型名称 元编程空间::参数<下标, 甲, 剩余参数...>::类型 作为结果;
    };
    模板<甲 首参, 甲 ... 列表>
    结构体 值{
        模板<自然数 下标>
        结构体 选择值{
            静态 符号常量 类型 作为结果 = 元编程空间::列表<下标, 甲, 首参, 列表...>::作为结果;
        };
    };
};