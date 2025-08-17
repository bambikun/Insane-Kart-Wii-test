#include <kamek.hpp>
#include <Settings/SettingsParam.hpp>
#include <MKVN.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>

namespace Pulsar{
namespace Settings{

//Most of these are used to enable/disable toggles for other codes to load.
// 30FPS
kmWrite32(0x80554224, 0x3C808000);
kmWrite32(0x80554228, 0x88841200);
kmWrite32(0x8055422C, 0x48000044);

void MenuThemeSwitch(){
    U8_MENUSINGLE1 = 0x65;
    U8_MENUMULTI1 = 0x69;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_MENU_THEME) == MENU_MK8) {
        U8_MENUSINGLE1 = 0x61;
        U8_MENUMULTI1 = 0x61;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_MENU_THEME) == MENU_SMK) {
        U8_MENUSINGLE1 = 0x62;
        U8_MENUMULTI1 = 0x62;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_MENU_THEME) == MENU_MKDD) {
        U8_MENUSINGLE1 = 0x63;
        U8_MENUMULTI1 = 0x63;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_MENU_THEME) == MENU_SMO) {
        U8_MENUSINGLE1 = 0x64;
        U8_MENUMULTI1 = 0x64;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_MENU_THEME) == MENU_DX) {
        U8_MENUSINGLE1 = 0x66;
        U8_MENUMULTI1 = 0x66;
    }
    U8_MENUSINGLE2 = U8_MENUSINGLE1;
    U8_MENUMULTI2 = U8_MENUMULTI1;
    U8_MENUSINGLE3 = U8_MENUSINGLE1;
    U8_MENUMULTI3 = U8_MENUMULTI1;
    U8_MENUSINGLE4 = U8_MENUSINGLE1;
    U8_MENUMULTI4 = U8_MENUMULTI1;
    U8_MENUSINGLE5 = U8_MENUSINGLE1;
    U16_CHARACTER = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_FAVORITE_CHARACTER);
    if(U16_MISSION_MODE_FIX != 0x0001) U16_CPUS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3,SETTINGS_CPU_DIFFICULTY);
    else U16_CPUS = 0x0000;
    U16_VOLUME = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_BRSTM_VOLUME) == VOLUME_90) {
        U16_VOLUME = 0x0005;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_BRSTM_VOLUME) == VOLUME_80) {
        U16_VOLUME = 0x0004;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_BRSTM_VOLUME) == VOLUME_70) {
        U16_VOLUME = 0x0003;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_BRSTM_VOLUME) == VOLUME_60) {
        U16_VOLUME = 0x0002;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_BRSTM_VOLUME) == VOLUME_50) {
        U16_VOLUME = 0x0001;
    }
    U16_HAW = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_HOST,SETTINGHOST_RADIO_HOSTWINS) == HOSTSETTING_HOSTWINS_ENABLED && U8_WWS_CHECK != 0x01) {
        U16_HAW = 0x0001;
    }
    U16_PERFORMANCE = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_PERFORMANCE_BAR);
}
static PageLoadHook THEMINGUI(MenuThemeSwitch);

