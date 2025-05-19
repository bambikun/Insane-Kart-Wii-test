#include <kamek.hpp>
#include <Settings/SettingsParam.hpp>
#include <MKVN.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>

namespace Pulsar{
namespace Settings{

//Most of these are used to enable/disable toggles for other codes to load.

void Remove_Background_Blur_Glow(){
    U32_RBBG_HOOK_PT1 = 0x03000000;
    U32_RBBG_HOOK_PT2 = 0x3f000000;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1, SETTINGS_BLUR_FIXES) == BLUR_FIXES_ON){
        U32_RBBG_HOOK_PT1 = 0x00000000;
        U32_RBBG_HOOK_PT2 = 0x30000000;
    }
}
static SectionLoadHook RBBG_Hook(Remove_Background_Blur_Glow);

void LakituRemove(){
    U16_LAKITU = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_KILL_LAKITU) == KILL_LAKITU_ENABLED){
        U16_LAKITU = 0x0001;
    }
}
static SectionLoadHook NOLAKITU(LakituRemove);

void AccurateItems(){
    U32_ACCURATE_ITEMS = 0x0000;

    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_ACCURATE_ITEMS) == 1) {
        U32_ACCURATE_ITEMS = 0x0001;
    }
}
static SectionLoadHook ACCURATE_ITEMS_Hook(AccurateItems);

void AutoTrailItems(){
    U32_TRAIL1 = 0x0000;

    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_AUTO_TRAIL_ITEMS) == ITEMS_AUTO_TRAIL_ENABLED) {
            U32_TRAIL1 = 0x0001;
    }
}
static SectionLoadHook ITEM_TRAIL(AutoTrailItems);


// 30FPS
kmWrite32(0x80554224, 0x3C808000);
kmWrite32(0x80554228, 0x88841200);
kmWrite32(0x8055422C, 0x48000044);

void Framerate(){
    U8_30FPS = 0x00;

    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_30_FPS) == THIRTY_FPS_ON) {
        U8_30FPS = 0x01;
    }
}
static SectionLoadHook FRAMERATE(Framerate);

void ColoredMiiTags(){
    U32_COLORS = 0x0000;

    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_COLORED_NAMES) == 1) {
        U32_COLORS = 0x0001;
    }
}
static SectionLoadHook MIICOLORS(ColoredMiiTags);

void MenuScrolling(){
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CUP_SCROLLING) == CUPS_2) {
        U8_MENU = 0x01;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CUP_SCROLLING) == CUPS_4) {
        U8_MENU = 0x02;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CUP_SCROLLING) == CUPS_6) {
        U8_MENU = 0x03;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CUP_SCROLLING) == CUPS_8) {
        U8_MENU = 0x04;
    }
}
static SectionLoadHook SCROLLING(MenuScrolling);

void RaceThemeSwitch(){
    U8_RACE_MENUS1 = 0x65;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_RACE_THEME) == RACE_MK8) {
        U8_RACE_MENUS1 = 0x61;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_RACE_THEME) == RACE_SMK) {
        U8_RACE_MENUS1 = 0x62;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_RACE_THEME) == RACE_MKDD) {
        U8_RACE_MENUS1 = 0x63;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_RACE_THEME) == RACE_SMO) {
        U8_RACE_MENUS1 = 0x64;
    }
    U8_RACE_MENUS2 = U8_RACE_MENUS1;
    U8_RACE_MENUS3 = U8_RACE_MENUS1;
}
static SectionLoadHook THEMINGRACE(RaceThemeSwitch);

void MenuThemeSwitch(){
    U8_MENUSINGLE1 = 0x65;
    U8_MENUMULTI1 = 0x69;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MENU_THEME) == MENU_MK8) {
        U8_MENUSINGLE1 = 0x61;
        U8_MENUMULTI1 = 0x61;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MENU_THEME) == MENU_SMK) {
        U8_MENUSINGLE1 = 0x62;
        U8_MENUMULTI1 = 0x62;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MENU_THEME) == MENU_MKDD) {
        U8_MENUSINGLE1 = 0x63;
        U8_MENUMULTI1 = 0x63;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MENU_THEME) == MENU_SMO) {
        U8_MENUSINGLE1 = 0x64;
        U8_MENUMULTI1 = 0x64;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MENU_THEME) == MENU_DX) {
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
}
static PageLoadHook THEMINGUI(MenuThemeSwitch);

