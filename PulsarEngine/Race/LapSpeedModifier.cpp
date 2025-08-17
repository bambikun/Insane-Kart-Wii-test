#include <kamek.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>
#include <MarioKartWii/Kart/KartMovement.hpp>
#include <MarioKartWii/Item/Obj/ObjProperties.hpp>
#include <Race/200ccParams.hpp>
#include <PulsarSystem.hpp>
#include <MKVN.hpp>
#include <Settings/SettingsParam.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/Audio/RaceMgr.hpp>

namespace Pulsar {
namespace Race {
//Mostly a port of MrBean's version with better hooks and arguments documentation
RaceinfoPlayer* LoadCustomLapCount(RaceinfoPlayer* player, u8 id) {
    u8 lapCount = KMP::Manager::sInstance->stgiSection->holdersArray[0]->raw->lapCount;
    if (lapCount == 0) {
        lapCount = 3;
    }
    if (U8_OFFLINE_FLAG != 0x00 && U16_MISSION_MODE_FIX != 0x0001) {
        lapCount = U8_OFFLINE_FLAG;
    }
    Racedata::sInstance->racesScenario.settings.lapCount = lapCount;
    return new(player) RaceinfoPlayer(id, lapCount);
}
kmCall(0x805328d4, LoadCustomLapCount);

void LogMaxLocalCurrentLapOnPageLoad() {
    u8 lapCount = KMP::Manager::sInstance->stgiSection->holdersArray[0]->raw->lapCount;
    if (U8_OFFLINE_FLAG != 0x00) {
        lapCount = U8_OFFLINE_FLAG;
    }
    if(Raceinfo::sInstance == nullptr || Racedata::sInstance == nullptr) return;
    Audio::RaceMgr* raceAudioMgr = Audio::RaceMgr::sInstance;
    u32 maxLap = 0;
    for(int i = 0; i < Racedata::sInstance->racesScenario.playerCount; ++i) {
        const RacedataPlayer& rdp = Racedata::sInstance->racesScenario.players[i];
        if(rdp.realControllerChannel >= 0) {
            RaceinfoPlayer* player = Raceinfo::sInstance->players[i];
            if(player != nullptr && player->currentLap > maxLap) {
                maxLap = player->currentLap;
            }
            if(player != nullptr) U32_TEST_CURRENT_KCP = player->raceCompletionMax;
        }
    }
    if(maxLap == 0) {
        Pulsar::System::sInstance->currentLap = 0;
    }
    if(maxLap > Pulsar::System::sInstance->currentLap) {
        Pulsar::System::sInstance->currentLap = maxLap;
    }
    U32_MUSIC_SPEED = 1.0f;
    if(Pulsar::System::sInstance->currentLap > 1 && Pulsar::System::sInstance->currentLap < lapCount && (raceAudioMgr->raceState == 0x4 || raceAudioMgr->raceState == 0x6)) {
        if(U32_TEST_IDS == 0x809 || (U32_TEST_IDS >= 0xE9E && U32_TEST_IDS <= 0xEA5) || U32_TEST_IDS == 0x109E || U32_TEST_IDS == 0x116A || U32_TEST_IDS == 0x12CD) {
        U32_MUSIC_SPEED = (Pulsar::System::sInstance->currentLap * 0.02) + 1.0f - 0.02f;
        }
    }
}
static RaceFrameHook LOG_LAP(LogMaxLocalCurrentLapOnPageLoad);

void OfflineFlag() {
    const SectionId section = SectionMgr::sInstance->curSection->sectionId;
    if(section == SECTION_SINGLE_P_FROM_MENU || section == SECTION_SINGLE_P_TT_CHANGE_CHARA || section == SECTION_SINGLE_P_TT_CHANGE_COURSE || section == SECTION_SINGLE_P_VS_NEXT_RACE || section == SECTION_LOCAL_MULTIPLAYER) {
        U8_OFFLINE_FLAG = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_RACE2,SETTINGS_LAP_COUNT);
    }
    if(section == SECTION_MAIN_MENU_FROM_BOOT || section == SECTION_MAIN_MENU_FROM_RESET || section == SECTION_MAIN_MENU_FROM_MENU || section == SECTION_MAIN_MENU_FROM_NEW_LICENSE || section == SECTION_MAIN_MENU_FROM_LICENSE || TTS_CHECK == 0x00000001) {
        U8_OFFLINE_FLAG = 0x00;
    }
    if(section == SECTION_P1_WIFI_VS || section == SECTION_P2_WIFI_VS) {
        if(U8_OFFLINE_FLAG != 0x00) {
            U8_OFFLINE_FLAG = 0x09;
            Pulsar::Debug::FatalError("Error 99");
    }
}
}
static PageLoadHook OFFLINE(OfflineFlag);

//kmWrite32(0x80723d64, 0x7FA4EB78);
void DisplayCorrectLap(AnmTexPatHolder* texPat) { //This Anm is held by a ModelDirector in a Lakitu::Player
    register u32 maxLap;
    asm(mr maxLap, r29;);
    texPat->UpdateRateAndSetFrame((float)(maxLap - 2));
    return;
}
kmCall(0x80723d70, DisplayCorrectLap);


//kmWrite32(0x808b5cd8, 0x3F800000); //change 100cc speed ratio to 1.0    
Kart::Stats* ApplySpeedModifier(KartId kartId, CharacterId characterId) {
    union SpeedModConv {
        float speedMod;
        u32 kmpValue;
    };

    Kart::Stats* stats = Kart::ComputeStats(kartId, characterId);
    SpeedModConv speedModConv;
    speedModConv.kmpValue = (KMP::Manager::sInstance->stgiSection->holdersArray[0]->raw->speedMod << 16);
    if(speedModConv.speedMod == 0.0f) speedModConv.speedMod = 1.0f;
    float factor = System::sInstance->IsContext(PULSAR_200) ? speedFactor : 1.0f;
    factor *= speedModConv.speedMod;

    Item::greenShellSpeed = 105.0f * factor;
    Item::redShellInitialSpeed = 75.0f * factor;
    Item::redShellSpeed = 130.0f * factor;
    Item::blueShellSpeed = 260.0f * factor;
    Item::blueShellMinimumDiveDistance = 640000.0f * factor;
    Item::blueShellHomingSpeed = 130.0f * factor;

    Kart::hardSpeedCap = 120.0f * factor;
    Kart::bulletSpeed = 145.0f * factor;
    Kart::starSpeed = 105.0f * factor;
    Kart::megaTCSpeed = 95.0f * factor;

    stats->baseSpeed *= factor;
    stats->standard_acceleration_as[0] *= factor;
    stats->standard_acceleration_as[1] *= factor;
    stats->standard_acceleration_as[2] *= factor;
    stats->standard_acceleration_as[3] *= factor;

    Kart::minDriftSpeedRatio = 0.55f * (factor > 1.0f ? (1.0f / factor) : 1.0f);
    Kart::unknown_70 = 70.0f * factor;
    Kart::regularBoostAccel = 3.0f * factor;

    return stats;
}
kmCall(0x8058f670, ApplySpeedModifier);

kmWrite32(0x805336B8, 0x60000000);
kmWrite32(0x80534350, 0x60000000);
kmWrite32(0x80534BBC, 0x60000000);
kmWrite32(0x80723D10, 0x281D0009);
kmWrite32(0x80723D40, 0x3BA00009);

kmWrite24(0x808AAA0C, 'PUL'); //time_number -> time_numPUL
}//namespace Race
}//namespace Pulsar