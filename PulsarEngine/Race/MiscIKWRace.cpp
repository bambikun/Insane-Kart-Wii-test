#include <kamek.hpp>
#include <MKVN.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <Settings/Settings.hpp>
#include <Settings/UI/ExpOptionsPage.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <SlotExpansion/CupsConfig.hpp>
namespace Pulsar {
namespace IKW {
kmWrite32(0x80856560, 0x60000000); // Don't Lose VR When Disconnecting (Bully)
kmWrite32(0x808565CC, 0x60000000); // Don't Lose BR When Disconnecting (Bully)
kmWrite32(0x8082AC00, 0x3B800001); // Mega Flips Everything
kmWrite32(0x807BA5D0, 0x60000000); // No Bullet Bill Icon
kmWrite32(0x807AFAA8, 0x48000038); // Impervious TC
kmWrite16(0x807B1DD2, 0x00000080); // Instant POW
kmWrite8(0x807BA077, 0x00000000); // Mushroom Glitch

//Hybrid Drift v2 [CLF78, Ismy]
asmFunc HybridDrift1() {
    ASM(
lwz r0, 0x14(r3);
lwz r12, 0(r28);
lwz r12, 0(r12);
lwz r12, 0x14(r12);
lwz r12, 0(r12);
lwz r12, 0x4(r12);
cmpwi r12, 2;
beqlr;
li r0, 0;
blr;
    )
}
kmCall(0x8057930C, HybridDrift1);
kmCall(0x80578DCC, HybridDrift1);

asmFunc HybridDrift3() {
    ASM(
lwz r0, 0x14(r3);
rlwinm. r12, r0, 0, 18, 18;
beq end2;
ori r0, r0, 0x10;
stw r0, 0x14(r3);
end2:
lwz r0, 0x4(r3);
blr;
    )
}
kmCall(0x8057DFA8, HybridDrift3);

asmFunc HybridDrift4() {
    ASM(
lwz r0, 0x14(r4);
rlwinm. r12, r0, 0, 18, 18;
beq end2;
ori r0, r0, 0x10;
stw r0, 0x14(r4);
end2:
lwz r0, 0x4(r4);
blr;
    )
}
kmCall(0x8057E018, HybridDrift4);

asmFunc HybridDrift6() {
    ASM(
  rlwinm.   r0,r0,0,27,27;
  li        r0, 0;
  stw       r0, 0x1C8(r3);
    )
}
kmCall(0x8057E108, HybridDrift6);

asmFunc HybridDrift7() {
    ASM(
lwz r3, 0x4(r30);
andi. r4, r3, 0x84;
beq end;
lwz r4, 0x14(r30);
rlwinm r4, r4, 0, 28, 26;
stw r4, 0x14(r30);
rlwinm r3, r3, 0, 4, 2;
stw r3, 0x4(r30);
end:
mr r3, r30;
blr;
    )
}
kmCall(0x80594AA8, HybridDrift7);
kmWrite8(0x8059450E, 0x00000020);
kmWrite32(0x80594A60, 0x60000000);
kmWrite32(0x805A35BC, 0x38600000);
kmWrite16(0x80745AB0, 0x00004800);

//No Low Battery Message
kmWrite16(0x805C379A, 0x0000FFFF);

//No DC at Countdown
kmWrite32(0x80655578, 0x60000000);

// Use Items on Cannon
kmWrite32(0x80797F88, 0x60000000);
kmWrite32(0x80797BA0, 0x60000000);
kmWrite32(0x80797c34, 0x60000000);

//CPUs Get Startup Boost
kmWrite32(0x8073ef10, 0x60000000);

//No Bullet Bill Cancel When Touching Bottom of Rainbow Road [Ro]
kmWrite32(0x8059BE30, 0x60000000);

//Bullet Bill Visible in Battle
kmWrite32(0x8058D9EC, 0x38800000);

//Shells Never Break
kmWrite32(0x807B5E58, 0x60000000);

asmFunc StarCannonFix() {
    ASM(
  andi.     r11, r0, 0x80;
  andis.    r12, r0, 0x8000;
  or.       r0, r11, r12;
    )
}
kmCall(0x8057C3F8, StarCannonFix);

asmFunc ItemRespawn() {
  lwz       r5, 0xB8(r3);
  lwz       r12, 0xA0(r3);
  cmpwi     r12, 0;
  beq-      loc_0x30;
  lwz       r12, 0x0(r12);
  lhz       r12, 0x32(r12);
  cmplwi    r12, 0xFFFF;
  bne-      loc_0x2C;
  li        r4, 0;

loc_0x2C:
  mr        r5, r12;

loc_0x30:


}
kmCall(0x808288B8, ItemRespawn);

asmFunc RespawnBoostOnline() {
  lwz       r4, 0x0(r3);
  lwz       r4, 0x3C(r4);
  cmpwi     r4, 0;
  beq-      loc_0x20;
  lwz       r4, 0x10(r4);
  lwz       r5, 0x10(r4);
  xoris     r5, r5, 0x4000;
  stw       r5, 0x10(r4);

loc_0x20:
  li        r4, 0x3;
}
kmCall(0x80581E40, RespawnBoostOnline);
kmCall(0x805820B0, RespawnBoostOnline);

asmFunc StuckPlayersFix() {
  lwz       r11, 0x8(r4);
  rlwinm.   r12,r11,0,21,21;
  beq-      loc_0x20;
  lha       r0, 0x56(r31);
  cmpwi     r0, 0x52;
  blt-      loc_0x20;
  rlwinm    r11,r11,0,22,20;
  stw       r11, 0x8(r4);

loc_0x20:
  mr        r4, r11;
}
kmCall(0x8058BF58, StuckPlayersFix);

//Motion Sensor Bombs
kmWrite16(0x807A5BF6, 0x0FFF);
kmWrite16(0x807A4ACA, 0x0FFF);

//Live View Shadow Bug Fix
kmWrite32(0x807eb988, 0x807c01c0);

//Fix Silent Bug
kmWrite32(0x8086975C, 0x4082001C);

//Force Title Screen
kmWrite32(0x8063AC94, 0x60000000);

//Custom Save File
kmWrite24(0x8088FE36, 0x696B77);

//TC Fix [Ismy]
//kmWrite32(0x80584AE8, 0x60000000);
//kmWrite32(0x80584B70, 0x60000000);

//Gravity Code [Conradi]
/*extern "C" void PALA(void*);
extern "C" void PALB(void*);
extern "C" void PALC(void*);
asmFunc GravityAreas() {
  lis       r3, PALA@ha;
  lwz       r3, PALA@l(r3);
  addi      r4, r30, 0x68;
  li        r5, -0x1;
  li        r6, 0xB;
  lis       r12, PALB@ha;
  ori       r12, r12, PALB@l;
  mtctr     r12;
  bctrl;
  cmpwi     r3, 0;
  fdivs     f3, f30, f30;
  blt-      loc_0x54;
  mr        r4, r3;
  lis       r3, PALA@ha;
  lwz       r3, PALA@l(r3);
  lis       r12, PALC@ha;
  ori       r12, r12, PALC@l;
  mtctr     r12;
  bctrl;
  lwz       r3, 0x4(r3);
  lfs       f3, 0x28(r3);

loc_0x54:
  mr        r3, r30;
  mr        r4, r29;
  lfs       f2, 0x114(r3);
  fmr       f1, f30;
  lfs       f0, 0x148(r3);
  fmuls     f0, f0, f3;
}
kmCall(0x805B5208, GravityAreas);*/

//Mii Outfit C
}//namespace IKW
}//namespace Pulsar