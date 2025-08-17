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
kmWrite32(0x80584b74, 0x60000000); //TC Fix [Ro]

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

//Use Items on Cannon
kmWrite32(0x80797F88, 0x60000000);
kmWrite32(0x80797BA0, 0x60000000);
kmWrite32(0x80797c34, 0x60000000);

//CPUs Get Startup Boost
kmWrite32(0x8073ef10, 0x60000000);

//Bullet Bill Visible in Battle
kmWrite32(0x8058D9EC, 0x38800000);

//Shells Never Break
kmWrite32(0x807B5E58, 0x60000000);

//Anti-Freeze
kmWrite32(0x80526660, 0x38000001); //Miis
kmWrite32(0x807A1990, 0x60000000); //Hacked Items

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

//Anti Online Item Delimiters [Ro]
asmFunc GetItemDelimiterShock() {
    ASM(
        nofralloc;
loc_0x0:
  mflr r12;
  cmpwi     r7, 0x1;
  bne+ validLightning;
  addi r12, r12, 0x12C;
  mtlr r12;
  blr;
validLightning:
  mulli r29, r3, 0xF0;
  blr;
    )
}
kmCall(0x807B7C34, GetItemDelimiterShock);

asmFunc GetItemDelimiterBlooper() {
    ASM(
        nofralloc;
loc_0x0:
  mflr r12;
  cmpwi     r7, 0x1;
  bne+ validBlooper;
  addi r12, r12, 0x1A8;
  mtlr r12;
  blr;
validBlooper:
  addi r11, r1, 0x50;
  blr;
    )
}
kmCall(0x807A81C0, GetItemDelimiterBlooper);

asmFunc GetItemDelimiterPOW() {
    ASM(
        nofralloc;
loc_0x0:
mflr r12;
  cmpwi     r7, 0x1;
  bne+ validPOW;
  addi r12, r12, 0x48;
  mtlr r12;
  blr;
validPOW:
  mr r30, r3;
  blr;
    )
}
kmCall(0x807B1B44, GetItemDelimiterPOW);

//Bullet Bill Fix [CLF78]
kmWrite8(0x80580272, 0x00000000);

//AirFIBs [Conradi]
kmWrite32(0x808a5770, 0x00000000);
kmWrite32(0x808a5774, 0x00000000);

//45sec Vote Time [Ro]
kmWrite32(0x80899EF4, 0x42340000);

//Shock Squishing [CLF78, Ro]
asmFunc ShockSquick1() {
    ASM(
        nofralloc;
  rlwinm.   r26,r6,16,31,31;
  bne-      loc_0x20;
  rlwinm.   r26,r6,25,31,31;
  beq-      loc_0x20;
  rlwinm.   r26,r7,25,31,31;
  bne-      loc_0x3C;
  li        r23, 0x1;
  b         loc_0x3C;

loc_0x20:
  rlwinm.   r26,r7,16,31,31;
  bne-      loc_0x3C;
  rlwinm.   r26,r7,25,31,31;
  beq-      loc_0x3C;
  rlwinm.   r26,r6,25,31,31;
  bne-      loc_0x3C;
  li        r24, 0x1;

loc_0x3C:
  cmpwi     r27, 0;
  rlwinm    r26,r3,1,31,31;
  blr;
    )
}
kmCall(0x8056fd4c, ShockSquick1);

asmFunc ShockSquish2() {
    ASM(
        nofralloc;
  lwz       r5, 0x0(r31);
  li        r4, 0xD;
  lwz       r5, 0x4(r5);
  lwz       r5, 0xC(r5);
  rlwinm.   r5,r5,17,31,31;
  bne-      loc_0x1C;
  li        r4, 0x10;

loc_0x1C:
  blr;

    )
}
kmCall(0x8057042c, ShockSquish2);

asmFunc ShockSquish3() {
    ASM(
        nofralloc;
  lwz       r5, 0x4(r30);
  li        r4, 0xD;
  lwz       r5, 0x4(r5);
  lwz       r5, 0xC(r5);
  rlwinm.   r5,r5,17,31,31;
  bne-      loc_0x1C;
  li        r4, 0x10;

loc_0x1C:
  blr;

    )
}
kmCall(0x805705bc, ShockSquish3);
kmWrite8(0x805698cb, 0x00);
kmWrite32(0x8056990c, 0x48000024);
kmWrite32(0x80569948, 0x48000018);

