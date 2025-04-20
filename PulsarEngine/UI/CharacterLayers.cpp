#include <kamek.hpp>
#include <Settings/SettingsParam.hpp>
#include <MKVN.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>

namespace Pulsar{
namespace Settings{

void LayersMario(){
    U32_MARIO = 0x6D720000;
    U8_MARIO = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_MARIO) == MARIO_1){
    U32_MARIO = 0x676E0000;
    U8_MARIO = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_MARIO) == MARIO_2){
    U32_MARIO = 0x736E0000;
    U8_MARIO = 0x65;
    }
}
static PageLoadHook CHARACTERMARIO(LayersMario);

void LayersToadette(){
    U32_TOADETTE = 0x6B6B0000;
    U8_TOADETTE = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_TOADETTE) == TOADETTE_1){
    U32_TOADETTE = 0x746D0000;
    U8_TOADETTE = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_TOADETTE) == TOADETTE_2){
    U32_TOADETTE = 0x74660000;
    U8_TOADETTE = 0x65;
    }
}
static PageLoadHook CHARACTERTOADETTE(LayersToadette);

void LayersToad(){
    U32_TOAD = 0x6B6F0000;
    U8_TOAD = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_TOAD) == TOAD_1){
    U32_TOAD = 0x74770000;
    U8_TOAD = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_TOAD) == TOAD_2){
    U32_TOAD = 0x6D630000;
    U8_TOAD = 0x65;
    }
}
static PageLoadHook CHARACTERTOAD(LayersToad);

void LayersWario(){
    U32_WARIO = 0x77720000;
    U8_WARIO = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_WARIO) == WARIO_1){
    U32_WARIO = 0x63630000;
    U8_WARIO = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_WARIO) == WARIO_2){
    U32_WARIO = 0x63710000;
    U8_WARIO = 0x65;
    }
}
static PageLoadHook CHARACTERWARIO(LayersWario);

void LayersBabyLuigi(){
    U32_BABY_LUIGI = 0x626C6700;
    U8_BABY_LUIGI = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_LUIGI) == BABY_LUIGI_1){
    U32_BABY_LUIGI = 0x65676700;
    U8_BABY_LUIGI = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_LUIGI) == BABY_LUIGI_2){
    U32_BABY_LUIGI = 0x73676700;
    U8_BABY_LUIGI = 0x65;
    }
}
static PageLoadHook CHARACTERBABYLUIGI(LayersBabyLuigi);

void LayersWaluigi(){
    U32_WALUIGI = 0x776C0000;
    U8_WALUIGI = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_WALUIGI) == WALUIGI_1){
    U32_WALUIGI = 0x64670000;
    U8_WALUIGI = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_WALUIGI) == WALUIGI_2){
    U32_WALUIGI = 0x77670000;
    U8_WALUIGI = 0x65;
    }
}
static PageLoadHook CHARACTERWALUIGI(LayersWaluigi);

void LayersDK(){
    U32_DONKEY_KONG = 0x646B0000;
    U8_DONKEY_KONG = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DONKEY_KONG) == DK_1){
    U32_DONKEY_KONG = 0x706E0000;
    U8_DONKEY_KONG = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DONKEY_KONG) == DK_2){
    U32_DONKEY_KONG = 0x736C0000;
    U8_DONKEY_KONG = 0x65;
    }
}
static PageLoadHook CHARACTERDK(LayersDK);

void LayersDryBones(){
    U32_DRY_BONES = 0x6B610000;
    U8_DRY_BONES = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_DRY_BONES) == DRY_BONES_1){
    U32_DRY_BONES = 0x62640000;
    U8_DRY_BONES = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_DRY_BONES) == DRY_BONES_2){
    U32_DRY_BONES = 0x667A0000;
    U8_DRY_BONES = 0x65;
    }
}
static PageLoadHook CHARACTERDryBones(LayersDryBones);