void GameModeToggle() {
    const SectionId sectionMode = SectionMgr::sInstance->curSection->sectionId;
    if(sectionMode == SECTION_CREATE_NEW_SAVE && WiiInput == 0x8000 || sectionMode == SECTION_CREATE_NEW_SAVE && GCInput == 0x1080 || sectionMode == SECTION_CREATE_NEW_SAVE && ClassicInput == 0x800) Debug::LaunchSoftware();
    if(sectionMode == SECTION_CORRUPT_SAVE && WiiInput == 0x8000 || sectionMode == SECTION_CORRUPT_SAVE && GCInput == 0x1080 || sectionMode == SECTION_CORRUPT_SAVE && ClassicInput == 0x800) Debug::LaunchSoftware();
    if(U8_WWS_CHECK != 0x01 && OfflineFlag_GameMode != 0x01) {
    U16_GAMEPLAY1 = 0x0000;
    U16_GAMEPLAY2 = 0x0000;
    U16_GAMEPLAY3 = 0x0000;
    U16_GAMEPLAY4 = 0x0000;
    U16_GAMEPLAY5 = 0x0000;
    U16_GAMEPLAY6 = 0x0000;
    U16_GAMEPLAY7 = 0x0000;
    U16_GAMEPLAY8 = 0x0000;
    U16_GAMEPLAY9 = 0x0000;
    U16_GAMEPLAYA = 0x0000;
    U16_GAMEPLAYB = 0x0000;
    U16_GAMEPLAYC = 0x0000;
    U16_GAMEPLAYC2 = 0x0000;
    U16_GAMEPLAYD = 0x0000;
    U16_GAMEPLAYE = 0x0000;
    U16_FREE_ROAM = 0x0000;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_BOMB_BLAST) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY1 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_INFINITE_ACCELERATION) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY2 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_BANANA_SLIP) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY3 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_RANDOM_ITEMS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY4 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_UNFAIR_ITEMS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY5 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_BLUE_SHELL_MADNESS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY6 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_MUSHROOM_DASH) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY7 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_BUMPER_KARTS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY8 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_RANDOM_EFFECTS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY9 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_ITEM_RAIN) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYA = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_SHELL_BREAK) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYB = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_CRAZY_ITEMS) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYC = 0x0001;
        U16_GAMEPLAYC2 = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_RIIBALANCED) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYD = 0x0001;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_MODE_ULTRAS_ENABLED) && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYE = 0x0001;
    }
    if(U8_WWS_CHECK != 0x01  && OfflineFlag_GameMode != 0x01) GameModeOnline = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_HOST,SETTINGS_GAME_MODE);
    if(sectionMode == SECTION_SINGLE_P_FROM_MENU) OfflineFlag_GameMode = 0x01;
    if(sectionMode == SECTION_MAIN_MENU_FROM_MENU) OfflineFlag_GameMode = 0x00;
    if(sectionMode == SECTION_MAIN_MENU_FROM_MENU) U16_MISSION_MODE_FIX = 0x0000;
    U8_30FPS = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY, SETTINGS_30_FPS) == 1 /*|| U16_GAMEPLAYA == 0x0001*/) {
    U8_30FPS = 0x01;
    }
    if(System::sInstance->IsContext(Pulsar::PULSAR_POINT_DISTRO)) U16_POINT_DISTRO = 0x0001;
    U16_FAST_MENUS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_FASTER) {
        U16_FAST_MENUS = 0x0001;
    }
U8_BATTLE_CHECK = 0x0;
if(Racedata::sInstance->menusScenario.settings.gamemode == MODE_BATTLE || Racedata::sInstance->menusScenario.settings.gamemode == MODE_PUBLIC_BATTLE || Racedata::sInstance->menusScenario.settings.gamemode == MODE_PRIVATE_BATTLE) {
    U8_BATTLE_CHECK = 0x1;
}

    SectionId id = SectionMgr::sInstance->nextSectionId;
    if (id == SECTION_SINGLE_P_BT_NEXT_BATTLE) {
        id = SECTION_SINGLE_P_VS_NEXT_RACE;
        SectionMgr::sInstance->nextSectionId = id;
    }
    if(id == SECTION_AWARD_38) {
        id = SECTION_MAIN_MENU_FROM_MENU;
        SectionMgr::sInstance->nextSectionId = id;
    }
    if(U8_BATTLE_CHECK == 0x0001 && id == SECTION_VS_RACE_INTRO) {
        id = SECTION_BALLOON_BATTLE_INTRO;
        SectionMgr::sInstance->nextSectionId = id;
    }
    if(Racedata::sInstance->menusScenario.settings.gamemode != MODE_GRAND_PRIX && id == SECTION_GP_INTRO) {
        id = SECTION_VS_RACE_INTRO;
        SectionMgr::sInstance->nextSectionId = id;
    }
    U16_FINISH_TIMES = 0x00;
    if(U8_BATTLE_CHECK != 0x0001) U16_FINISH_TIMES = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ONLINE,SETTINGS_SHOW_FINISH_TIMES);
}
static PageLoadHook GAMEMODE(GameModeToggle);

void FontToggle() {
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_FONT) > 0) {
        U8_FONT = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_FONT) + 0x60;
    }
    U16_MENU_SOUNDS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_MENU_SOUNDS);
    U16_RACECOUNTMOD = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_RACE_COUNT_MODIFIER);
}
BootHook FONTTOGGLE(FontToggle, 1);