void FavChar() {
    U16_CHARACTER = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_DEFAULT_CHARACTER) == FAVORITE_CHAR_ENABLED) {
        U16_CHARACTER = 0x0001;
    }
}
static PageLoadHook FAVCHARACTER(FavChar);

void BRSTMS() {
    U8_BRSTMS = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_PACK_MUSIC) == PACK_MUSIC_ENABLED) {
        U8_BRSTMS = 0x01;
    }
}
static SectionLoadHook BRSTMTOGGLE(BRSTMS);

void SilentController() {
    U16_CONTROLLER = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_SILENT_CONTROLLER_CHANGE) == SILENT_CONTROLLER_CHANGE_ENABLED) {
        U16_CONTROLLER = 0x0001;
    }
}
static SectionLoadHook CONTROLLERCHANGE(SilentController);

void ItemsOnMinimap() {
    U16_MINIMAPITEMS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_ITEMS_ON_MINIMAP) == ITEMS_ON_MINIMAP_ENABLED) {
        U16_MINIMAPITEMS = 0x0001;
    }
}
static SectionLoadHook MINIITEMS(ItemsOnMinimap);

void StarAnimation() {
    U16_STAR= 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_STAR_ANIMATION) == STAR_ANIMATION_ON) {
        U16_STAR = 0x0001;
    }
}
static SectionLoadHook STAR(StarAnimation);

void Rubberbanding() {
    U32_RUBBERBANDING = 0x0001;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CPU_RUBBERBANDING) == RUBBERBANDING_ENABLED || U16_MISSION_MODE_FIX == 0x0001) {
        U32_RUBBERBANDING = 0x0000;
    }
}
static PageLoadHook RUBBERBANDING(Rubberbanding);

void NoCharacterVoices() {
    U16_NOVOICE = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_MUTE_CHARACTERS) == MUTE_CHARACTERS_ENABLED) {
        U16_NOVOICE = 0x0001;
    }
}
static SectionLoadHook NoSounds(NoCharacterVoices);

void TripleBananas() {
    U16_BANANAS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_TRIPLE_BANANAS) == TRIPLE_BANANAS_ROTATE) {
        U16_BANANAS = 0x0001;
    }
}
static SectionLoadHook TRIPLEBANANAS(TripleBananas);

void IdleDC() {
    U16_DCS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_NO_IDLE_DC) == IDLE_DC_DISABLED) {
        U16_DCS = 0x0001;
    }
}
static SectionLoadHook NODCS(IdleDC);

void PositionTracker() {
    U16_POSITION = 0x0001;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_POSITION_TRACKER) == POSITION_TRACKER_DISABLED) {
        U16_POSITION = 0x0000;
    }
}
static SectionLoadHook POS(PositionTracker);

void ColoredMinimaps() {
    U16_MINIMAPS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_COLORED_MINIMAPS) == COLORED_MINIMAPS_ENABLED) {
        U16_MINIMAPS = 0x0001;
    }
}
static SectionLoadHook COLOREDUWU(ColoredMinimaps);

void FinishTimes() {
    U16_FINISH_TIMES = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_FINISH_TIMES) == FINISH_TIMES_ENABLED) {
        U16_FINISH_TIMES = 0x0001;
    }
}
static SectionLoadHook FINISHTIMES(FinishTimes);

void MegaFOVToggle() {
    U16_FOV = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_MEGA_FOV) == MEGA_FOV_ENABLED) {
        U16_FOV = 0x0001;
    }
}
static SectionLoadHook MegaCamera(MegaFOVToggle);

void CPUDifficultyToggle() {
    if(U16_MISSION_MODE_FIX != 0x0001) U16_CPUS = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_CPU_DIFFICULTY);
    else U16_CPUS = 0x0000;
}
static PageLoadHook CPUToggle(CPUDifficultyToggle);

void NoLuma() {
    U16_LUMA = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_REMOVE_LUMA) == REMOVE_LUMA_ENABLED) {
        U16_LUMA = 0x0001;
    }
}
static SectionLoadHook LumaToggle(NoLuma);