void LayersDiddyKong(){
    U32_DIDDY_KONG = 0x64640000;
    U8_DIDDY_KONG = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DIDDY_KONG) == DIDDY_KONG_1){
    U32_DIDDY_KONG = 0x64780000;
    U8_DIDDY_KONG = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DIDDY_KONG) == DIDDY_KONG_2){
    U32_DIDDY_KONG = 0x63620000;
    U8_DIDDY_KONG = 0x65;
    }
}
static PageLoadHook CHARACTERDIDDYKONG(LayersDiddyKong);

void LayersBabyPeach(){
    U32_BABY_PEACH = 0x62706300;
    U8_BABY_PEACH = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_PEACH) == BABY_PEACH_1){
    U32_BABY_PEACH = 0x73706300;
    U8_BABY_PEACH = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_PEACH) == BABY_PEACH_2){
    U32_BABY_PEACH = 0x67626300;
    U8_BABY_PEACH = 0x65;
    }
}
static PageLoadHook CHARACTERBABYPEACH(LayersBabyPeach);

void LayersRosalina(){
    U32_ROSALINA = 0x72730000;
    U32_ROSALINA_MENU = 0x72735F6D;
    U8_ROSALINA = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_ROSALINA) == ROSALINA_1){
    U32_ROSALINA = 0x68710000;
    U32_ROSALINA_MENU = 0x68715F6D;
    U8_ROSALINA = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_ROSALINA) == ROSALINA_2){
    U32_ROSALINA = 0x706C0000;
    U32_ROSALINA_MENU = 0x706C5F6D;
    U8_ROSALINA = 0x65;
    }
}
static PageLoadHook CHARACTERROSALINA(LayersRosalina);

void LayersYoshi(){
    U32_YOSHI = 0x79730000;
    U8_YOSHI = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_YOSHI) == YOSHI_1){
    U32_YOSHI = 0x70700000;
    U8_YOSHI = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_YOSHI) == YOSHI_2){
    U32_YOSHI = 0x70790000;
    U8_YOSHI = 0x65;
    }
}
static PageLoadHook CHARACTERYOSHI(LayersYoshi);

void LayersBowserJr(){
    U32_BOWSER_JR = 0x6A720000;
    U8_BOWSER_JR = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BOWSER_JR) == BOWSER_JR_1){
    U32_BOWSER_JR = 0x68620000;
    U8_BOWSER_JR = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BOWSER_JR) == BOWSER_JR_2){
    U32_BOWSER_JR = 0x6B6D0000;
    U8_BOWSER_JR = 0x65;
    }
}
static PageLoadHook CHARACTERBOWSERJR(LayersBowserJr);

void LayersBowser(){
    U32_BOWSER = 0x6B700000;
    U8_BOWSER = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BOWSER) == BOWSER_1){
    U32_BOWSER = 0x77700000;
    U8_BOWSER = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BOWSER) == BOWSER_2){
    U32_BOWSER = 0x6B620000;
    U8_BOWSER = 0x65;
    }
}
static PageLoadHook CHARACTERBOWSER(LayersBowser);

void LayersKingBoo(){
    U32_KING_BOO = 0x6B740000;
    U8_KING_BOO = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_KING_BOO) == KING_BOO_1){
    U32_KING_BOO = 0x6D690000;
    U8_KING_BOO = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_KING_BOO) == KING_BOO_2){
    U32_KING_BOO = 0x726F0000;
    U8_KING_BOO = 0x65;
    }
}
static PageLoadHook CHARACTERKINGBOO(LayersKingBoo);

void LayersBirdo(){
    U32_BIRDO = 0x63610000;
    U8_BIRDO = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BIRDO) == BIRDO_1){
    U32_BIRDO = 0x6D6D0000;
    U8_BIRDO = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_BIRDO) == BIRDO_2){
    U32_BIRDO = 0x626C0000;
    U8_BIRDO = 0x65;
    }
}
static PageLoadHook CHARACTERBIRDO(LayersBirdo);

void LayersDaisy(){
    U32_DAISY = 0x64730000;
    U32_DAISY_MENU = 0x64735F6D;
    U8_DAISY = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DAISY) == DAISY_1){
    U32_DAISY = 0x646D0000;
    U32_DAISY_MENU = 0x646D5F6D;
    U8_DAISY = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW8, SETTINGS_DAISY) == DAISY_2){
    U32_DAISY = 0x73770000;
    U32_DAISY_MENU = 0x73775F6D;
    U8_DAISY = 0x65;
    }
}
static PageLoadHook CHARACTERDAISY(LayersDaisy);

