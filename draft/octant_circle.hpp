#ifndef xpack_draft_octant_circle
#define xpack_draft_octant_circle
#pragma push_macro("xuser")
#undef  xuser
#define xuser mixc::draft_octant_circle
#include"define/base_type.hpp"
#pragma pop_macro("xuser")

namespace mixc::draft_octant_circle{
    /* 速度位移加速度画圆法
     * ==================================================
     * y 轴方向做初速度为 0 的匀加速运动
     * 0.5·ay·t^2 = (1 - 0.5·sqrt(2))·r
     * x 轴方向做初速度为 vx 的匀减速运动
     * vx·t - 0.5·ax·t^2 = 0.5·sqrt(2)·r
     * 在 45°角处水平速度等于垂直数组
     * vx - ax·t = bx·t
     * 
     * 下列算法作为用浮点数示意的八分画圆算法有以下特点
     * - 可并行化
     * - 可随机访问圆上任意角度对应的坐标
     * - 时间作为精度的刻度，被分得越细精度越高
     */ 
    template<class painter>
    inline void octant_circle(u32 r, painter const & draw){
        u32 w      = (u32)(f32(r) * 0.5 * sqrt(2.0));
        u32 t      = (r);
        u32 tt     = (t * t);
        f32 ay     = (f32(r - w) * 2.0 / tt);
        f32 vx     = (f32(w) - 0.5 * ay * tt) * 2.0 / t;
        f32 ax     = (vx * t - f32(w)) * 2.0 / tt;
        f32 vy     = (0);
        f32 sx     = (0);
        f32 sy     = (r);
        u32 last_x = u32(0);
        u32 last_y = u32(sy);
        u32 i      = 1;

        draw(0, last_x, last_y);

        while(vx > vy){
            vx    -= ax;
            vy    += ay;
            sx    += vx;
            sy    -= vy;
            auto x = (u32)round(sx);
            auto y = (u32)round(sy);

            if (last_x == x){
                last_y = last_y;
                continue;
            }

            draw(i, last_x = x, last_y = y);
            i     += 1;
        }
    }
}

#endif

namespace xuser::inc{
    using ::mixc::draft_octant_circle::octant_circle;
}