void FontToggle() {
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_FONT) > 0) {
        U8_FONT = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_FONT) + 0x60;
    }
}
BootHook FONTTOGGLE(FontToggle, 1);

void EffectsOnMinimap() {
    U16_EFFECTS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_EFFECTS_ON_MINIMAP) == EFFECTS_ON_MINIMAP_ON) {
        U16_EFFECTS = 0x0001;
    }
}
static SectionLoadHook KARTEFFECT(EffectsOnMinimap);

void MenuSoundToggle() {
    U16_MENU_SOUNDS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_MENU_SOUNDS) == MENU_SOUNDS_OFF) {
        U16_MENU_SOUNDS = 0x0001;
    }
}
BootHook MENUSOUNDS(MenuSoundToggle, 2);

void FirstPerson() {
    U16_WINGS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_FIRST_PERSON) == FIRST_PERSON_ENABLED) {
        U16_WINGS = 0x0001;
    }
}
static SectionLoadHook FIRSTCAM(FirstPerson);

void BrakeDriftingToggle() {
    U8_BRAKEDRIFTING = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_BRAKE_DRIFTING) == BRAKE_DRIFTING_ENABLED) {
        U8_BRAKEDRIFTING = 0x01;
    }
}
static RaceLoadHook BRAKEDRIFTING(BrakeDriftingToggle);

void PerformanceBar() {
    U16_PERFORMANCE = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_PERFORMANCE_BAR) == PERFORMANCE_BAR_ENABLED) {
        U16_PERFORMANCE = 0x0001;
    }
}
BootHook PERFORMANCE(PerformanceBar, 3);

void Predition() {
    U16_PREDICTION = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_OPPONENT_PREDICTION) == OPPONENT_PREDICTION_ENABLED) {
        U16_PREDICTION = 0x0001;
    }
}
static RaceLoadHook PREDICTION(Predition);

void RaceCountMod() {
    U16_RACECOUNTMOD = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_RACE_COUNT_MOD) == RACE_COUNT_MODIFIER_ENABLED) {
        U16_RACECOUNTMOD = 0x0001;
    }
}
BootHook RACECOUNT(RaceCountMod, 4);

void NewItem() {
    U16_NEWITEMS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_NEW_ITEMS) == NEW_ITEMS_ENABLED) {
        U16_NEWITEMS = 0x0001;
    }
}
static RaceLoadHook NEWITEMSS(NewItem);

void AutoAcceleration() {
    U16_AUTOACCEL = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_AUTO_ACCELERATION) == AUTO_ACCELERATE_ENABLED && TTS_CHECK != 0x00000001) {
        U16_AUTOACCEL = 0x0001;
    }
}
static SectionLoadHook AUTOSTART(AutoAcceleration);

void LightningFlashToggle() {
    U16_LIGHTNINGFLASH = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_LIGHTNING_FLASH) == LIGHTNING_FLASH_DISABLED) {
        U16_LIGHTNINGFLASH = 0x0001;
    }
}
static SectionLoadHook LIGHTNINGFLASH(LightningFlashToggle);

void QuitConfirmToggle() {
    U16_QUITCONFIRM = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_QUIT_CONFIRMATION) == QUIT_CONFIRMATION_ENABLED) {
        U16_QUITCONFIRM = 0x0001;
    }
}
static RaceLoadHook QUITCONFIRM(QuitConfirmToggle);

void MillisecondsMod() {
    U16_MILLISECONDS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_MILLISECONDS_MODE) == MILLISECONDS_ITEMS) {
        U16_MILLISECONDS = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_MILLISECONDS_MODE) == MILLISECONDS_SHOCK) {
        U16_MILLISECONDS = 0x0002;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_MILLISECONDS_MODE) == MILLISECONDS_CRUSH) {
        U16_MILLISECONDS = 0x0003;
    }
}
static SectionLoadHook MILLISECONDSMODS(MillisecondsMod);

void ItemBoxesOnMinimap() {
    U16_ITEMBOXES = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_ITEM_BOXES_ON_MINIMAP) == ITEM_BOXES_MINIMAP_ENABLED) {
        U16_ITEMBOXES = 0x0001;
    }
}
static SectionLoadHook MEMEMAP(ItemBoxesOnMinimap);

