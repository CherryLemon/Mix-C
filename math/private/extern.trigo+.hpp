#ifdef xuser
    #undef xuser
#endif

#define xuser mixc::math_private
#include<x86intrin.h>
#include"configure.hpp"
#include"define/mfxx.hpp"
#include"macro/xalign.hpp"
#include"math/cos.hpp"
#include"math/sin.hpp"
#include"math/tan.hpp"
#include"memop/cast.hpp"

namespace mixc::math_cos{
    using namespace ::mixc::math_private;

    extern f64 cos(f64 x){
        f64 t  = inc::tan(0.5 * x);
        f64 tt = t * t;
        return (1.0 - tt) / (1 + tt);
    }
}

namespace mixc::math_sin{
    using namespace ::mixc::math_private;

    extern f64 sin(f64 x){
        f64 t = inc::tan(0.5 * x);
        return 2.0 * t / (1.0 + t * t);
    }
}

namespace mixc::math_tan{
    using namespace ::mixc::math_private;

    constexpr xalign(4096) f64 lut[] = {
        0.00000000000000000e+00, 6.25815075662750147e-02, 1.25655136575130968e-01, 1.89728610718059133e-01, 2.55341921221036267e-01, 3.23086244351745520e-01, 3.93626575925632758e-01, 4.67730025452391800e-01, 5.46302489843790513e-01, 6.30437673835884767e-01, 7.21484440990904420e-01, 8.21141801589894122e-01, 9.31596459944072461e-01, 1.05572763941191991e+00, 1.19742162923434797e+00, 1.36207197637622823e+00,
        0.00000000000000000e+00, 3.90626986833619184e-03, 7.81265894960000764e-03, 1.17192864712722449e-02, 1.56262716899438238e-02, 1.95337339058802886e-02, 2.34417924775976425e-02, 2.73505668364533010e-02, 3.12601765012559564e-02, 3.51707410928981533e-02, 3.90823803490153875e-02, 4.29952141386755494e-02, 4.69093624771025491e-02, 5.08249455404379742e-02, 5.47420836805446493e-02, 5.86608974398559835e-02,
        0.00000000000000000e+00, 2.44140629850638525e-04, 4.88281288805110976e-04, 7.32422005967265158e-04, 9.76562810440976629e-04, 1.22070373133016258e-03, 1.46484479773879572e-03, 1.70898603877091815e-03, 1.95312748353065521e-03, 2.19726916112222942e-03, 2.44141110064997431e-03, 2.68555333121834830e-03, 2.92969588193194862e-03, 3.17383878189552513e-03, 3.41798206021399423e-03, 3.66212574599245277e-03,
        0.00000000000000000e+00, 1.52587890636842379e-05, 3.05175781344739031e-05, 4.57763672194744231e-05, 6.10351563257912253e-05, 7.62939454605297370e-05, 9.15527346307953857e-05, 1.06811523843693599e-04, 1.22070313106329805e-04, 1.37329102425809430e-04, 1.52587891809237904e-04, 1.67846681263720653e-04, 1.83105470796363106e-04, 1.98364260414270692e-04, 2.13623050124548838e-04, 2.28881839934302972e-04,
        0.00000000000000000e+00, 9.53674316406539121e-07, 1.90734863281481296e-06, 2.86102294922655626e-06, 3.81469726564350372e-06, 4.76837158206739007e-06, 5.72204589849995005e-06, 6.67572021494291836e-06, 7.62939453139802974e-06, 8.58306884786701890e-06, 9.53674316435162058e-06, 1.04904174808535695e-05, 1.14440917973746004e-05, 1.23977661139164479e-05, 1.33514404304808469e-05, 1.43051147470695320e-05,
        0.00000000000000000e+00, 5.96046447753906956e-08, 1.19209289550781815e-07, 1.78813934326173781e-07, 2.38418579101567018e-07, 2.98023223876961948e-07, 3.57627868652358997e-07, 4.17232513427758586e-07, 4.76837158203161140e-07, 5.36441802978567082e-07, 5.96046447753976836e-07, 6.55651092529390825e-07, 7.15255737304809473e-07, 7.74860382080233203e-07, 8.34465026855662438e-07, 8.94069671631097603e-07,
        0.00000000000000000e+00, 3.72529029846191408e-09, 7.45058059692382826e-09, 1.11758708953857427e-08, 1.49011611938476574e-08, 1.86264514923095725e-08, 2.23517417907714881e-08, 2.60770320892334043e-08, 2.98023223876953213e-08, 3.35276126861572391e-08, 3.72529029846191579e-08, 4.09781932830810776e-08, 4.47034835815429985e-08, 4.84287738800049207e-08, 5.21540641784668442e-08, 5.58793544769287691e-08,
        0.00000000000000000e+00, 2.32830643653869629e-10, 4.65661287307739258e-10, 6.98491930961608887e-10, 9.31322574615478516e-10, 1.16415321826934815e-09, 1.39698386192321777e-09, 1.62981450557708740e-09, 1.86264514923095703e-09, 2.09547579288482666e-09, 2.32830643653869629e-09, 2.56113708019256592e-09, 2.79396772384643555e-09, 3.02679836750030519e-09, 3.25962901115417482e-09, 3.49245965480804445e-09,
        0.00000000000000000e+00, 1.45519152283668518e-11, 2.91038304567337036e-11, 4.36557456851005554e-11, 5.82076609134674072e-11, 7.27595761418342590e-11, 8.73114913702011108e-11, 1.01863406598567963e-10, 1.16415321826934814e-10, 1.30967237055301666e-10, 1.45519152283668518e-10, 1.60071067512035370e-10, 1.74622982740402222e-10, 1.89174897968769073e-10, 2.03726813197135925e-10, 2.18278728425502777e-10,
        0.00000000000000000e+00, 9.09494701772928238e-13, 1.81898940354585648e-12, 2.72848410531878471e-12, 3.63797880709171295e-12, 4.54747350886464119e-12, 5.45696821063756943e-12, 6.36646291241049767e-12, 7.27595761418342590e-12, 8.18545231595635414e-12, 9.09494701772928238e-12, 1.00044417195022106e-11, 1.09139364212751389e-11, 1.18234311230480671e-11, 1.27329258248209953e-11, 1.36424205265939236e-11,
        0.00000000000000000e+00, 5.68434188608080149e-14, 1.13686837721616030e-13, 1.70530256582424045e-13, 2.27373675443232059e-13, 2.84217094304040074e-13, 3.41060513164848089e-13, 3.97903932025656104e-13, 4.54747350886464119e-13, 5.11590769747272134e-13, 5.68434188608080149e-13, 6.25277607468888164e-13, 6.82121026329696178e-13, 7.38964445190504193e-13, 7.95807864051312208e-13, 8.52651282912120223e-13,
        0.00000000000000000e+00, 3.55271367880050093e-15, 7.10542735760100186e-15, 1.06581410364015028e-14, 1.42108547152020037e-14, 1.77635683940025046e-14, 2.13162820728030056e-14, 2.48689957516035065e-14, 2.84217094304040074e-14, 3.19744231092045084e-14, 3.55271367880050093e-14, 3.90798504668055102e-14, 4.26325641456060112e-14, 4.61852778244065121e-14, 4.97379915032070130e-14, 5.32907051820075139e-14,
        0.00000000000000000e+00, 2.22044604925031308e-16, 4.44089209850062616e-16, 6.66133814775093924e-16, 8.88178419700125232e-16, 1.11022302462515654e-15, 1.33226762955018785e-15, 1.55431223447521916e-15, 1.77635683940025046e-15, 1.99840144432528177e-15, 2.22044604925031308e-15, 2.44249065417534439e-15, 2.66453525910037570e-15, 2.88657986402540701e-15, 3.10862446895043831e-15, 3.33066907387546962e-15,
    };

