#ifndef _SETTINGS_PARAMS_
#define _SETTINGS_PARAMS_
#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>

namespace Pulsar {
namespace UI { class SettingsPanel; }
namespace Settings {

class Params {
public:
    static const int pulsarPageCount = 5;
    static const int userPageCount = 8;
    static const int pageCount = pulsarPageCount + userPageCount;

    static const int maxRadioCount = 6; //per page, due to space
    static const int maxScrollerCount = 5; //per page, due to space

    //Pulsar and User
    static u8 radioCount[pageCount];
    static u8 scrollerCount[pageCount];
    static u8 buttonsPerPagePerRow[pageCount][maxRadioCount];
    static u8 optionsPerPagePerScroller[pageCount][maxScrollerCount];

};

//Contains all the settings. 
enum Type {
    SETTINGSTYPE_MENU,
    SETTINGSTYPE_RACE,
    SETTINGSTYPE_HOST,
    SETTINGSTYPE_OTT,
    SETTINGSTYPE_KO,
    SETTINGSTYPE_IKW1,
    SETTINGSTYPE_IKW2,
    SETTINGSTYPE_IKW3,
    SETTINGSTYPE_IKW4,
    SETTINGSTYPE_IKW6,
    SETTINGSTYPE_IKW7,
    SETTINGSTYPE_IKW8,
    SETTINGSTYPE_IKW9,
};

//If you want to add settings to your packs, they go in this enum, and GetUserSettingValue should be used to obtain the value of a given setting
enum UserType {

};

}//namespace Settings

//SETTINGS ENUM, for the page, DO NOT FORGET THE +6 for scrollers (see menu settings for example)
//Use these 3 for "u32 setting" in GetSettingValue, the return will be the value of the other enums
enum MenuSettings {
    SETTINGMENU_RADIO_FASTMENUS = 0,
    SETTINGMENU_RADIO_LAYOUT = 1,
    SETTINGMENU_RADIO_MUSIC = 2,
    SETTINGMENU_SCROLL_BOOT = 0 + 6
};

enum RaceSettings {
    SETTINGRACE_RADIO_MII,
    SETTINGRACE_RADIO_SPEEDUP,
    SETTINGRACE_RADIO_BATTLE,
    SETTINGRACE_RADIO_BLUES,
    SETTINGRACE_RADIO_SOM,

    SETTINGRACE_SCROLL_SOM = 0 + 6
};

enum HostSettings {
    SETTINGHOST_RADIO_HOSTWINS = 0,
    SETTINGHOST_RADIO_CC = 1,
    SETTINGHOST_ALLOW_MIIHEADS = 2,

    SETTINGHOST_SCROLL_GP_RACES = 0 + 6
};

enum OTTSettings {
    SETTINGOTT_ONLINE = 0,
    SETTINGOTT_OFFLINE = 1,
    SETTINGOTT_ALLOWCHANGECOMBO = 2,
    SETTINGOTT_ALLOWUMTS = 3,
    SETTINGOTT_MUTEPTANDPLAYERS = 4,
};

enum KOSettings {
    SETTINGKO_ENABLED = 0,
    SETTINGKO_FINAL = 1,
    SETTINGKO_KOPERRACE = 0 + 6,
    SETTINGKO_RACESPERKO = 1 + 6,

};

enum IKW1 {
    SETTINGS_ACCURATE_ITEMS = 0,
    SETTINGS_BLUR_FIXES = 1,
    SETTINGS_30_FPS = 2,
    SETTINGS_STAR_ANIMATION = 3,
    SETTINGS_EFFECTS_ON_MINIMAP = 4,
    SETTINGS_MENU_SOUNDS = 5,