//Poocha Fix [Ro]
asmFunc PochaFix() {
    ASM(
        nofralloc;
  lbz       r31, 0x78(r3);
  cmpwi     r31, 0;
  beq-      loc_0x24;
  lbz       r31, 0xE(r3);
  addi      r31, r31, 0x1;
  cmpwi     r31, 0x3C;
  blt-      loc_0x24;
  li        r31, 0;
  stb       r31, 0x78(r3);

loc_0x24:
  stb       r31, 0xE(r3);
  mr        r31, r3;
  blr;

    )
}
kmCall(0x8069B3A8, PochaFix);

//Item Route Lag Fix [Ro]
asmFunc ItemRouteLagFix() {
    ASM(
        nofralloc;
  lfs       f1, 0x48(r29);
  lwz       r0, 0x4(r29);
  cmpwi     r0, 0x1;
  beq-      loc_0x18;
  cmpwi     r0, 0x5;
  bne-      loc_0x34;

loc_0x18:
  lfs       f2, 0x258(r29);
  lfs       f0, 0x4(r31);
  fcmpo     cr0, f2, f0;
  blt-      loc_0x34;
  fsubs     f1, f1, f1;
  stfs      f1, 0x258(r29);
  lfs       f1, 0x10(r31);

loc_0x34:
  blr;

    )
}
kmCall(0x8079f740, ItemRouteLagFix);

extern "C" void sInstance__8Racedata(void*);
//Fix Live View Character Icons [Ro]
asmFunc LiveViewFix1() {
    ASM(
        nofralloc;
  lis       r12, sInstance__8Racedata@ha;
  lwz       r12, sInstance__8Racedata@l(r12);
  lwz       r12, 0xB74(r12);
  cmpwi     r12, 0x6;
  bne-      loc_0x18;
  li        r3, 0;

loc_0x18:
  extsb.    r28, r3;
  blr;

    )
}
kmCall(0x807EAF78, LiveViewFix1);

extern "C" void FixLiveViewBug(void*);
asmFunc LiveViewFix() {
    ASM(
        nofralloc;
  lwz       r0, 0x38(r3);
  lwz       r12, 0xB74(r6);
  cmpwi     r12, 0x6;
  bne-      loc_0x38;
  mr        r3, r28;
  mflr      r29;        
  lis       r12, FixLiveViewBug@h;
  ori       r12, r12, FixLiveViewBug@l;
  mtctr     r12;
  bctrl;
  mtlr      r29;     
  lbz       r0, 0x1B4(r28);
  sub       r0, r3, r0;
  cntlzw    r0, r0;
  rlwinm    r0,r0,27,5,31;
  xori      r0, r0, 0x1;

loc_0x38:
blr;
    )
}
kmCall(0x807EB440, LiveViewFix);

//Allow Pausing Before The Race Starts [Sponge]
kmWrite32(0x80856a28, 0x40810050);

//Allow Looking Backwards Anytime [Ro, Gaberboo]
kmWrite32(0x805A228C, 0x60000000); //Respawn
kmWrite32(0x805A225C, 0x38800001); //Countdown

//Goomba Size Memorizer [_tZ]
kmWrite32(0x80821E78, 0x38600158);
kmWrite32(0x806DC750, 0xD19D0044);
kmWrite32(0x806DC6F0, 0xD19D0044);
kmWrite32(0x806DCB30, 0xD19C0044);
kmWrite32(0x806DCAD4, 0xD19C0040);

asmFunc GoombaSizeMemorizer1() {
    ASM(
        nofralloc;
  lfs       f8, 0x3C(r29);
  lfs       f7, 0x40(r29);
  lfs       f6, 0x44(r29);
  stfs      f8, 0x14C(r29);
  stfs      f7, 0x150(r29);
  stfs      f6, 0x154(r29);
  li        r30, 0;
  blr;

    )
}
kmCall(0x806db1b4, GoombaSizeMemorizer1);

asmFunc GoombaSizeMemorizer2() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r29);
  lfs       f10, 0x150(r29);
  lfs       f11, 0x154(r29);
  fmul      f12, f11, f1;
  fmul      f1, f9, f1;
  fmul      f0, f10, f0;
  stfs      f1, 0x3C(r29);
  blr;

    )
}
kmCall(0x806DC6E8, GoombaSizeMemorizer2);
kmCall(0x806DC748, GoombaSizeMemorizer2);

asmFunc GoombaSizeMemorizer3() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r28);
  lfs       f10, 0x150(r28);
  lfs       f11, 0x154(r28);
  fmul      f12, f11, f1;
  fmul      f1, f9, f1;
  fmul      f0, f10, f0;
  stfs      f1, 0x3C(r28);
  blr;

    )
}
kmCall(0x806DCB28, GoombaSizeMemorizer3);

