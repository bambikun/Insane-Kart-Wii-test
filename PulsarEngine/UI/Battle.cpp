#include <kamek.hpp>
#include <Settings/SettingsParam.hpp>
#include <MKVN.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>

namespace Pulsar{
namespace Settings{
kmWrite32(0x8084e674, 0x48000018);
kmWrite32(0x8084b7b0, 0x48000018);
kmWrite32(0x808409ec, 0x4800001C);

//General Online Fixes (ZPL)
kmWrite32(0x8062e11c, 0x3880006E);
kmWrite32(0x8062e128, 0x3880006F);
kmWrite32(0x806501e8, 0x3860006f);
kmWrite32(0x806501d8, 0x4BFFFE44);
kmWrite32(0x806509b8, 0x3880006E);

//Fix Random Track Selection (Toadette Hack Fan)
kmWrite32(0x80643218, 0x38000000);

//2P WW Battle (Toadette Hack Fan)
kmWrite32(0x8062E788, 0x3880006E);
kmWrite32(0x8062E794, 0x3880006F);

//1P Balloon Battle Froom (Toadette Hack Fan)
kmWrite32(0x8062E938, 0x3880006E);
kmWrite32(0x8062E944, 0x3880006F);

//1P Coin Runners Froom (Toadette Hack Fan)
kmWrite32(0x8062E9C8, 0x3880006E);
kmWrite32(0x8062E9D4, 0x3880006F);

//2P Balloon Battle Froom (Toadette Hack Fan)
kmWrite32(0x8062EB78, 0x3880006E);
kmWrite32(0x8062EB84, 0x3880006F);

//2P Coin Runners Froom (Toadette Hack Fan)
kmWrite32(0x8062EC08, 0x3880006E);
kmWrite32(0x8062EC14, 0x3880006F);

//100cc on Battle
kmWrite32(0x808b5ce0, 0x3F666666);

//High Coin Count
kmWrite32(0x8087B5A0, 0x3B80000A);

asmFunc CoinBattle_EarlyOutIfInvalid() {
    ASM(
        lis       r12, 0x8000;
        cmplw     r6, r12;
        bge       valid;
        lwz       r0, 0x24(r1);
        mtlr      r0;
        lwz       r31, 0x1C(r1);
        lwz       r30, 0x18(r1);
        lwz       r29, 0x14(r1);
        lwz       r28, 0x10(r1);
        addi      r1, r1, 0x20;
        blr;
        valid:
        lwz       r5, 0x20B8(r6);
        blr;
    )
}
kmCall(0x8053D47C, CoinBattle_EarlyOutIfInvalid);

}
}