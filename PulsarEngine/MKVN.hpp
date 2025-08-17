#ifndef _MKVN_
#define _MKVN_
#include <PulsarSystem.hpp>
#include <kamek.hpp>
#include <Settings/Settings.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/Race/RaceData.hpp>

enum Transmission{
    TRANSMISSION_DEFAULT,
    TRANSMISSION_OUTSIDE,
    TRANSMISSION_INSIDE
};

enum ExtraPageId{
    PAGE_TRANSMISSION_SELECT = PAGE_BATTLE_TOTAL_LEADERBOARDS,
    PAGE_MULTI_TRANSMISSION_SELECT = PAGE_COMPETITION_LEADERBOARD
};

extern u8 GameModeOnline;
extern u8 REGION;
extern u32 TTS_CHECK;
extern u32 U32_RBBG_HOOK_PT1;
extern u32 U32_RBBG_HOOK_PT2;
extern u32 U32_RATE_HOOK;
extern u16 U32_ACCURATE_ITEMS;
extern u16 U32_TRAIL1;
extern u8 U8_30FPS;
extern u16 U32_COLORS;
extern u8 U8_MENU;
extern u16 U16_BATTLE;
extern u16 U16_MENUS;
extern u16 U16_CHARACTER;
extern u8 U8_BRSTMS;
extern u16 U16_CONTROLLER;
extern u16 U16_MINIMAPITEMS;
extern u16 U16_MISSION;
extern u16 U16_STAR;
extern u16 U32_RUBBERBANDING;
extern u16 U16_LAKITU;
extern u16 U16_NOVOICE;
extern u16 U16_BANANAS;
extern u16 U16_DCS;
extern u16 U16_POSITION;
extern u16 U16_MINIMAPS;
extern u16 U16_FINISH_TIMES;
extern u16 U16_FOV;
extern u16 U16_CPUS;
extern u16 U16_LUMA;
extern u16 U16_FONT;
extern u32 AntiCheat4;
extern u16 U16_EFFECTS;
extern u32 CodeHandlerIKW;
extern u16 U16_MENU_SOUNDS;
extern u16 U16_WINGS;
extern u8 U8_BRAKEDRIFTING;
extern u16 U16_PERFORMANCE;
extern u16 U16_PREDICTION;
extern u16 U16_TITLE1;
extern u16 U16_TITLE2;
extern u16 U16_MENUSUI;
extern u16 U16_RACECOUNTMOD;
extern u16 U16_NEWITEMS;
extern u16 U16_AUTOACCEL;
extern u16 U16_LIGHTNINGFLASH;
extern u16 U16_QUITCONFIRM;
extern u16 U16_MILLISECONDS;
extern u16 U16_ITEMBOXES;
extern u16 U16_TRANSMISSION;
extern u16 U16_BULLETBILLTOGGLE;
extern u16 U16_MIISCAMERA;
extern u16 U16_FCOFFLINE;
extern u16 U16_FCONLINE;
extern u16 U16_OTHERMEGA;
extern u16 U16_OTHERSTAR;
extern u16 U16_MULTICHANNEL;
extern u16 U16_ENGINE;
extern u16 U16_VOLUME;
extern u16 U16_MEGA;
extern u16 U16_STARMUSIC;
extern u16 U16_SQUISH;
extern u16 U16_THWOMP;
extern u16 U16_CHOMP;
extern u16 U16_GAMEPLAY1;
extern u16 U16_GAMEPLAY2;
extern u16 U16_GAMEPLAY3;
extern u16 U16_GAMEPLAY4;
extern u16 U16_GAMEPLAY5;
extern u16 U16_GAMEPLAY6;
extern u16 U16_GAMEPLAY7;
extern u16 U16_GAMEPLAY8;
extern u16 U16_GAMEPLAY9;
extern u16 U16_TURNINAIR;
extern u16 U16_GAMEPLAYA;
extern u16 U16_GAMEPLAYB;
extern u16 U16_GAMEPLAYC;
extern u16 U16_GAMEPLAYC2;
extern u16 U16_GAMEPLAYD;
extern u16 U16_GAMEPLAYE;
extern u8 U8_INPUT_VIEW;
extern u8 U8_DEBUG;
extern u8 U8_RED1;
extern u8 U8_GREEN1;
extern u8 U8_BLUE1;
extern u8 U8_ALPHA1;
extern u8 U8_RED2;
extern u8 U8_GREEN2;
extern u8 U8_BLUE2;
extern u8 U8_ALPHA2;
extern u8 U8_RED3;
extern u8 U8_GREEN3;
extern u8 U8_BLUE3;
extern u8 U8_ALPHA3;
extern u8 U8_RED4;
extern u8 U8_GREEN4;
extern u8 U8_BLUE4;
extern u8 U8_ALPHA4;
extern u8 U8_RED5;
extern u8 U8_GREEN5;
extern u8 U8_BLUE5;
extern u8 U8_ALPHA5;
extern u8 U8_RED6;
extern u8 U8_GREEN6;
extern u8 U8_BLUE6;
extern u8 U8_ALPHA6;
extern u8 U8_WWS_CHECK;
extern u16 U16_WAITING;
extern u16 WiiInput;
extern u16 GCInput;
extern u16 ClassicInput;
extern u32 ItemRainOnlineFixHook;
extern u16 U16_POINT_DISTRO;
extern u16 U16_CROWN;
extern u16 U16_FRIENDLY_FIRE;
extern u8 U8_EFFECTSNAME;
extern float U32_MUSIC_SPEED;
extern float U32_TEST_CURRENT_KCP;
extern u8 U8_BUTTONS_WII;
extern u8 U8_BUTTONS_GCN;
extern u32 ItemCycler3;
extern u32 RacerCount;
extern u16 U16_FAST_MENUS;
extern u16 U16_MISSION_MUSIC;
extern u32 GeckoLoader;
extern u8 U8_INPUT;
extern u8 U8_OFFLINE_FLAG;
extern u16 U16_TRACK_MANIA;
extern u32 U32_TEST_IDS;
extern u32 U32_AUTHOR_IDS;
extern u32 U32_MISSION_MODE_ENABLE;
extern u8 OfflineFlag_GameMode;
extern u16 U16_FREE_ROAM;
extern u8 U8_RACE_MENUS1;
extern u8 U8_RACE_MENUS2;
extern u8 U8_RACE_MENUS3;
extern u8 U8_MENUSINGLE1;
extern u8 U8_MENUSINGLE2;
extern u8 U8_MENUSINGLE3;
extern u8 U8_MENUSINGLE4;
extern u8 U8_MENUSINGLE5;
extern u8 U8_MENUMULTI1;
extern u8 U8_MENUMULTI2;
extern u8 U8_MENUMULTI3;
extern u8 U8_MENUMULTI4;
extern u8 U8_FONT;
extern u16 U16_MISSION_MODE_FIX;
extern u8 U8_COMPATIBILITY;
extern u8 U8_MY_STUFF;
extern u16 U16_MINIMAP_ROTATION;
extern u16 U16_TOPOGRAPHY;
extern u16 U16_HAW;
extern float F32_MENUSPEED;
extern u16 U8_BATTLE_CHECK;

#endif