void Remove_Background_Blur_Glow(){
    U32_RBBG_HOOK_PT1 = 0x03000000;
    U32_RBBG_HOOK_PT2 = 0x3f000000;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS, SETTINGS_BLUR_FIXES) == BLUR_FIXES_ON){
        U32_RBBG_HOOK_PT1 = 0x00000000;
        U32_RBBG_HOOK_PT2 = 0x30000000;
    }
    U16_LAKITU = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2, SETTINGS_KILL_LAKITU);
    U32_ACCURATE_ITEMS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1, SETTINGS_ACCURATE_ITEMS);
    U32_TRAIL1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY, SETTINGS_AUTO_TRAIL_ITEMS);
    U32_COLORS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3, SETTINGS_NAMETAGS);
    U8_MENU = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY, SETTINGS_CUPS_SCROLLING)+1;
    U8_RACE_MENUS1 = 0x65;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_RACE_THEME) == RACE_MK8) {
        U8_RACE_MENUS1 = 0x61;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_RACE_THEME) == RACE_SMK) {
        U8_RACE_MENUS1 = 0x62;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_RACE_THEME) == RACE_MKDD) {
        U8_RACE_MENUS1 = 0x63;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_VISUALS,SETTINGS_RACE_THEME) == RACE_SMO) {
        U8_RACE_MENUS1 = 0x64;
    }
    U8_RACE_MENUS2 = U8_RACE_MENUS1;
    U8_RACE_MENUS3 = U8_RACE_MENUS1;
    U8_BRSTMS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_PACK_MUSIC);
    U16_CONTROLLER = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_SILENT_CONTROLLER_CHANGE);
    U16_MINIMAPITEMS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1, SETTINGS_ITEMS_ON_MINIMAP);
    U16_STAR = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_STAR_ANIMATION);
    U32_RUBBERBANDING = 0x0001;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3,SETTINGS_CPU_RUBBERBANDING) == RUBBERBANDING_ENABLED || U16_MISSION_MODE_FIX == 0x0001) {
        U32_RUBBERBANDING = 0x0000;
    }
    U16_NOVOICE = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_CHARACTER_SOUNDS);
    U16_BANANAS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_TRIPLE_BANANAS);
    U16_DCS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ONLINE,SETTINGS_NO_IDLE_DC) == IDLE_DC_DISABLED) {
        U16_DCS = 0x0001;
    }
    U16_POSITION = 0x0001;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ONLINE,SETTINGS_POSITION_TRACKER) == POSITION_TRACKER_DISABLED) {
        U16_POSITION = 0x0000;
    }
    U16_MINIMAPS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3,SETTINGS_COLORED_MINIMAPS);
    U16_FOV = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_BETTER_MEGA_FOV);
    U16_LUMA = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_REMOVE_LUMA);
    U16_EFFECTS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_EFFECTS_ON_MINIMAP);
    U8_EFFECTSNAME = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_EFFECTS_ON_MINIMAP) + 0x6D;
    U16_WINGS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY,SETTINGS_1ST_PERSON);
    U8_BRAKEDRIFTING = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY,SETTINGS_BRAKE_DRIFTING) == BRAKE_DRIFTING_ENABLED) {
        U8_BRAKEDRIFTING = 0x01;
    }
    U16_PREDICTION = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ONLINE,SETTINGS_OPPONENT_PREDICTION);
    U16_NEWITEMS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_RECEIVE_MINIMAP_ICONS_SIZE);
    U16_AUTOACCEL = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE4,SETTINGS_AUTO_ACCELERATION) == AUTO_ACCELERATE_ENABLED && TTS_CHECK != 0x00000001) {
        U16_AUTOACCEL = 0x0001;
    }
    U16_LIGHTNINGFLASH = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY,SETTINGS_NO_LIGHTNING_FLASH);
    U16_QUITCONFIRM = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3,SETTINGS_SHOW_QUIT_CONFIRMATION);
    U16_MILLISECONDS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE4,SETTINGS_MILLISECONDS_MODIFIER);
    U16_ITEMBOXES = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_ITEMBOXES_ON_MINIMAP);
    U16_BULLETBILLTOGGLE = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1,SETTINGS_NO_BULLET_MODEL);
    U16_MIISCAMERA = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_MIIS_STARE_AT_CAMERA);
    U16_OTHERMEGA = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_OTHERS_MEGA_MUSIC);
    U16_OTHERSTAR = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_OTHERS_STAR_MUSIC);
    U16_MULTICHANNEL = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_MULTI_CHANNEL);
    U16_ENGINE = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_ENGINE_SOUNDS);
    U16_MEGA = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_MEGA_MUSIC);
    U16_STARMUSIC = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND1,SETTINGS_STAR_MUSIC);
    U16_SQUISH = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_MUSIC_DISTORTION);
    U16_THWOMP = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_THWOMP_SOUND);
    U16_CHOMP = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_SOUND2,SETTINGS_CHOMP_LAUNCH);
    U8_INPUT_VIEW = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE4,SETTINGS_INPUT_VIEWER);
    U16_MINIMAP_ROTATION = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE4,SETTINGS_ICON_ROTATION);
    U8_DEBUG = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ACCESSIBILITY,SETTINGS_KMP_INFO);
    U16_WAITING = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_ONLINE,SETTINGS_WAITING_MUSIC);
    U16_TRACK_MANIA = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE3,SETTINGS_TRACKMANIA_CAM);
    U8_COMPATIBILITY = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_COMPATIVILITY_MODE) + 0x72;
    U16_POINT_DISTRO = 0x0000;
    U16_CROWN = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE4,SETTINGS_CROWN);
    U16_TOPOGRAPHY = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE1, SETTINGS_MINIMAP_TOPOGRAPHY);
    U32_MUSIC_SPEED = 1.0f;
}
static SectionLoadHook RBBG_Hook(Remove_Background_Blur_Glow);