void LayersDryBowser(){
    U32_DRY_BOWSER = 0x626B0000;
    U8_DRY_BOWSER = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9, SETTINGS_DRY_BOWSER) == DRY_BOWSER_1){
    U32_DRY_BOWSER = 0x6B720000;
    U8_DRY_BOWSER = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9, SETTINGS_DRY_BOWSER) == DRY_BOWSER_2){
    U32_DRY_BOWSER = 0x67640000;
    U8_DRY_BOWSER = 0x65;
    }
}
static PageLoadHook CHARACTERDRYBOWSER(LayersDryBowser);

void LayersFunkyKong(){
    U32_FUNKY_KONG = 0x666B0000;
    U8_FUNKY_KONG = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9, SETTINGS_FUNKY_KONG) == FUNKY_KONG_1){
    U32_FUNKY_KONG = 0x62700000;
    U8_FUNKY_KONG = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW9, SETTINGS_FUNKY_KONG) == FUNKY_KONG_2){
    U32_FUNKY_KONG = 0x64650000;
    U8_FUNKY_KONG = 0x65;
    }
}
static PageLoadHook CHARACTERFUNKYKONG(LayersFunkyKong);

void LayersBabyMario(){
    U32_BABY_MARIO = 0x626D7200;
    U8_BABY_MARIO = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_MARIO) == BABY_MARIO_1){
    U32_BABY_MARIO = 0x706B7200;
    U8_BABY_MARIO = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_MARIO) == BABY_MARIO_2){
    U32_BABY_MARIO = 0x6E6A7200;
    U8_BABY_MARIO = 0x65;
    }
}
static PageLoadHook CHARACTERBABYMARIO(LayersBabyMario);

void LayersLuigi(){
    U32_LUIGI = 0x6C670000;
    U8_LUIGI = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_LUIGI) == LUIGI_1){
    U32_LUIGI = 0x73760000;
    U8_LUIGI = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_LUIGI) == LUIGI_2){
    U32_LUIGI = 0x6E620000;
    U8_LUIGI = 0x65;
    }
}
static PageLoadHook CHARACTERLUIGI(LayersLuigi);

void LayersBabyDaisy(){
    U32_BABY_DAISY = 0x62647300;
    U8_BABY_DAISY = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_DAISY) == BABY_DAISY_1){
    U32_BABY_DAISY = 0x6D6D7300;
    U8_BABY_DAISY = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_BABY_DAISY) == BABY_DAISY_2){
    U32_BABY_DAISY = 0x6D6B7300;
    U8_BABY_DAISY = 0x65;
    }
}
static PageLoadHook CHARACTERBABYDAISY(LayersBabyDaisy);

void LayersKoopaTroopa(){
    U32_KOOPA_TROOPA = 0x6E6B0000;
    U8_KOOPA_TROOPA = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_KOOPA_TROOPA) == KOOPA_TROOPA_1){
    U32_KOOPA_TROOPA = 0x70740000;
    U8_KOOPA_TROOPA = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_KOOPA_TROOPA) == KOOPA_TROOPA_2){
    U32_KOOPA_TROOPA = 0x6C6B0000;
    U8_KOOPA_TROOPA = 0x65;
    }
}
static PageLoadHook CHARACTERKOOPATROOPA(LayersKoopaTroopa);

void LayersPeach(){
    U32_PEACH = 0x70630000;
    U32_PEACH_MENU = 0x70635F6D;
    U8_PEACH = 0x63;

    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_PEACH) == PEACH_1){
    U32_PEACH = 0x70690000;
    U32_PEACH_MENU = 0x70695F6D;
    U8_PEACH = 0x64;
    }
    if (Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW7, SETTINGS_PEACH) == PEACH_2){
    U32_PEACH = 0x73740000;
    U32_PEACH_MENU = 0x73745F6D;
    U8_PEACH = 0x65;
    }
}
static PageLoadHook CHARACTERPEACH(LayersPeach);

}
}