void TransmissionToggle() {
    U16_TRANSMISSION = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_TRANSMISSION) == TRANSMISSION_INSIDE && TTS_CHECK != 0x00000001) {
        U16_TRANSMISSION = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_TRANSMISSION) == TRANSMISSION_OUTSIDE && TTS_CHECK != 0x00000001) {
        U16_TRANSMISSION = 0x0002;
    }
}
static SectionLoadHook TRANSMISSION(TransmissionToggle);

void BulletModel() {
    U16_BULLETBILLTOGGLE = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_BULLET_MODEL) == BULLET_MODEL_DISABLED) {
        U16_BULLETBILLTOGGLE = 0x0001;
    }
}
static SectionLoadHook BULLETBILLTOGGLE(BulletModel);

void MiisLookAtCamera() {
    U16_MIISCAMERA = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW4,SETTINGS_MII_CAMERAS) == MII_STARE_DISABLED) {
        U16_MIISCAMERA = 0x0001;
    }
}
static SectionLoadHook MIISTARE(MiisLookAtCamera);

void OtherMega() {
    U16_OTHERMEGA = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_OTHERS_MEGA) == OTHERS_MEGA_MUSIC_DISABLED) {
        U16_OTHERMEGA = 0x0001;
    }
}
static SectionLoadHook OTHERMEGA(OtherMega);

void OtherStar() {
    U16_OTHERSTAR = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_OTHERS_STAR) == OTHERS_STAR_MUSIC_DISABLED) {
        U16_OTHERSTAR = 0x0001;
    }
}
static SectionLoadHook OTHERSTAR(OtherStar);

void MultiChannelToggle() {
    U16_MULTICHANNEL = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_MULTI_CHANNEL) == MULTI_CHANNEL_ENABLED) {
        U16_MULTICHANNEL = 0x0001;
    }
}
static SectionLoadHook MULTIMUSIC(MultiChannelToggle);

void EngineToggle() {
    U16_ENGINE = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_ENGINE_SOUNDS) == ENGINE_SOUNDS_DISABLED) {
        U16_ENGINE = 0x0001;
    }
}
static SectionLoadHook ENGINESOUNDS(EngineToggle);

void BRSTMVolume() {
    U16_VOLUME = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_BRSTM_VOLUME) == VOLUME_90) {
        U16_VOLUME = 0x0005;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_BRSTM_VOLUME) == VOLUME_80) {
        U16_VOLUME = 0x0004;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_BRSTM_VOLUME) == VOLUME_70) {
        U16_VOLUME = 0x0003;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_BRSTM_VOLUME) == VOLUME_60) {
        U16_VOLUME = 0x0002;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_BRSTM_VOLUME) == VOLUME_50) {
        U16_VOLUME = 0x0001;
    }
}
static SectionLoadHook VOLUME(BRSTMVolume);

void OwnMegaMusic() {
    U16_MEGA = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_MEGA_MUSIC) == MEGA_MUSIC_DISABLED) {
        U16_MEGA = 0x0001;
    }
}
static SectionLoadHook MEGAMUSIC(OwnMegaMusic);

void OwnStarMusic() {
    U16_STARMUSIC = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_STAR_MUSIC) == STAR_MUSIC_DISABLED) {
        U16_STARMUSIC = 0x0001;
    }
}
static SectionLoadHook STARMUSIC(OwnStarMusic);

void ShockEffect() {
    U16_SQUISH = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_SQUISH_EFFECT) == SQUISH_DISABLED) {
        U16_SQUISH = 0x0001;
    }
}
static SectionLoadHook SQUISH(ShockEffect);

void ThwompDamage() {
    U16_THWOMP = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_THWOMP_SOUND) == THWOMP_DAMAGE_DISABLED) {
        U16_THWOMP = 0x0001;
    }
}
static SectionLoadHook DAMAGE(ThwompDamage);