    SETTINGS_GAME_MODE = 0 + 6,
    SETTINGS_OPPONENT_PREDICTION = 1 + 6,
    SETTINGS_PERFORMANCE_BAR = 2 + 6,
    SETTINGS_BRAKE_DRIFTING = 3 + 6,
    SETTINGS_FIRST_PERSON = 4 + 6,
};

enum IKW2 {
    SETTINGS_COLORED_NAMES = 0,
    SETTINGS_DEFAULT_CHARACTER = 1,
    SETTINGS_PACK_MUSIC = 2,
    SETTINGS_AUTO_TRAIL_ITEMS = 3,
    SETTINGS_INPUT_VIEWER = 4,
    SETTINGS_SILENT_CONTROLLER_CHANGE = 5,

    SETTINGS_RACE_THEME = 0 + 6,
    SETTINGS_MENU_THEME = 1 + 6,
    SETTINGS_MUTE_CHARACTERS = 2 + 6,
    SETTINGS_KILL_LAKITU = 3 + 6,
    SETTINGS_ITEMS_ON_MINIMAP = 4 + 6,
};

enum IKW3 {
    SETTINGS_CUP_SCROLLING = 0,
    SETTINGS_TRIPLE_BANANAS = 1,
    SETTINGS_NO_IDLE_DC = 2,
    SETTINGS_CPU_RUBBERBANDING = 3,
    SETTINGS_CPU_DIFFICULTY = 4,
    SETTINGS_POSITION_TRACKER = 5,

    SETTINGS_FONT = 0 + 6,
    SETTINGS_WAITING_MUSIC = 1 + 6,
    SETTINGS_MEGA_FOV = 2 + 6,
    SETTINGS_COLORED_MINIMAPS = 3 + 6,
    SETTINGS_FINISH_TIMES = 4 + 6,
};

enum IKW4 {
    SETTINGS_REMOVE_LUMA = 0,
    SETTINGS_RACE_COUNT_MOD = 1,
    SETTINGS_NEW_ITEMS = 2,
    SETTINGS_AUTO_ACCELERATION = 3,
    SETTINGS_LIGHTNING_FLASH = 4,
    SETTINGS_QUIT_CONFIRMATION = 5,

    SETTINGS_MILLISECONDS_MODE = 0 + 6,
    SETTINGS_MII_CAMERAS = 1 + 6,
    SETTINGS_BULLET_MODEL = 2 + 6,
    SETTINGS_TRANSMISSION = 3 + 6,
    SETTINGS_ITEM_BOXES_ON_MINIMAP = 4 + 6,
};

enum IKW5 {
    SETTINGS_OTHERS_MEGA = 0,
    SETTINGS_OTHERS_STAR = 1,
    SETTINGS_MULTI_CHANNEL = 2,
    SETTINGS_ENGINE_SOUNDS = 3,
    SETTINGS_MEGA_MUSIC = 4,
    SETTINGS_STAR_MUSIC = 5,

    SETTINGS_LAP_COUNT = 0 + 6,
    SETTINGS_BRSTM_VOLUME = 1 + 6,
    SETTINGS_CHOMP_LAUNCH = 2 + 6,
    SETTINGS_THWOMP_SOUND = 3 + 6,
    SETTINGS_SQUISH_EFFECT = 4 + 6,
};

enum IKW6 {
    SETTINGS_BABY_MARIO = 0,
    SETTINGS_BABY_LUIGI = 1,
    SETTINGS_BABY_PEACH = 2,
    SETTINGS_BABY_DAISY = 3,
    SETTINGS_TOAD = 4,
    SETTINGS_TOADETTE = 5,

    SETTINGS_PEACH = 0 + 6,
    SETTINGS_LUIGI = 1 + 6,
    SETTINGS_MARIO = 2 + 6,
    SETTINGS_DRY_BONES = 3 + 6,
    SETTINGS_KOOPA_TROOPA = 4 + 6
};

enum IKW7 {
    SETTINGS_DAISY = 0,
    SETTINGS_YOSHI = 1,
    SETTINGS_BIRDO = 2,
    SETTINGS_DIDDY_KONG = 3,
    SETTINGS_BOWSER_JR = 4,
    SETTINGS_WARIO = 5,

