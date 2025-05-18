#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/SinglePlayer.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <MKVN.hpp>
//Implements 4 TT modes by splitting the "Time Trials" button


namespace Pulsar {
static void SetCC();
namespace UI {



void CorrectButtonCount(Pages::SinglePlayer* page) {
    const System* system = System::sInstance;
    const bool hasFeather = system->GetInfo().HasFeather();
    const bool has200cc = system->GetInfo().Has200cc();
    page->externControlCount = 21 + hasFeather + has200cc + (hasFeather && has200cc);
    new (page) Page;
}
kmCall(0x806266b8, CorrectButtonCount);
kmWrite32(0x806266d4, 0x60000000);

//kmWrite32(0x8084f080, 0x7F89E378); //get idx in r9
static void LoadCorrectBRCTR(PushButton& button, const char* folder, const char* ctr, const char* variant, u32 localPlayerField) {
    register int idx;
    asm(mr idx, r28;);
    Pages::SinglePlayer* page = button.parentGroup->GetParentPage<Pages::SinglePlayer>();
    const System* system = System::sInstance;

    u32 varId = 0;
    u32 count = page->externControlCount;
    if(count > 5 && (idx == 1 || idx > 3)) {
            ctr = "TingleTop";
            if(idx != 1) varId = idx - 3;
        char ttVariant[0x15];
        snprintf(ttVariant, 0x15, "PulTTFour_%d", varId);
        variant = ttVariant;

    }

    button.Load(folder, ctr, variant, localPlayerField, 0, false);
    page->curMovieCount = 0;
}
kmCall(0x8084f084, LoadCorrectBRCTR);


//kmWrite32(0x8084f08c, 0x60000000);
//kmWrite32(0x8084f094, 0x38030001);
//kmWrite32(0x8084f098, 0x60000000);

void OnButtonSelect(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const s32 id = button.buttonId;
    u32 count = page->externControlCount;
    if(count > 5 && (id == 1 || id > 3)) {

        u32 bmgId;
        if(id == count - 2) U32_MISSION_MODE_ENABLE = 0x00000001;
        else U32_MISSION_MODE_ENABLE = 0x00000000;
        if(id == count - 1) bmgId = BMG_SETTINGSBUTTON_BOTTOM;
        else if(id == count - 2) bmgId = BMG_MISSION_MODE_BOTTOM;
        else if(id == count - 3) bmgId = BMG_OTT_WW_BOTTOM;
        else if(id == count - 4) bmgId = BMG_BOOSTSTACKER_WW_BOTTOM;
        else if(id == count - 5) bmgId = BMG_COUNTDOWN_WW_BOTTOM;
        else if(id == count - 6) bmgId = BMG_SHELLBREAK_WW_BOTTOM;
        else if(id == count - 7) bmgId = BMG_ITEMRAIN_WW_BOTTOM;
        else if(id == count - 8) bmgId = BMG_ITEMRAMPAGE_WW_BOTTOM;
        else if(id == count - 9) bmgId = BMG_BUMPERKARTS_WW_BOTTOM;
        else if(id == count -10) bmgId = BMG_MUSHROOMDASH_WW_BOTTOM;
        else if(id == count -11) bmgId = BMG_BSMADNESS_WW_BOTTOM;
        else if(id == count -12) bmgId = BMG_UNFAIRITEMS_WW_BOTTOM;
        else if(id == count -13) bmgId = BMG_RANDOMITEMS_WW_BOTTOM;
        else if(id == count -14) bmgId = BMG_BANANASLIP_WW_BOTTOM;
        else if(id == count -15) bmgId = BMG_ACCELERATION_WW_BOTTOM;
        else if(id == count -16) bmgId = BMG_BOMBBLAST_WW_BOTTOM;
        else if(id == count -17) bmgId = BMG_FREE_ROAM_BOTTOM;
        else {
            button.buttonId = 1;
            page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
            button.buttonId = id;
            bmgId = BMG_TT_MODE_BOTTOM_SINGLE;
            const System* system = System::sInstance;
            if(id > 3) bmgId = bmgId + id - 3;
        }
        page->bottomText->SetMessage(bmgId);
    }
    else page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
}
kmWritePointer(0x808D9F64, &OnButtonSelect);

//Sets the ttMode based on which button was clicked
void OnButtonClick(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;
    if(page->externControlCount > 5 && id == page->externControlCount - 2) U16_MISSION_MODE_FIX = 0x0001;
    else U16_MISSION_MODE_FIX = 0x0000;
    U16_GAMEPLAYE = 0x0000;
    U16_GAMEPLAYD = 0x0000;
    U16_GAMEPLAYC = 0x0000;
    U16_GAMEPLAYC2 = 0x0000;
    U16_GAMEPLAYB = 0x0000;
    U16_GAMEPLAYA = 0x0000;
    U16_GAMEPLAY9 = 0x0000;
    U16_GAMEPLAY8 = 0x0000;
    U16_GAMEPLAY7 = 0x0000;
    U16_GAMEPLAY6 = 0x0000;
    U16_GAMEPLAY5 = 0x0000;
    U16_GAMEPLAY4 = 0x0000;
    U16_GAMEPLAY3 = 0x0000;
    U16_GAMEPLAY2 = 0x0000;
    U16_GAMEPLAY1 = 0x0000;
    U16_FREE_ROAM = 0x0000;
    if(page->externControlCount > 4 && id == page->externControlCount - 1) {
        ExpSection::GetSection()->GetPulPage<SettingsPanel>()->prevPageId = PAGE_SINGLE_PLAYER_MENU;
        page->nextPageId = static_cast<PageId>(SettingsPanel::id);
        page->EndStateAnimated(0, button.GetAnimationFrameSize());
        return;
    }
    if(page->externControlCount > 4 && id == page->externControlCount - 2 && U32_MISSION_MODE_ENABLE != 0x00000001) {
        page->nextPageId = PAGE_MISSION_LEVEL_SELECT_UNUSED;
        page->EndStateAnimated(0, button.GetAnimationFrameSize());
        return;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 3) {
        U16_GAMEPLAYE = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 4) {
        U16_GAMEPLAYD = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 5) {
        U16_GAMEPLAYC = 0x0001;
        U16_GAMEPLAYC2 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 6) {
        U16_GAMEPLAYB = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 7) {
        U16_GAMEPLAYA = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 8) {
        U16_GAMEPLAY9 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 9) {
        U16_GAMEPLAY8 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 10) {
        U16_GAMEPLAY7 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 11) {
        U16_GAMEPLAY6 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 12) {
        U16_GAMEPLAY5 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 13) {
        U16_GAMEPLAY4 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 14) {
        U16_GAMEPLAY3 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 15) {
        U16_GAMEPLAY2 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 16) {
        U16_GAMEPLAY1 = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 17) {
        U16_FREE_ROAM = 0x0001;
    }
    else if (page->externControlCount > 5 && id == page->externControlCount - 2) U8_OFFLINE_FLAG = 0x0;
    else if (page->externControlCount > 5 && id != page->externControlCount - 2 && Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_LAP_COUNT) != 0) U8_OFFLINE_FLAG = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_IKW6,SETTINGS_LAP_COUNT);

    if(id == 1 || id == 4 || id == 5 || id == 6 || id == 7) {
        U8_OFFLINE_FLAG = 0x0;
        button.buttonId = 1;
    }
    if(id > 6 && id != 7 && id != 23) button.buttonId = 2;
    U32_TEST_IDS = id;
    page->Pages::SinglePlayer::OnButtonClick(button, hudSlotId);
    button.buttonId = id;
    System* system = System::sInstance;
    if(id == 1 || id > 3) {
        TTMode mode = TTMODE_150;
        if(id > 3) mode = (TTMode)(id - 3);
        system->ttMode = mode;
        SetCC();
    }
}
kmWritePointer(0x808BBED0, OnButtonClick);
}//namespace UI

//Sets the CC (based on the mode) when retrying after setting a time, as racedata's CC is overwritten usually
static void SetCC() {
    const System* system = System::sInstance;
    EngineClass cc = CC_150;
    if(system->ttMode == TTMODE_200 || system->ttMode == TTMODE_200_FEATHER) cc = CC_100;
    Racedata::sInstance->menusScenario.settings.engineClass = cc;
}
kmBranch(0x805e1ef4, SetCC);
kmBranch(0x805e1d58, SetCC);

}//namespace Pulsar