    extern f64 tan(f64 x){
        using namespace inc;

        mf64 m    = x;
        auto deci = 
            m.real_exp() < 0 ? 
            m.real_dec() >> -m.real_exp() : 
            m.real_exp() << m.real_exp();
        auto decx = deci >> 4; // 4bit 剩余位
        auto remx = lut[16 * 12 + (deci & 0xf)];
        auto dec0 = _mm_set1_epi16(u16(decx >> 32));
        auto dec1 = _mm_set1_epi16(u16(decx >> 16));
        auto dec2 = _mm_set1_epi16(u16(decx));
        auto mask = _mm_setr_epi16(0xf, 0xf0, 0xf00, 0xf000, 0, 0, 0, 0);
        auto shft = _mm_setr_epi16(0x1000, 0x100, 0x10, 0x1, 0, 0, 0, 0);
        auto step = _mm_set1_epi32(64);
        auto ofs0 = _mm_setr_epi32(48, 32, 16, 0);
        auto ofs1 = _mm_add_epi32(ofs0, step);
        auto ofs2 = _mm_add_epi32(ofs1, step);
        auto msk0 = _mm_and_si128(dec0, mask);
        auto msk1 = _mm_and_si128(dec1, mask);
        auto msk2 = _mm_and_si128(dec2, mask);
        auto zero = _mm_setzero_si128();

        auto bas0 = _mm_mullo_epi16(msk0, shft);
        auto bas1 = _mm_mullo_epi16(msk1, shft);
        auto bas2 = _mm_mullo_epi16(msk2, shft);

        auto bas3 = _mm_srli_epi16(bas0, 12);
        auto bas4 = _mm_srli_epi16(bas1, 12);
        auto bas5 = _mm_srli_epi16(bas2, 12);

        auto bas6 = _mm_unpacklo_epi16(bas3, zero);
        auto bas7 = _mm_unpacklo_epi16(bas4, zero);
        auto bas8 = _mm_unpacklo_epi16(bas5, zero);

        auto idx0 = _mm_add_epi32(bas6, ofs0);
        auto idx1 = _mm_add_epi32(bas7, ofs1);
        auto idx2 = _mm_add_epi32(bas8, ofs2);

        auto lut0 = _mm256_i32gather_pd(lut, idx0, 8);
        auto lut1 = _mm256_i32gather_pd(lut, idx1, 8);
        auto lut2 = _mm256_i32gather_pd(lut, idx2, 8);
        auto one0 = _mm256_set1_pd(1.0);
        auto sum0 = _mm256_add_pd(lut0, lut1);
        auto mul0 = _mm256_mul_pd(lut0, lut1);
        auto mix0 = _mm256_sub_pd(one0, mul0);

        auto div0 = _mm256_div_pd(sum0, mix0);
        auto sum1 = _mm256_add_pd(div0, lut2);
        auto mul1 = _mm256_mul_pd(div0, lut2);
        auto mix1 = _mm256_sub_pd(one0, mul1);
        auto div1 = _mm256_div_pd(sum1, mix1);
        auto hlf0 = _mm256_extractf128_pd(div1, 0); /*低 128 bit*/
        auto hlf1 = _mm256_extractf128_pd(div1, 1); /*高 128 bit*/
        auto one1 = _mm256_extractf128_pd(one0, 0); /*低 128 bit*/

        auto sum2 = _mm_add_pd(hlf0, hlf1);
        auto mul2 = _mm_mul_pd(hlf0, hlf1);
        auto mix2 = _mm_sub_pd(one1, mul2);
        auto div2 = _mm_div_pd(sum2, mix2);

        auto f0   = cast<f64>(_mm_extract_epi64(*(__m128i *)& div2, 0));
        auto f1   = cast<f64>(_mm_extract_epi64(*(__m128i *)& div2, 1));
        auto f2   = remx;
        auto r    = ((f0 + f1) + (1.0 - f0 * f1) * f2) / ((1.0 - f0 * f1) - f2 * (f0 * f1));
        return m.sign ? -r : r;
    }
}