void RecolorsMenus() {
    U8_RED1 = 0xFF;
    U8_GREEN1 = 0x00;
    U8_BLUE1 = 0xFF;
    U8_ALPHA1= 0xFF;
    U8_RED2 = 0xFF;
    U8_GREEN2 = 0x7F;
    U8_BLUE2 = 0xFF;
    U8_ALPHA2= 0xFF;
    U8_RED3 = 0xFF;
    U8_GREEN3 = 0x00;
    U8_BLUE3 = 0xFF;
    U8_ALPHA3= 0x70;
    U8_RED4 = 0xFF;
    U8_GREEN4 = 0x00;
    U8_BLUE4 = 0xFF;
    U8_ALPHA4= 0xFF;
    U8_RED5 = 0xFF;
    U8_GREEN5 = 0x7F;
    U8_BLUE5 = 0xFF;
    U8_ALPHA5= 0xFF;
    U8_RED6 = 0xFF;
    U8_GREEN6 = 0x00;
    U8_BLUE6 = 0xFF;
    U8_ALPHA6= 0x70;
if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_MENU_COLOR) == COLOR_DEFAULT) {
    U8_RED1 = 0xFF;
    U8_GREEN1 = 0xFF;
    U8_BLUE1 = 0x00;
    U8_ALPHA1= 0xFF;

    U8_RED2 = 0xD2;
    U8_GREEN2 = 0xAA;
    U8_BLUE2 = 0x00;
    U8_ALPHA2= 0xFF;

    U8_RED3 = 0xD2;
    U8_GREEN3 = 0xAA;
    U8_BLUE3 = 0x00;
    U8_ALPHA3= 0x46;

    U8_RED4 = 0xFF;
    U8_GREEN4 = 0xFF;
    U8_BLUE4 = 0x00;
    U8_ALPHA4= 0xFF;

    U8_RED5 = 0xD2;
    U8_GREEN5 = 0xAA;
    U8_BLUE5 = 0x00;
    U8_ALPHA5= 0xFF;
    
    U8_RED6 = 0xD2;
    U8_GREEN6 = 0xAA;
    U8_BLUE6 = 0x00;
    U8_ALPHA6= 0x46;
    }
if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC,SETTINGMENU_MENU_COLOR) == COLOR_CUSTOM) {

    U8_RED1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_RED)*16 +15;
    U8_GREEN1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_GREEN)*16 +15;
    U8_BLUE1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_BLUE)*16 +15;
    U8_ALPHA1= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_ALPHA)*16 +15;

    U8_RED2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_RED)*16 +15;
    U8_GREEN2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_GREEN)*16 +15;
    U8_BLUE2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_BLUE)*16 +15;
    U8_ALPHA2= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_ALPHA)*16 +15;

    U8_RED3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_RED)*16 +15;
    U8_GREEN3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_GREEN)*16 +15;
    U8_BLUE3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_BLUE)*16 +15;
    U8_ALPHA3= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_ALPHA)*16 +15;

    U8_RED4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_RED)*16 +15;
    U8_GREEN4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_GREEN)*16 +15;
    U8_BLUE4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_BLUE)*16 +15;
    U8_ALPHA4= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_ALPHA)*16 +15;

    U8_RED5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_RED)*16 +15;
    U8_GREEN5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_GREEN)*16 +15;
    U8_BLUE5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_BLUE)*16 +15;
    U8_ALPHA5= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_ALPHA)*16 +15;

    U8_RED6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_RED)*16 +15;
    U8_GREEN6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_GREEN)*16 +15;
    U8_BLUE6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_BLUE)*16 +15;
    U8_ALPHA6= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_COLORS,SETTINGS_SECONDARY_ALPHA)*16 +15;

    }
}
static PageLoadHook RECOLORTHIS(RecolorsMenus);
}
}