    SETTINGS_ROSALINA = 0 + 6,
    SETTINGS_KING_BOO = 1 + 6,
    SETTINGS_BOWSER = 2 + 6,
    SETTINGS_DONKEY_KONG = 3 + 6,
    SETTINGS_WALUIGI = 4 + 6,
};

enum IKW8 {
    SETTINGS_FUNKY_KONG = 0,
    SETTINGS_DRY_BOWSER = 1,
    SETTINGDEBUG_SCROLL_KMP = 2,
    SETTINGS_TRACK_MANIA = 3,
    SETTINGS_TURN_IN_AIR = 4,
    SETTINGS_COMPATIBILITY_MODE = 5,

    SETTINGS_ALPHA = 0 + 6,
    SETTINGS_BLUE = 1 + 6,
    SETTINGS_GREEN = 2 + 6,
    SETTINGS_RED = 3 + 6,
    SETTINGS_COLORS = 4 + 6,
};

//MENU SETTINGS
enum MenuSettingFastMenus {
    MENUSETTING_FASTMENUS_DISABLED = 0x0,
    MENUSETTING_FASTMENUS_FASTER = 0x1,
    MENUSETTING_FASTMENUS_ENABLED = 0x2
};

enum MenuSettingLayout {
    MENUSETTING_LAYOUT_ALPHABETICAL = 0x0,
    MENUSETTING_LAYOUT_DEFAULT = 0x1
};

enum MenuSettingMusic {
    MENUSETTING_MUSIC_DEFAULT = 0x0,
    MENUSETTING_MUSIC_DISABLE_ALL = 0x1,
    MENUSETTING_MUSIC_DISABLE_RACE = 0x2
};

enum MenuSettingBoot {
    MENUSETTING_BOOT_DISABLED,
    MENUSETTING_BOOT_L1,
    MENUSETTING_BOOT_L2,
    MENUSETTING_BOOT_L3,
    MENUSETTING_BOOT_L4
};

//RACE SETTINGS
enum RaceSettingMII {
    RACESETTING_MII_DISABLED = 0x0,
    RACESETTING_MII_ENABLED = 0x1
};

enum RaceSettingSPEEDUP {
    RACESETTING_SPEEDUP_DISABLED = 0x0,
    RACESETTING_SPEEDUP_ENABLED = 0x1
};

enum RaceSettingBATTLE {
    RACESETTING_BATTLE_GLITCH_DISABLED = 0x0,
    RACESETTING_BATTLE_GLITCH_ENABLED = 0x1,
    RACESETTING_BATTLE_GLITCH_NONE = 0x2
};

enum RaceSettingBLUES {
    RACESETTING_DRAGGABLE_BLUES_DISABLED = 0x0,
    RACESETTING_DRAGGABLE_BLUES_ENABLED = 0x1
};

enum RaceSettingSOM {
    RACESETTING_SOM_LEFT = 0x0,
    RACESETTING_SOM_RIGHT = 0x1,
    RACESETTING_SOM_DISABLED = 0x2
};

enum RaceSettingSOMDigits {
    HOSTSETTING_SOM_DIGITS_0,
    HOSTSETTING_SOM_DIGITS_1,
    HOSTSETTING_SOM_DIGITS_2,
    HOSTSETTING_SOM_DIGITS_3,
};

//HOST SETTINGS
enum HostSettingHAW {
    HOSTSETTING_HOSTWINS_DISABLED,
    HOSTSETTING_HOSTWINS_ENABLED
};

enum HostSettingHostCC {
    HOSTSETTING_CC_NORMAL,
    HOSTSETTING_CC_150,
    HOSTSETTING_CC_100,
    HOSTSETTING_CC_MIRROR
};

enum HostSettingMiiHeads {
    HOSTSETTING_ALLOW_MIIHEADS_ENABLED,
    HOSTSETTING_ALLOW_MIIHEADS_DISABLED
};

enum HostSettingGPRACES {
    HOSTSETTING_GP_RACES_4,
    HOSTSETTING_GP_RACES_8,
    HOSTSETTING_GP_RACES_12,
    HOSTSETTING_GP_RACES_24,
    HOSTSETTING_GP_RACES_32,
    HOSTSETTING_GP_RACES_64,
    HOSTSETTING_GP_RACES_2,
    //space for a 7th setting is available
};

//OTTSETTINGS
enum OTTSettingOnline {
    OTTSETTING_ONLINE_DISABLED,
    OTTSETTING_ONLINE_NORMAL,
    OTTSETTING_ONLINE_FEATHER,
};

enum OTTSettingOffline {
    OTTSETTING_OFFLINE_DISABLED,
    OTTSETTING_OFFLINE_NORMAL,
    OTTSETTING_OFFLINE_FEATHER,
};

enum OTTSettingCombo {
    OTTSETTING_COMBO_DISABLED,
    OTTSETTING_COMBO_ENABLED
};

enum OTTSettingUMTs {
    OTTSETTING_UMTS_DISABLED,
    OTTSETTING_UMTS_ENABLED
};

//KOSETTINGS
enum KOSettingEnabled {
    KOSETTING_DISABLED,
    KOSETTING_ENABLED,
};
enum KOSettingFINAL {
    KOSETTING_FINAL_DISABLED,
    KOSETTING_FINAL_ALWAYS,
};
enum KOSettingKOPerRace {
    KOSETTING_KOPERRACE_1,
    KOSETTING_KOPERRACE_2,
    KOSETTING_KOPERRACE_3,
    KOSETTING_KOPERRACE_4
};

enum KOSettingRacesPerKO {
    KOSETTING_RACESPERKO_1,
    KOSETTING_RACESPERKO_2,
    KOSETTING_RACESPERKO_3,
    KOSETTING_RACESPERKO_4
};
//KOSETTINGS


//IKW Pages 1
enum AccurateItems {
    ACCURATE_ITEMS_OFF = 0x0,
    ACCURATE_ITMES_ON = 0x1
};

enum BlurFixes {
    BLUR_FIXES_OFF = 0x0,
    BLUR_FIXES_ON = 0x1
};

enum ThirtyFPS {
    THIRTY_FPS_OFF = 0x0,
    THIRTY_FPS_ON = 0x1
};

enum StarAnimation {
    STAR_ANIMATION_OFF = 0x0,
    STAR_ANIMATION_ON = 0x1
};

enum EffectsOnMinimap {
    EFFECTS_ON_MINIMAP_OFF = 0x0,
    EFFECTS_ON_MINIMAP_ON = 0x1
};

enum MenuSounds {
    MENU_SOUNDS_ON = 0x0,
    MENU_SOUNDS_OFF = 0x1
};

enum GameModes {
    GAME_MODE_DEFAULT,
    GAME_MODE_BOB_OMB_BLAST,
    GAME_MODE_INFINITE_ACCELERATION,
    GAME_MODE_BANANA_SLIP,
    GAME_MODE_RANDOM_ITEMS,
    GAME_MODE_UNFAIR_ITEMS,
    GAME_MODE_BLUE_SHELL_MADNESS,
    GAME_MODE_MUSHROOM_DASH,
    GAME_MODE_BUMPER_KARTS,
    GAME_MODE_RANDOM_EFFECTS,
    GAME_MODE_ITEM_RAIN,
    GAME_MODE_SHELL_BREAK,
    GAME_MODE_CRAZY_ITEMS,
    GAME_MODE_RIIBALANCED,
    GAME_MODE_ULTRAS_ENABLED
};

enum OpponentPrediction {
    OPPONENT_PREDICTION_DISABLED = 0x0,
    OPPONENT_PREDICTION_ENABLED = 0x1
};

enum PerformanceBar {
    PERFORMANCE_BAR_DISABLED = 0x0,
    PERFORMANCE_BAR_ENABLED = 0x1
};

enum BrakeDrifting {
    BRAKE_DRIFTING_ENABLED = 0x0,
    BRAKE_DRIFTING_DISABLED = 0x1
};

enum FirstPerson {
    FIRST_PERSON_DISABLED = 0x0,
    FIRST_PERSON_ENABLED = 0x1
};

//IKW Pages 2
enum ColoredNametags {
    COLORED_NAMETAGS_DISABLED = 0x0,
    COLORED_NAMETAGS_ENABLED = 0x1
};

enum DefaultCharacter {
    FAVORITE_CHAR_DISABLED = 0x0,
    FAVORITE_CHAR_ENABLED = 0x1
};

enum PackMusic {
    PACK_MUSIC_DISABLED = 0x0,
    PACK_MUSIC_ENABLED = 0x1
};

enum AutoTrailItems {
    ITEMS_AUTO_TRAIL_DISABLED = 0x0,
    ITEMS_AUTO_TRAIL_ENABLED = 0x1
};

enum InputViewer {
    INPUT_VIEWER_OFF = 0x0,
    INPUT_VIEWER_ON = 0x1
};

enum SilentControllerChange {
    SILENT_CONTROLLER_CHANGE_DISABLED = 0x0,
    SILENT_CONTROLLER_CHANGE_ENABLED = 0x1
};

enum RaceTheme {
    RACE_DEFAULT,
    RACE_MK8,
    RACE_SMK,
    RACE_MKDD,
    RACE_SMO,
    RACE_DX
};

enum MenuTheme {
    MENU_DEFAULT,
    MENU_MK8,
    MENU_SMK,
    MENU_MKDD,
    MENU_SMO,
    MENU_DX
};

enum MuteCharacters {
    MUTE_CHARACTERS_DISABLED,
    MUTE_CHARACTERS_ENABLED
};

enum KillLakitu {
    KILL_LAKITU_DISABLED,
    KILL_LAKITU_ENABLED
};

enum ItemsOnMinimap {
    ITEMS_ON_MINIMAP_DISABLED,
    ITEMS_ON_MINIMAP_ENABLED
};

//IKW Pages 3
enum CupsScrolling {
    CUPS_2 = 0x0,
    CUPS_4 = 0x1,
    CUPS_6 = 0x2,
    CUPS_8 = 0x3
};

enum TripleBananas {
    TRIPLE_BANANAS_TRAIL = 0x0,
    TRIPLE_BANANAS_ROTATE = 0x1
};

enum NoIdleDC {
    IDLE_DC_ENABLED = 0x0,
    IDLE_DC_DISABLED = 0x1
};

enum CPURubberbanding {
    RUBBERBANDING_DISABLED = 0x0,
    RUBBERBANDING_ENABLED = 0x1
};

enum CPUDifficulty {
    DIFFICULTY_NORMAL = 0x0,
    DIFFICULTY_HARD = 0x1,
    DIFFICULTY_EXTREME = 0x2
};

enum HidePositionTracker {
    POSITION_TRACKER_ENABLED = 0x0,
    POSITION_TRACKER_DISABLED = 0x1
};

enum Font {
    FONT_DEFAULT,
    FONT_NSMBU,
    FONT_SUPER_MARIO_MAKER,
    FONT_CRASH_BANDICOOT,
    FONT_JUST_DANCE,
    FONT_MK8,
    FONT_SPLATOON,
    FONT_MARIO,
    FONT_SPLATOON1
};

enum WaitingMusic {
    WAITING_MUSIC_NORMAL = 0x0,
    WAITING_MUSIC_COURSE = 0x1
};

enum BetterMegaFOV {
    MEGA_FOV_DISABLED = 0x0,
    MEGA_FOV_ENABLED = 0x1
};

enum ColoredMinimaps {
    COLORED_MINIMAPS_DISABLED = 0x0,
    COLORED_MINIMAPS_ENABLED = 0x1
};

enum ShowFinishTimes {
    FINISH_TIMES_DISABLED = 0x0,
    FINISH_TIMES_ENABLED = 0x1
};

//IKW Pages 4
enum RemoveLuma {
    REMOVE_LUMA_DISABLED = 0x0,
    REMOVE_LUMA_ENABLED = 0x1
};

enum RaceCountModifier {
    RACE_COUNT_MODIFIER_DISABLED = 0x0,
    RACE_COUNT_MODIFIER_ENABLED = 0x1
};

enum NewItems {
    NEW_ITEMS_DISABLED = 0x0,
    NEW_ITEMS_ENABLED = 0x1
};

enum AutoAcceleration {
    AUTO_ACCELERATE_DISABLED = 0x0,
    AUTO_ACCELERATE_ENABLED = 0x1
};

enum LightningFlash {
    LIGHTNING_FLASH_ENABLED = 0x0,
    LIGHTNING_FLASH_DISABLED = 0x1
};

enum QuitConfirmation {
    QUIT_CONFIRMATION_DISABLED = 0x0,
    QUIT_CONFIRMATION_ENABLED = 0x1
};

enum MillisecondsModifier {
    MILLISECONDS_NORMAL,
    MILLISECONDS_ITEMS,
    MILLISECONDS_SHOCK,
    MILLISECONDS_CRUSH
};

enum MiiCamera {
    MII_STARE_ENABLED,
    MII_STARE_DISABLED
};

enum NoBulletModel {
    BULLET_MODEL_ENABLED,
    BULLET_MODEL_DISABLED
};

enum Transmission {
    TRANSMISSION_NORMAL,
    TRANSMISSION_INSIDE,
    TRANSMISSION_OUTSIDE
};

enum ItemBoxesOnMinimap {
    ITEM_BOXES_MINIMAP_DISABLED,
    ITEM_BOXES_MINIMAP_ENABLED
};

//IKW Pages 6
enum OthersMega {
    OTHERS_MEGA_MUSIC_ENABLED = 0x0,
    OTHERS_MEGA_MUSIC_DISABLED = 0x1
};

enum OthersStar {
    OTHERS_STAR_MUSIC_ENABLED = 0x0,
    OTHERS_STAR_MUSIC_DISABLED = 0x1
};

enum MultiChannel {
    MULTI_CHANNEL_DISABLED = 0x0,
    MULTI_CHANNEL_ENABLED = 0x1
};

enum EngineSounds {
    ENGINE_SOUNDS_ENABLED = 0x0,
    ENGINE_SOUNDS_DISABLED = 0x1
};

enum MegaMusic {
    MEGA_MUSIC_ENABLED = 0x0,
    MEGA_MUSIC_DISABLED = 0x1
};

enum StarMusic {
    STAR_MUSIC_ENABLED = 0x0,
    STAR_MUSIC_DISABLED = 0x1
};

enum HideFriendCode {
    LAP_COUNT_NORMAL = 0x0,
    LAP_COUNT_1 = 0x1,
    LAP_COUNT_2 = 0x2,
    LAP_COUNT_3 = 0x3,
    LAP_COUNT_4 = 0x4,
    LAP_COUNT_5 = 0x5,
    LAP_COUNT_6 = 0x6,
    LAP_COUNT_7 = 0x7,
    LAP_COUNT_8 = 0x8,
};

enum VolumeBRSTM {
    VOLUME_100,
    VOLUME_90,
    VOLUME_80,
    VOLUME_70,
    VOLUME_60,
    VOLUME_50
};

enum ChompLaunch {
    CHOMP_LAUNCH_ENABLED,
    CHOMP_LAUNCH_DISABLED
};

enum ThwompDamage {
    THWOMP_DAMAGE_ENABLED,
    THWOMP_DAMAGE_DISABLED
};

enum SquishEffect {
    SQUISH_ENABLED,
    SQUISH_DISABLED
};

//IKW Pages 7
enum BabyMarioLayers {
    BABY_MARIO_DEFAULT = 0x0,
    BABY_MARIO_1 = 0x1,
    BABY_MARIO_2 = 0x2
};

enum BabyLuigiLayers {
    BABY_LUIGI_DEFAULT = 0x0,
    BABY_LUIGI_1 = 0x1,
    BABY_LUIGI_2 = 0x2
};

enum BabyPeachLayers {
    BABY_PEACH_DEFAULT = 0x0,
    BABY_PEACH_1 = 0x1,
    BABY_PEACH_2 = 0x2
};

enum BabyDaisyLayers {
    BABY_DAISY_DEFAULT = 0x0,
    BABY_DAISY_1 = 0x1,
    BABY_DAISY_2 = 0x2
};

enum ToadLayers {
    TOAD_DEFAULT = 0x0,
    TOAD_1 = 0x1,
    TOAD_2 = 0x2
};

enum ToadetteLayers {
    TOADETTE_DEFAULT = 0x0,
    TOADETTE_1 = 0x1,
    TOADETTE_2 = 0x2
};

enum PeachLayers {
    PEACH_DEFAULT = 0x0,
    PEACH_1 = 0x1,
    PEACH_2 = 0x2
};

enum LuigiLayers {
    LUIGI_DEFAULT = 0x0,
    LUIGI_1 = 0x1,
    LUIGI_2 = 0x2
};

enum MarioLayers {
    MARIO_DEFAULT = 0x0,
    MARIO_1 = 0x1,
    MARIO_2 = 0x2
};

enum DryBonesLayers {
    DRY_BONES_DEFAULT = 0x0,
    DRY_BONES_1 = 0x1,
    DRY_BONES_2 = 0x2
};

enum KoopaTroopaLayers {
    KOOPA_KOOPA_DEFAULT = 0x0,
    KOOPA_TROOPA_1 = 0x1,
    KOOPA_TROOPA_2 = 0x2
};

//IKW Page 8
enum DaisyLayers {
    DAISY_DEFAULT_DEFAULT = 0x0,
    DAISY_1 = 0x1,
    DAISY_2 = 0x2
};

enum YoshiLayers {
    YOSHI_DEFAULT = 0x0,
    YOSHI_1 = 0x1,
    YOSHI_2 = 0x2
};

enum BirdoLayers {
    BIRDO_DEFAULT = 0x0,
    BIRDO_1 = 0x1,
    BIRDO_2 = 0x2
};

enum DiddyKongLayers {
    DIDDY_KONG_DEFAULT = 0x0,
    DIDDY_KONG_1 = 0x1,
    DIDDY_KONG_2 = 0x2
};

enum BowserJrLayers {
    BOWSER_JR_DEFAULT = 0x0,
    BOWSER_JR_1 = 0x1,
    BOWSER_JR_2 = 0x2
};

enum WarioLayers {
    WARIO_DEFAULT = 0x0,
    WARIO_1 = 0x1,
    WARIO_2 = 0x2
};

enum RosalinaLayers {
    ROSALINA_DEFAULT = 0x0,
    ROSALINA_1 = 0x1,
    ROSALINA_2 = 0x2
};

enum KingBooLayers {
    KING_BOO_DEFAULT = 0x0,
    KING_BOO_1 = 0x1,
    KING_BOO_2 = 0x2
};

enum BowserLayers {
    BOWSER_DEFAULT = 0x0,
    BOWSER_1 = 0x1,
    BOWSER_2 = 0x2
};

enum DonkeyKongLayers {
    DK_DEFAULT = 0x0,
    DK_1 = 0x1,
    DK_2 = 0x2
};

enum WaluigiLayers {
    WALUIGI_DEFAULT = 0x0,
    WALUIGI_1 = 0x1,
    WALUIGI_2 = 0x2
};

//IKW Pages 9
enum FunkyKongLayers {
    FUNKY_KONG_DEFAULT = 0x0,
    FUNKY_KONG_1 = 0x1,
    FUNKY_KONG_2 = 0x2
};

enum DryBowserLayers {
    DRY_BOWSER_DEFAULT = 0x0,
    DRY_BOWSER_1 = 0x1,
    DRY_BOWSER_2 = 0x2
};

enum DebugSettingKMP {
    DEBUGSETTING_KMP_DISABLED = 0x0,
    DEBUGSETTING_KMP_KEYCPS = 0x1,
    DEBUGSETTING_KMP_ITPTS = 0x2
};

enum TrackManiaCam {
    CAM_DISABLED = 0x0,
    CAM_ENABLED = 0x1
};

enum TurnInAir {
    TURN_IN_AIR_ENABLED = 0x0,
    TURN_IN_AIR_DISABLED = 0x1
};

enum CompatibilityMode {
    COMPATIBILITY_MODE_DISABLED = 0x0,
    COMPATIBILITY_MODE_ENABLED = 0x1
};

enum AlphaColor {
    ALPHA_0F = 0x0F,
    ALPHA_1F = 0x1F,
    ALPHA_2F = 0x2F,
    ALPHA_3F = 0x3F,
    ALPHA_4F = 0x4F,
    ALPHA_5F = 0x5F,
    ALPHA_6F = 0x6F,
    ALPHA_7F = 0x7F,
    ALPHA_8F = 0x8F,
    ALPHA_9F = 0x9F,
    ALPHA_AF = 0xAF,
    ALPHA_BF = 0xBF,
    ALPHA_CF = 0xCF,
    ALPHA_DF = 0xDF,
    ALPHA_EF = 0xEF,
    ALPHA_FF = 0xFF,
};

enum BlueColor {
    BLUE_0F = 0x0F,
    BLUE_1F = 0x1F,
    BLUE_2F = 0x2F,
    BLUE_3F = 0x3F,
    BLUE_4F = 0x4F,
    BLUE_5F = 0x5F,
    BLUE_6F = 0x6F,
    BLUE_7F = 0x7F,
    BLUE_8F = 0x8F,
    BLUE_9F = 0x9F,
    BLUE_AF = 0xAF,
    BLUE_BF = 0xBF,
    BLUE_CF = 0xCF,
    BLUE_DF = 0xDF,
    BLUE_EF = 0xEF,
    BLUE_FF = 0xFF,
};

enum GreenColor {
    GREEN_0F = 0x0F,
    GREEN_1F = 0x1F,
    GREEN_2F = 0x2F,
    GREEN_3F = 0x3F,
    GREEN_4F = 0x4F,
    GREEN_5F = 0x5F,
    GREEN_6F = 0x6F,
    GREEN_7F = 0x7F,
    GREEN_8F = 0x8F,
    GREEN_9F = 0x9F,
    GREEN_AF = 0xAF,
    GREEN_BF = 0xBF,
    GREEN_CF = 0xCF,
    GREEN_DF = 0xDF,
    GREEN_EF = 0xEF,
    GREEN_FF = 0xFF,
};

enum RedColor {
    RED_0F = 0x0F,
    RED_1F = 0x1F,
    RED_2F = 0x2F,
    RED_3F = 0x3F,
    RED_4F = 0x4F,
    RED_5F = 0x5F,
    RED_6F = 0x6F,
    RED_7F = 0x7F,
    RED_8F = 0x8F,
    RED_9F = 0x9F,
    RED_AF = 0xAF,
    RED_BF = 0xBF,
    RED_CF = 0xCF,
    RED_DF = 0xDF,
    RED_EF = 0xEF,
    RED_FF = 0xFF,
};

enum ColorsToggle {
    COLORS_IKW = 0x0,
    COLORS_DEFAULT = 0x1,
    COLORS_CUSTOM = 0x2
};


}//namespace Pulsar



#endif