void ChompLaunch() {
    U16_CHOMP = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_CHOMP_LAUNCH) == CHOMP_LAUNCH_DISABLED) {
        U16_CHOMP = 0x0001;
    }
}
static SectionLoadHook CHOMPLAUNCH(ChompLaunch);

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
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_BOB_OMB_BLAST && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY1 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_INFINITE_ACCELERATION && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY2 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_BANANA_SLIP && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY3 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_RANDOM_ITEMS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY4 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_UNFAIR_ITEMS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY5 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_BLUE_SHELL_MADNESS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY6 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_MUSHROOM_DASH && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY7 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_BUMPER_KARTS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY8 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_RANDOM_EFFECTS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAY9 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_ITEM_RAIN && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYA = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_SHELL_BREAK && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYB = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_CRAZY_ITEMS && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYC = 0x0001;
        U16_GAMEPLAYC2 = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_RIIBALANCED && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYD = 0x0001;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE) == GAME_MODE_ULTRAS_ENABLED && TTS_CHECK != 0x00000001 && U8_WWS_CHECK != 0x01 && sectionMode != SECTION_MISSION_MODE && OfflineFlag_GameMode != 0x01) {
        U16_GAMEPLAYE = 0x0001;
    }
    if(U8_WWS_CHECK != 0x01) GameModeOnline = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW1,SETTINGS_GAME_MODE);
    if(sectionMode == SECTION_SINGLE_P_FROM_MENU) OfflineFlag_GameMode = 0x01;
    if(sectionMode == SECTION_MAIN_MENU_FROM_MENU) OfflineFlag_GameMode = 0x00;
    if(sectionMode == SECTION_MAIN_MENU_FROM_MENU) U16_MISSION_MODE_FIX = 0x0000;
}
static PageLoadHook GAMEMODE(GameModeToggle);

void InputViewer() {
    U8_INPUT_VIEW = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW2,SETTINGS_INPUT_VIEWER) == INPUT_VIEWER_ON) {
        U8_INPUT_VIEW = 0x01;
    }
}
static SectionLoadHook INPUTDISPLAY(InputViewer);

void FasterMenuNavigation() {
    U16_FAST_MENUS = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MENU,SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_FASTER) {
        U16_FAST_MENUS = 0x0001;
    }
}
static SectionLoadHook FASTMENUS(FasterMenuNavigation);

void KMPInfoDisplay() {
    U8_DEBUG = 0x00;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGDEBUG_SCROLL_KMP) == DEBUGSETTING_KMP_KEYCPS) {
        U8_DEBUG = 0x01;
    }
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGDEBUG_SCROLL_KMP) == DEBUGSETTING_KMP_ITPTS) {
        U8_DEBUG = 0x02;
    }
}
static SectionLoadHook KMPINFO(KMPInfoDisplay);

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
if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_COLORS) == COLORS_DEFAULT) {
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
if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_COLORS) == COLORS_CUSTOM) {

    U8_RED1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE1 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA1= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;
    U8_RED2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE2 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA2= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;
    U8_RED3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE3 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA3= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;
    U8_RED4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE4 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA4= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;
    U8_RED5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE5 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA5= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;
    U8_RED6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_RED)*16 +15;
    U8_GREEN6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_GREEN)*16 +15;
    U8_BLUE6 = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_BLUE)*16 +15;
    U8_ALPHA6= Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_ALPHA)*16 +15;

    }
}
static PageLoadHook RECOLORTHIS(RecolorsMenus);

void WaitingMusic() {
    U16_WAITING = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW3,SETTINGS_WAITING_MUSIC) == WAITING_MUSIC_COURSE){
        U16_WAITING = 0x0001;
    }
}
static SectionLoadHook WAITINGMUSIC(WaitingMusic);

void TrackManiaCam() {
    U16_TRACK_MANIA = 0x0000;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_TRACK_MANIA) == CAM_ENABLED) {
        U16_TRACK_MANIA = 0x0001;
    }
}
static SectionLoadHook TRACKMANIA(TrackManiaCam);

void CompatibilityMode() {
    U8_COMPATIBILITY = 0x72;
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9,SETTINGS_COMPATIBILITY_MODE) == 1) U8_COMPATIBILITY = 0x73;
}
static PageLoadHook COMPATIBILITY(CompatibilityMode);

}
}