#ifdef xuser
    #undef xuser
#endif

#define xuser mixc::math_expe
#include"configure.hpp"
#include"define/inf.hpp"
#include"define/mfxx.hpp"
#include"math/expe.hpp"
#include"math/div.hpp"
#include"mixc.hpp"

namespace mixc::math_expe{
    #if xuse_math_expe_lut6x16 
    constexpr uxx step              = 4;
    constexpr f64 lut [][1 << step] = {
        {1.000000000000000000e+00, 1.000000059604646552e+00, 1.000000119209296656e+00, 1.000000178813950313e+00, 1.000000238418607523e+00, 1.000000298023268286e+00, 1.000000357627932601e+00, 1.000000417232600469e+00, 1.000000476837271890e+00, 1.000000536441946863e+00, 1.000000596046625390e+00, 1.000000655651307468e+00, 1.000000715255993100e+00, 1.000000774860682284e+00, 1.000000834465375022e+00, 1.000000894070071311e+00, },
        {1.000000000000000000e+00, 1.000000953674771154e+00, 1.000001907350451803e+00, 1.000002861027041949e+00, 1.000003814704541592e+00, 1.000004768382950733e+00, 1.000005722062269373e+00, 1.000006675742497513e+00, 1.000007629423635155e+00, 1.000008583105682297e+00, 1.000009536788638942e+00, 1.000010490472505091e+00, 1.000011444157280743e+00, 1.000012397842965901e+00, 1.000013351529560565e+00, 1.000014305217064736e+00, },
        {1.000000000000000000e+00, 1.000015258905478414e+00, 1.000030518043791024e+00, 1.000045777414941384e+00, 1.000061037018933045e+00, 1.000076296855769562e+00, 1.000091556925454486e+00, 1.000106817227991372e+00, 1.000122077763383771e+00, 1.000137338531635238e+00, 1.000152599532749324e+00, 1.000167860766729584e+00, 1.000183122233579571e+00, 1.000198383933302839e+00, 1.000213645865902939e+00, 1.000228908031383427e+00, },
        {1.000000000000000000e+00, 1.000244170429747855e+00, 1.000488400478694473e+00, 1.000732690161397100e+00, 1.000977039492416535e+00, 1.001221448486317134e+00, 1.001465917157666808e+00, 1.001710445521037025e+00, 1.001955033591002812e+00, 1.002199681382142754e+00, 1.002444388909038995e+00, 1.002689156186277240e+00, 1.002933983228446758e+00, 1.003178870050140376e+00, 1.003423816665954486e+00, 1.003668823090489045e+00, },
        {1.000000000000000000e+00, 1.003913889338347573e+00, 1.007843097206447977e+00, 1.011787683559331491e+00, 1.015747708586685747e+00, 1.019723232713774154e+00, 1.023714316602357916e+00, 1.027721021151621656e+00, 1.031743407499102669e+00, 1.035781537021623803e+00, 1.039835471336229998e+00, 1.043905272301128493e+00, 1.047991002016632700e+00, 1.052092722826109788e+00, 1.056210497316931968e+00, 1.060344388321431496e+00, },
        {1.000000000000000000e+00, 1.064494458917859426e+00, 1.133148453066826309e+00, 1.206230249420980699e+00, 1.284025416687741467e+00, 1.366837941173796340e+00, 1.454991414618201307e+00, 1.548830298634133062e+00, 1.648721270700128103e+00, 1.755054656960298505e+00, 1.868245957432222344e+00, 1.988737469582291758e+00, 2.117000016612674584e+00, 2.253534787213208447e+00, 2.398875293967097803e+00, 2.553589458062926746e+00, },
    };
    #elif xuse_math_expe_lut3x256
    constexpr uxx step              = 8;
    constexpr f64 lut [][1 << step] = {
        {1.000000000000000000e+00, 1.000000059604646552e+00, 1.000000119209296656e+00, 1.000000178813950313e+00, 1.000000238418607523e+00, 1.000000298023268286e+00, 1.000000357627932601e+00, 1.000000417232600469e+00, 1.000000476837271890e+00, 1.000000536441946863e+00, 1.000000596046625390e+00, 1.000000655651307468e+00, 1.000000715255993100e+00, 1.000000774860682284e+00, 1.000000834465375022e+00, 1.000000894070071311e+00, 1.000000953674771154e+00, 1.000001013279474549e+00, 1.000001072884181497e+00, 1.000001132488891997e+00, 1.000001192093606051e+00, 1.000001251698323657e+00, 1.000001311303044816e+00, 1.000001370907769527e+00, 1.000001430512497791e+00, 1.000001490117229608e+00, 1.000001549721964978e+00, 1.000001609326703900e+00, 1.000001668931446375e+00, 1.000001728536192403e+00, 1.000001788140941984e+00, 1.000001847745695117e+00, 1.000001907350451803e+00, 1.000001966955212042e+00, 1.000002026559975833e+00, 1.000002086164743177e+00, 1.000002145769514074e+00, 1.000002205374288524e+00, 1.000002264979066526e+00, 1.000002324583848081e+00, 1.000002384188633189e+00, 1.000002443793421849e+00, 1.000002503398214062e+00, 1.000002563003009828e+00, 1.000002622607809147e+00, 1.000002682212612018e+00, 1.000002741817418443e+00, 1.000002801422228419e+00, 1.000002861027041949e+00, 1.000002920631859031e+00, 1.000002980236679666e+00, 1.000003039841503854e+00, 1.000003099446331594e+00, 1.000003159051162887e+00, 1.000003218655997733e+00, 1.000003278260836132e+00, 1.000003337865678083e+00, 1.000003397470523587e+00, 1.000003457075372644e+00, 1.000003516680225253e+00, 1.000003576285081416e+00, 1.000003635889941131e+00, 1.000003695494804398e+00, 1.000003755099671219e+00, 1.000003814704541592e+00, 1.000003874309415518e+00, 1.000003933914292996e+00, 1.000003993519174028e+00, 1.000004053124058612e+00, 1.000004112728946748e+00, 1.000004172333838438e+00, 1.000004231938733680e+00, 1.000004291543632475e+00, 1.000004351148534823e+00, 1.000004410753440723e+00, 1.000004470358350176e+00, 1.000004529963263182e+00, 1.000004589568179741e+00, 1.000004649173099852e+00, 1.000004708778023516e+00, 1.000004768382950733e+00, 1.000004827987881503e+00, 1.000004887592815825e+00, 1.000004947197753700e+00, 1.000005006802695128e+00, 1.000005066407640108e+00, 1.000005126012588641e+00, 1.000005185617540727e+00, 1.000005245222496366e+00, 1.000005304827455557e+00, 1.000005364432418301e+00, 1.000005424037384598e+00, 1.000005483642354448e+00, 1.000005543247327850e+00, 1.000005602852304805e+00, 1.000005662457285313e+00, 1.000005722062269373e+00, 1.000005781667256987e+00, 1.000005841272248153e+00, 1.000005900877242871e+00, 1.000005960482241143e+00, 1.000006020087242967e+00, 1.000006079692248344e+00, 1.000006139297257274e+00, 1.000006198902269756e+00, 1.000006258507285791e+00, 1.000006318112305379e+00, 1.000006377717328520e+00, 1.000006437322355213e+00, 1.000006496927385459e+00, 1.000006556532419258e+00, 1.000006616137456609e+00, 1.000006675742497513e+00, 1.000006735347541971e+00, 1.000006794952589980e+00, 1.000006854557641543e+00, 1.000006914162696658e+00, 1.000006973767755326e+00, 1.000007033372817547e+00, 1.000007092977883320e+00, 1.000007152582952646e+00, 1.000007212188025525e+00, 1.000007271793101957e+00, 1.000007331398181941e+00, 1.000007391003265479e+00, 1.000007450608352568e+00, 1.000007510213443211e+00, 1.000007569818537406e+00, 1.000007629423635155e+00, 1.000007689028736455e+00, 1.000007748633841309e+00, 1.000007808238949715e+00, 1.000007867844061674e+00, 1.000007927449177186e+00, 1.000007987054296251e+00, 1.000008046659418868e+00, 1.000008106264545038e+00, 1.000008165869674761e+00, 1.000008225474808036e+00, 1.000008285079944865e+00, 1.000008344685085246e+00, 1.000008404290229179e+00, 1.000008463895376666e+00, 1.000008523500527705e+00, 1.000008583105682297e+00, 1.000008642710840442e+00, 1.000008702316002139e+00, 1.000008761921167389e+00, 1.000008821526336192e+00, 1.000008881131508548e+00, 1.000008940736684457e+00, 1.000009000341863918e+00, 1.000009059947046932e+00, 1.000009119552233498e+00, 1.000009179157423618e+00, 1.000009238762617290e+00, 1.000009298367814515e+00, 1.000009357973015293e+00, 1.000009417578219623e+00, 1.000009477183427506e+00, 1.000009536788638942e+00, 1.000009596393853931e+00, 1.000009655999072472e+00, 1.000009715604294566e+00, 1.000009775209520213e+00, 1.000009834814749413e+00, 1.000009894419982165e+00, 1.000009954025218470e+00, 1.000010013630458328e+00, 1.000010073235701739e+00, 1.000010132840948702e+00, 1.000010192446199219e+00, 1.000010252051453287e+00, 1.000010311656710909e+00, 1.000010371261972084e+00, 1.000010430867236811e+00, 1.000010490472505091e+00, 1.000010550077776923e+00, 1.000010609683052309e+00, 1.000010669288331247e+00, 1.000010728893613738e+00, 1.000010788498899781e+00, 1.000010848104189378e+00, 1.000010907709482527e+00, 1.000010967314779229e+00, 1.000011026920079484e+00, 1.000011086525383291e+00, 1.000011146130690651e+00, 1.000011205736001564e+00, 1.000011265341316030e+00, 1.000011324946634048e+00, 1.000011384551955619e+00, 1.000011444157280743e+00, 1.000011503762609420e+00, 1.000011563367941650e+00, 1.000011622973277432e+00, 1.000011682578616767e+00, 1.000011742183959654e+00, 1.000011801789306095e+00, 1.000011861394656088e+00, 1.000011921000009634e+00, 1.000011980605366733e+00, 1.000012040210727384e+00, 1.000012099816091589e+00, 1.000012159421459346e+00, 1.000012219026830655e+00, 1.000012278632205518e+00, 1.000012338237583933e+00, 1.000012397842965901e+00, 1.000012457448351422e+00, 1.000012517053740496e+00, 1.000012576659133122e+00, 1.000012636264529301e+00, 1.000012695869929033e+00, 1.000012755475332317e+00, 1.000012815080739155e+00, 1.000012874686149545e+00, 1.000012934291563488e+00, 1.000012993896980983e+00, 1.000013053502402032e+00, 1.000013113107826633e+00, 1.000013172713254787e+00, 1.000013232318686493e+00, 1.000013291924121753e+00, 1.000013351529560565e+00, 1.000013411135002930e+00, 1.000013470740448848e+00, 1.000013530345898318e+00, 1.000013589951351341e+00, 1.000013649556807917e+00, 1.000013709162268046e+00, 1.000013768767731728e+00, 1.000013828373198962e+00, 1.000013887978669749e+00, 1.000013947584144089e+00, 1.000014007189621981e+00, 1.000014066795103427e+00, 1.000014126400588425e+00, 1.000014186006076976e+00, 1.000014245611569079e+00, 1.000014305217064736e+00, 1.000014364822563945e+00, 1.000014424428066707e+00, 1.000014484033573021e+00, 1.000014543639082889e+00, 1.000014603244596309e+00, 1.000014662850113282e+00, 1.000014722455633808e+00, 1.000014782061157886e+00, 1.000014841666685517e+00, 1.000014901272216702e+00, 1.000014960877751438e+00, 1.000015020483289728e+00, 1.000015080088831570e+00, 1.000015139694376965e+00, 1.000015199299925913e+00, },
        {1.000000000000000000e+00, 1.000015258905478414e+00, 1.000030518043791024e+00, 1.000045777414941384e+00, 1.000061037018933045e+00, 1.000076296855769562e+00, 1.000091556925454486e+00, 1.000106817227991372e+00, 1.000122077763383771e+00, 1.000137338531635238e+00, 1.000152599532749324e+00, 1.000167860766729584e+00, 1.000183122233579571e+00, 1.000198383933302839e+00, 1.000213645865902939e+00, 1.000228908031383427e+00, 1.000244170429747855e+00, 1.000259433060999777e+00, 1.000274695925142747e+00, 1.000289959022180318e+00, 1.000305222352116044e+00, 1.000320485914953479e+00, 1.000335749710696176e+00, 1.000351013739347690e+00, 1.000366278000911574e+00, 1.000381542495391383e+00, 1.000396807222790670e+00, 1.000412072183112989e+00, 1.000427337376361896e+00, 1.000442602802540943e+00, 1.000457868461653685e+00, 1.000473134353703677e+00, 1.000488400478694473e+00, 1.000503666836629627e+00, 1.000518933427512694e+00, 1.000534200251347228e+00, 1.000549467308136784e+00, 1.000564734597884916e+00, 1.000580002120595179e+00, 1.000595269876271129e+00, 1.000610537864916319e+00, 1.000625806086534304e+00, 1.000641074541128641e+00, 1.000656343228702882e+00, 1.000671612149260584e+00, 1.000686881302805302e+00, 1.000702150689340590e+00, 1.000717420308870005e+00, 1.000732690161397100e+00, 1.000747960246925432e+00, 1.000763230565458555e+00, 1.000778501117000025e+00, 1.000793771901553399e+00, 1.000809042919122230e+00, 1.000824314169710075e+00, 1.000839585653320489e+00, 1.000854857369957028e+00, 1.000870129319623247e+00, 1.000885401502322703e+00, 1.000900673918058952e+00, 1.000915946566835548e+00, 1.000931219448656049e+00, 1.000946492563524009e+00, 1.000961765911442986e+00, 1.000977039492416535e+00, 1.000992313306448213e+00, 1.001007587353541575e+00, 1.001022861633700178e+00, 1.001038136146927578e+00, 1.001053410893227331e+00, 1.001068685872602995e+00, 1.001083961085058125e+00, 1.001099236530596278e+00, 1.001114512209221011e+00, 1.001129788120935880e+00, 1.001145064265744442e+00, 1.001160340643650253e+00, 1.001175617254656872e+00, 1.001190894098767853e+00, 1.001206171175986755e+00, 1.001221448486317134e+00, 1.001236726029762548e+00, 1.001252003806326552e+00, 1.001267281816012706e+00, 1.001282560058824565e+00, 1.001297838534765687e+00, 1.001313117243839629e+00, 1.001328396186049948e+00, 1.001343675361400203e+00, 1.001358954769893950e+00, 1.001374234411534748e+00, 1.001389514286326152e+00, 1.001404794394271722e+00, 1.001420074735375015e+00, 1.001435355309639588e+00, 1.001450636117069000e+00, 1.001465917157666808e+00, 1.001481198431436570e+00, 1.001496479938381844e+00, 1.001511761678506188e+00, 1.001527043651813160e+00, 1.001542325858306318e+00, 1.001557608297989221e+00, 1.001572890970865427e+00, 1.001588173876938493e+00, 1.001603457016211978e+00, 1.001618740388689441e+00, 1.001634023994374440e+00, 1.001649307833270534e+00, 1.001664591905381281e+00, 1.001679876210710239e+00, 1.001695160749260967e+00, 1.001710445521037025e+00, 1.001725730526041971e+00, 1.001741015764279363e+00, 1.001756301235752760e+00, 1.001771586940465722e+00, 1.001786872878421807e+00, 1.001802159049624575e+00, 1.001817445454077584e+00, 1.001832732091784394e+00, 1.001848018962748564e+00, 1.001863306066973653e+00, 1.001878593404463220e+00, 1.001893880975220825e+00, 1.001909168779250027e+00, 1.001924456816554386e+00, 1.001939745087137461e+00, 1.001955033591002812e+00, 1.001970322328153998e+00, 1.001985611298594579e+00, 1.002000900502328115e+00, 1.002016189939358166e+00, 1.002031479609688291e+00, 1.002046769513322051e+00, 1.002062059650263005e+00, 1.002077350020514713e+00, 1.002092640624080735e+00, 1.002107931460964632e+00, 1.002123222531169964e+00, 1.002138513834700291e+00, 1.002153805371559173e+00, 1.002169097141750170e+00, 1.002184389145276844e+00, 1.002199681382142754e+00, 1.002214973852351460e+00, 1.002230266555906524e+00, 1.002245559492811506e+00, 1.002260852663069967e+00, 1.002276146066685468e+00, 1.002291439703661568e+00, 1.002306733574001830e+00, 1.002322027677709813e+00, 1.002337322014789080e+00, 1.002352616585243190e+00, 1.002367911389075705e+00, 1.002383206426290186e+00, 1.002398501696890195e+00, 1.002413797200879291e+00, 1.002429092938261037e+00, 1.002444388909038995e+00, 1.002459685113216724e+00, 1.002474981550797787e+00, 1.002490278221785746e+00, 1.002505575126184161e+00, 1.002520872263996594e+00, 1.002536169635226608e+00, 1.002551467239877763e+00, 1.002566765077953621e+00, 1.002582063149457745e+00, 1.002597361454393696e+00, 1.002612659992765036e+00, 1.002627958764575326e+00, 1.002643257769828130e+00, 1.002658557008527009e+00, 1.002673856480675525e+00, 1.002689156186277240e+00, 1.002704456125335718e+00, 1.002719756297854518e+00, 1.002735056703837206e+00, 1.002750357343287342e+00, 1.002765658216208489e+00, 1.002780959322604209e+00, 1.002796260662478066e+00, 1.002811562235833622e+00, 1.002826864042674439e+00, 1.002842166083004081e+00, 1.002857468356826109e+00, 1.002872770864144087e+00, 1.002888073604961578e+00, 1.002903376579282145e+00, 1.002918679787109351e+00, 1.002933983228446758e+00, 1.002949286903297930e+00, 1.002964590811666430e+00, 1.002979894953555821e+00, 1.002995199328969667e+00, 1.003010503937911531e+00, 1.003025808780384976e+00, 1.003041113856393565e+00, 1.003056419165940863e+00, 1.003071724709030433e+00, 1.003087030485665837e+00, 1.003102336495850641e+00, 1.003117642739588407e+00, 1.003132949216882700e+00, 1.003148255927737083e+00, 1.003163562872155120e+00, 1.003178870050140376e+00, 1.003194177461696413e+00, 1.003209485106826796e+00, 1.003224792985535089e+00, 1.003240101097824857e+00, 1.003255409443699663e+00, 1.003270718023163072e+00, 1.003286026836218648e+00, 1.003301335882869955e+00, 1.003316645163120559e+00, 1.003331954676974022e+00, 1.003347264424433910e+00, 1.003362574405503788e+00, 1.003377884620187220e+00, 1.003393195068487770e+00, 1.003408505750409004e+00, 1.003423816665954486e+00, 1.003439127815127781e+00, 1.003454439197932454e+00, 1.003469750814372070e+00, 1.003485062664450194e+00, 1.003500374748170392e+00, 1.003515687065536227e+00, 1.003530999616551265e+00, 1.003546312401219073e+00, 1.003561625419543214e+00, 1.003576938671527254e+00, 1.003592252157174759e+00, 1.003607565876489294e+00, 1.003622879829474424e+00, 1.003638194016133716e+00, 1.003653508436470734e+00, 1.003668823090489045e+00, 1.003684137978192214e+00, 1.003699453099583806e+00, 1.003714768454667388e+00, 1.003730084043446526e+00, 1.003745399865924786e+00, 1.003760715922105733e+00, 1.003776032211992933e+00, 1.003791348735589953e+00, 1.003806665492900360e+00, 1.003821982483927717e+00, 1.003837299708675594e+00, 1.003852617167147555e+00, 1.003867934859347167e+00, 1.003883252785277996e+00, 1.003898570944943610e+00, },
        {1.000000000000000000e+00, 1.003913889338347573e+00, 1.007843097206447977e+00, 1.011787683559331491e+00, 1.015747708586685747e+00, 1.019723232713774154e+00, 1.023714316602357916e+00, 1.027721021151621656e+00, 1.031743407499102669e+00, 1.035781537021623803e+00, 1.039835471336229998e+00, 1.043905272301128493e+00, 1.047991002016632700e+00, 1.052092722826109788e+00, 1.056210497316931968e+00, 1.060344388321431496e+00, 1.064494458917859426e+00, 1.068660772431348105e+00, 1.072843392434877440e+00, 1.077042382750244949e+00, 1.081257807449039599e+00, 1.085489730853619468e+00, 1.089738217538093226e+00, 1.094003332329305458e+00, 1.098285140307825843e+00, 1.102583706808942211e+00, 1.106899097423657477e+00, 1.111231377999690482e+00, 1.115580614642480752e+00, 1.119946873716197190e+00, 1.124330221844750710e+00, 1.128730725912810842e+00, 1.133148453066826309e+00, 1.137583470716049606e+00, 1.142035846533565582e+00, 1.146505648457324049e+00, 1.150992944691176441e+00, 1.155497803705916514e+00, 1.160020294240325138e+00, 1.164560485302219161e+00, 1.169118446169504393e+00, 1.173694246391232697e+00, 1.178287955788663232e+00, 1.182899644456327838e+00, 1.187529382763100595e+00, 1.192177241353271569e+00, 1.196843291147624760e+00, 1.201527603344520269e+00, 1.206230249420980699e+00, 1.210951301133781809e+00, 1.215690830520547439e+00, 1.220448909900848716e+00, 1.225225611877307566e+00, 1.230021009336704542e+00, 1.234835175451090991e+00, 1.239668183678905571e+00, 1.244520107766095140e+00, 1.249391021747240033e+00, 1.254280999946683737e+00, 1.259190116979666995e+00, 1.264118447753466348e+00, 1.269066067468537123e+00, 1.274033051619660913e+00, 1.279019475997097527e+00, 1.284025416687741467e+00, 1.289050950076282918e+00, 1.294096152846373292e+00, 1.299161101981795324e+00, 1.304245874767637757e+00, 1.309350548791474619e+00, 1.314475201944549115e+00, 1.319619912422962159e+00, 1.324784758728865549e+00, 1.329969819671659818e+00, 1.335175174369196772e+00, 1.340400902248986733e+00, 1.345647083049410510e+00, 1.350913796820936110e+00, 1.356201123927340211e+00, 1.361509145046934424e+00, 1.366837941173796340e+00, 1.372187593619005409e+00, 1.377558184011883647e+00, 1.382949794301241203e+00, 1.388362506756626800e+00, 1.393796403969583072e+00, 1.399251568854906811e+00, 1.404728084651914146e+00, 1.410226034925710680e+00, 1.415745503568466591e+00, 1.421286574800696729e+00, 1.426849333172545717e+00, 1.432433863565078088e+00, 1.438040251191573469e+00, 1.443668581598826834e+00, 1.449318940668453847e+00, 1.454991414618201307e+00, 1.460686090003262739e+00, 1.466403053717599112e+00, 1.472142392995264747e+00, 1.477904195411738397e+00, 1.483688548885259548e+00, 1.489495541678169948e+00, 1.495325262398260381e+00, 1.501177800000122719e+00, 1.507053243786507265e+00, 1.512951683409685402e+00, 1.518873208872817583e+00, 1.524817910531326670e+00, 1.530785879094276654e+00, 1.536777205625756760e+00, 1.542791981546270986e+00, 1.548830298634133062e+00, 1.554892249026866883e+00, 1.560977925222612417e+00, 1.567087420081537116e+00, 1.573220826827252848e+00, 1.579378239048238387e+00, 1.585559750699267452e+00, 1.591765456102842351e+00, 1.597995449950633228e+00, 1.604249827304922945e+00, 1.610528683600057618e+00, 1.616832114643902836e+00, 1.623160216619305568e+00, 1.629513086085561806e+00, 1.635890819979889937e+00, 1.642293515618909898e+00, 1.648721270700128103e+00, 1.655174183303428198e+00, 1.661652351892567637e+00, 1.668155875316680128e+00, 1.674684852811783946e+00, 1.681239384002296162e+00, 1.687819568902552790e+00, 1.694425507918334889e+00, 1.701057301848400631e+00, 1.707715051886023376e+00, 1.714398859620535756e+00, 1.721108827038879809e+00, 1.727845056527163178e+00, 1.734607650872221402e+00, 1.741396713263186319e+00, 1.748212347293060610e+00, 1.755054656960298505e+00, 1.761923746670392675e+00, 1.768819721237467335e+00, 1.775742685885877585e+00, 1.782692746251815005e+00, 1.789670008384919539e+00, 1.796674578749897688e+00, 1.803706564228147030e+00, 1.810766072119387107e+00, 1.817853210143296689e+00, 1.824968086441157449e+00, 1.832110809577504067e+00, 1.839281488541780801e+00, 1.846480232750004531e+00, 1.853707152046434320e+00, 1.860962356705247503e+00, 1.868245957432222344e+00, 1.875558065366427274e+00, 1.882898792081916734e+00, 1.890268249589433672e+00, 1.897666550338118686e+00, 1.905093807217225867e+00, 1.912550133557845355e+00, 1.920035643134632633e+00, 1.927550450167544597e+00, 1.935094669323582415e+00, 1.942668415718541207e+00, 1.950271804918766577e+00, 1.957904952942918016e+00, 1.965567976263739210e+00, 1.973260991809835274e+00, 1.980984116967456947e+00, 1.988737469582291758e+00, 1.996521167961262221e+00, 2.004335330874331050e+00, 2.012180077556313450e+00, 2.020055527708696498e+00, 2.027961801501465646e+00, 2.035899019574938370e+00, 2.043867303041604999e+00, 2.051866773487976745e+00, 2.059897552976440972e+00, 2.067959764047123720e+00, 2.076053529719759521e+00, 2.084178973495568534e+00, 2.092336219359141029e+00, 2.100525391780329241e+00, 2.108746615716146631e+00, 2.117000016612674584e+00, 2.125285720406976567e+00, 2.133603853529019774e+00, 2.141954542903604301e+00, 2.150337915952299868e+00, 2.158754100595390114e+00, 2.167203225253824516e+00, 2.175685418851177934e+00, 2.184200810815617834e+00, 2.192749531081879205e+00, 2.201331710093247213e+00, 2.209947478803547604e+00, 2.218596968679144909e+00, 2.227280311700948459e+00, 2.235997640366426261e+00, 2.244749087691626748e+00, 2.253534787213208447e+00, 2.262354872990477591e+00, 2.271209479607433700e+00, 2.280098742174823174e+00, 2.289022796332200927e+00, 2.297981778250000077e+00, 2.306975824631609749e+00, 2.316005072715461008e+00, 2.325069660277120946e+00, 2.334169725631394984e+00, 2.343305407634437381e+00, 2.352476845685870020e+00, 2.361684179730909476e+00, 2.370927550262502416e+00, 2.380207098323469355e+00, 2.389522965508656795e+00, 2.398875293967097803e+00, 2.408264226404181028e+00, 2.417689906083828218e+00, 2.427152476830680259e+00, 2.436652083032291764e+00, 2.446188869641334256e+00, 2.455762982177807976e+00, 2.465374566731262340e+00, 2.475023769963025096e+00, 2.484710739108440196e+00, 2.494435621979114439e+00, 2.504198566965172892e+00, 2.513999723037523154e+00, 2.523839239750128468e+00, 2.533717267242289740e+00, 2.543633956240936487e+00, 2.553589458062926746e+00, 2.563583924617355993e+00, 2.573617508407875091e+00, 2.583690362535017319e+00, 2.593802640698534500e+00, 2.603954497199742275e+00, 2.614146086943874562e+00, 2.624377565442447221e+00, 2.634649088815630976e+00, 2.644960813794633623e+00, 2.655312897724091560e+00, 2.665705498564470682e+00, 2.676138774894476666e+00, 2.686612885913474695e+00, 2.697127991443918649e+00, 2.707684251933789806e+00, },
    };
    #endif

    constexpr uxx lut_length       = sizeof(lut) / sizeof(lut[0]);
    constexpr uxx mask_lut         = (1 << step) - 1;
}

namespace mixc::math_expe::origin{
    f64 expe_unsafe(f64 x){
        using namespace inc;
        bool is_neg = x < 0;

        if (is_neg){
            x = -x;
        }

        auto qr         = div_unsafe(x, 1.0);
        uxx  q          = uxx(qr.quotient);
        f64  m          = expe_unsafe(q);
        mf64 r          = qr.remainder;
        mf64 linear     = r;
        uxx  s          = uxx(-r.real_exp_unsafe());
        uxx  sft        = s + r.decimal_bits() - lut_length * step/*线性区*/;
        u64  dec        = r.real_dec_unsafe() >> sft;
        linear.decimal  = dec << sft;
        r              -= linear;

        for(uxx i = 0; i < lut_length; i++, dec >>= step){
            auto idx = dec & mask_lut;
            auto v   = lut[i][idx];
            m       *= v;
        }

        r = m * (1 + r);

        if (is_neg){
            r = 1.0 / r;
        }
        return r;
    }
}