asmFunc GoombaSizeMemorizer4() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r28);
  lfs       f10, 0x150(r28);
  lfs       f11, 0x154(r28);
  fmul      f12, f11, f0;
  fmul      f13, f9, f0;
  fmul      f0, f10, f0;
  stfs      f12, 0x3C(r28);
  blr;

    )
}
kmCall(0x806DCACC, GoombaSizeMemorizer4);

asmFunc BalloonPosFix() {
  ASM(
    nofralloc;
  stwu      r1, -0x50(r1);
  stmw      r14, 0x8(r1);
  lis       r14, 0x4320;
  ori       r14, r14, 0;
  stw       r14, 0x0(r3);
  lis       r14, 0xC270;
  ori       r14, r14, 0;
  stw       r14, 0x4(r3);
  lis       r14, 0x4339;
  ori       r14, r14, 0;
  stw       r14, 0x8(r3);
  lmw       r14, 0x8(r1);
  addi      r1, r1, 0x50;
  lfs       f1, 0x0(r3);
  blr;
  )
}
kmCall(0x8086f2a4, BalloonPosFix);

asmFunc ItemBoxFix() {
  ASM(
    nofralloc;
  add       r3, r0, r29;
  lwz       r12, 0xA0(r28);
  lwz       r11, 0x58(r3);
  cmpwi     r11, 0;
  bne-      loc_0x2C;
  lhz       r11, 0x208(r12);
  cmpwi     r11, 0x41A0;
  blt-      loc_0x2C;
  lis       r11, 0x4000;
  stw       r11, 0x208(r12);
  stw       r11, 0x200(r12);

loc_0x2C:
blr;
  )
}
kmCall(0x807eefb8, ItemBoxFix);

//Event Overflow Protection [Seeky]
asmFunc EventOverflowProtection() {
  ASM(
    nofralloc;
  lbz       r12, 0x1C(r27);
  add       r12, r30, r12;
  cmpwi     r12, 0xE0;
  blt+      loc_0x18;
  li        r0, 0;
  stb       r0, 0x19(r27);

loc_0x18:
  lbz       r0, 0x19(r27);
  blr;
  )
}
kmCall(0x8065BBD4, EventOverflowProtection);

//Enhanced Pause Menu [Ro]
kmWrite32(0x8062c658, 0x38800019);
kmWrite32(0x8062c79c, 0x38800019);
kmWrite32(0x80633a98, 0x38600019);
kmWrite32(0x8062c8e0, 0x38800019);
kmWrite32(0x80633970, 0x38600019);
kmWrite32(0x8083d618, 0x60000000);

extern "C" void sInstance__8Racedata(void*);
extern "C" void sInstance__10SectionMgr(void*);
asmFunc EnhancedPauseMenu1() {
  ASM(
  lwz r3, sInstance__10SectionMgr@l (r6);
  lwz r12, sInstance__8Racedata@l (r6);
  lwz r0, 0x1760 (r12);
  cmpwi r0, 2;
  beq end;

  cmpwi r4, 0x49;
  beq decreaseRaceNum;

  cmpwi r4, 0x4A;
  bne end;

  li r4, 0x4B;

  cmpwi r0, 1;
  beq decreaseRaceNum;

  li r4, 0x4C;

  decreaseRaceNum:
  lwz r6, 0x98 (r3);
  lwz r31, 0x60 (r6);
  subi r31, r31, 1;
  stw r31, 0x60 (r6);

  li r31, 5;
  stw r31, 0x1764 (r12);

  end:
  mr r31, r5;
  blr;
  )
}
kmCall(0x806024d8, EnhancedPauseMenu1);

extern "C" void sInstance__8Racedata(void*);
asmFunc EnhancedPauseMenu2() {
  ASM(
  lis r3, sInstance__8Racedata@ha;
  lwz r3, sInstance__8Racedata@l (r3);
  lwz r4, 0x1760 (r3);
  cmpwi r4, 2;
  beq end;
  li r4, 0x1;
  stw r4, 0xD18 (r3);
  stw r4, 0xE08 (r3);
  stw r4, 0xEF8 (r3);

  end:
  li        r3, 0x6C4;
  blr;
  )
}
kmCall(0x80623df4, EnhancedPauseMenu2);

kmWrite32(0x80859068, 0x48000808);
kmWrite32(0x80858e38, 0x48000040);

//Prevent People To Join WWs Through Friends [Ro, B_squo]
kmWrite32(0x8065a004, 0x38000001);
kmWrite32(0x8065a050, 0x38000001);

//Prevent Lag Sync
kmWrite32(0x80654b00, 0x4E800020);

}//namespace IKW
}//namespace Pulsar