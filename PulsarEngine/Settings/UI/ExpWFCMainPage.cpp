#include <MarioKartWii/UI/Page/Other/GlobeSearch.hpp>
#include <MarioKartWii/RKSYS/RKSYSMgr.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <UI/UI.hpp>
#include <MKVN.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace UI {
//EXPANDED WFC, keeping WW button and just hiding it in case it is ever needed...

kmWrite32(0x8064b984, 0x60000000); //nop the InitControl call in the init func
kmWrite24(0x80899a36, 'PUL'); //8064ba38
kmWrite24(0x80899a5B, 'PUL'); //8064ba90

ExpWFCMain::ExpWFCMain() {
    this->onSettingsClick.subject = this;
    this->onSettingsClick.ptmf = &ExpWFCMain::OnSettingsButtonClick;
    this->onButtonSelectHandler.ptmf = &ExpWFCMain::ExtOnButtonSelect;
}

void ExpWFCMain::OnInit() {
    U8_WWS_CHECK = 0x00;
    this->InitControlGroup(6); //5 controls usually + settings button
    WFCMainMenu::OnInit();
    this->AddControl(5, settingsButton, 0);

    this->settingsButton.Load(UI::buttonFolder, "Settings1P", "Settings", 1, 0, false);
    this->settingsButton.buttonId = 5;
    this->settingsButton.SetOnClickHandler(this->onSettingsClick, 0);
    this->settingsButton.SetOnSelectHandler(this->onButtonSelectHandler);

    this->topSettingsPage = SettingsPanel::id;
}

void ExpWFCMain::OnSettingsButtonClick(PushButton& pushButton, u32 r5) {
    ExpSection::GetSection()->GetPulPage<SettingsPanel>()->prevPageId = PAGE_WFC_MAIN;
    this->nextPageId = static_cast<PageId>(this->topSettingsPage);
    this->EndStateAnimated(0, pushButton.GetAnimationFrameSize());
}

void ExpWFCMain::ExtOnButtonSelect(PushButton& button, u32 hudSlotId) {
    U8_WWS_CHECK = 0x00;
    if(button.buttonId == 5) {
        u32 bmgId = BMG_SETTINGS_BOTTOM + 1;
        if(this->topSettingsPage == PAGE_VS_TEAMS_VIEW) bmgId += 1;
        else if(this->topSettingsPage == PAGE_BATTLE_MODE_SELECT) bmgId += 2;
        this->bottomText.SetMessage(bmgId, 0);
    }
    else this->OnButtonSelect(button, hudSlotId);
}

//ExpWFCModeSel
kmWrite32(0x8064c284, 0x38800001); //distance func

ExpWFCModeSel::ExpWFCModeSel() : lastClickedButton(0) {
    this->onButtonSelectHandler.ptmf = &ExpWFCModeSel::OnModeButtonSelect;
    this->onModeButtonClickHandler.ptmf = &ExpWFCModeSel::OnModeButtonClick;
}

void ExpWFCModeSel::InitOTTButton(ExpWFCModeSel& self) {
    self.InitControlGroup(19);
    self.AddControl(5, self.ottButton, 0);
    self.ottButton.Load(UI::buttonFolder, "PULOTTButton", "PULOTTButton", 1, 0, 0);
    self.ottButton.buttonId = ottButtonId;
    self.ottButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.ottButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(6, self.countdownButton, 0);
    self.countdownButton.Load(UI::buttonFolder, "CountdownButton", "PULOTTButton", 1, 0, 0);
    self.countdownButton.buttonId = countdownButtonId;
    self.countdownButton.SetMessage(BMG_COUNTDOWN_BUTTON);
    self.countdownButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.countdownButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(7, self.bombblastButton, 0);
    self.bombblastButton.Load(UI::buttonFolder, "BombBlastButton", "PULOTTButton", 1, 0, 0);
    self.bombblastButton.buttonId = bombblastButtonId;
    self.bombblastButton.SetMessage(BMG_BOMBBLAST_BUTTON);
    self.bombblastButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.bombblastButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(8, self.accelerationButton, 0);
    self.accelerationButton.Load(UI::buttonFolder, "AccelerationButton", "PULOTTButton", 1, 0, 0);
    self.accelerationButton.buttonId = accelerationButtonId;
    self.accelerationButton.SetMessage(BMG_ACCELERATION_BUTTON);
    self.accelerationButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.accelerationButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(9, self.bananaslipButton, 0);
    self.bananaslipButton.Load(UI::buttonFolder, "BananaSlipButton", "PULOTTButton", 1, 0, 0);
    self.bananaslipButton.buttonId = bananaslipButtonId;
    self.bananaslipButton.SetMessage(BMG_BANANASLIP_BUTTON);
    self.bananaslipButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.bananaslipButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(10, self.randomitemsButton, 0);
    self.randomitemsButton.Load(UI::buttonFolder, "RandomItemsButton", "PULOTTButton", 1, 0, 0);
    self.randomitemsButton.buttonId = randomitemsButtonId;
    self.randomitemsButton.SetMessage(BMG_RANDOMITEMS_BUTTON);
    self.randomitemsButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.randomitemsButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(11, self.unfairitemsButton, 0);
    self.unfairitemsButton.Load(UI::buttonFolder, "UnfairItemsButton", "PULOTTButton", 1, 0, 0);
    self.unfairitemsButton.buttonId = unfairitemsButtonId;
    self.unfairitemsButton.SetMessage(BMG_UNFAIRITEMS_BUTTON);
    self.unfairitemsButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.unfairitemsButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(12, self.bsmadnessButton, 0);
    self.bsmadnessButton.Load(UI::buttonFolder, "BSMadnessButton", "PULOTTButton", 1, 0, 0);
    self.bsmadnessButton.buttonId = bsmadnessButtonId;
    self.bsmadnessButton.SetMessage(BMG_BSMADNESS_BUTTON);
    self.bsmadnessButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.bsmadnessButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(13, self.mushroomdashButton, 0);
    self.mushroomdashButton.Load(UI::buttonFolder, "MushroomDashButton", "PULOTTButton", 1, 0, 0);
    self.mushroomdashButton.buttonId = mushroomdashButtonId;
    self.mushroomdashButton.SetMessage(BMG_MUSHROOMDASH_BUTTON);
    self.mushroomdashButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.mushroomdashButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(14, self.bumperkartsButton, 0);
    self.bumperkartsButton.Load(UI::buttonFolder, "BumperKartsButton", "PULOTTButton", 1, 0, 0);
    self.bumperkartsButton.buttonId = bumperkartsButtonId;
    self.bumperkartsButton.SetMessage(BMG_BUMPERKARTS_BUTTON);
    self.bumperkartsButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.bumperkartsButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(15, self.itemrampageButton, 0);
    self.itemrampageButton.Load(UI::buttonFolder, "ItemRampageButton", "PULOTTButton", 1, 0, 0);
    self.itemrampageButton.buttonId = itemrampageButtonId;
    self.itemrampageButton.SetMessage(BMG_ITEMRAMPAGE_BUTTON);
    self.itemrampageButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.itemrampageButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(16, self.itemrainButton, 0);
    self.itemrainButton.Load(UI::buttonFolder, "ItemRainButton", "PULOTTButton", 1, 0, 0);
    self.itemrainButton.buttonId = itemrainButtonId;
    self.itemrainButton.SetMessage(BMG_ITEMRAIN_BUTTON);
    self.itemrainButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.itemrainButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(17, self.shellbreakButton, 0);
    self.shellbreakButton.Load(UI::buttonFolder, "ShellBreakButton", "PULOTTButton", 1, 0, 0);
    self.shellbreakButton.buttonId = shellbreakButtonId;
    self.shellbreakButton.SetMessage(BMG_SHELLBREAK_BUTTON);
    self.shellbreakButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.shellbreakButton.SetOnSelectHandler(self.onButtonSelectHandler);

    self.AddControl(18, self.booststackerButton, 0);
    self.booststackerButton.Load(UI::buttonFolder, "BoostStackerButton", "PULOTTButton", 1, 0, 0);
    self.booststackerButton.buttonId = booststackerButtonId;
    self.booststackerButton.SetMessage(BMG_BOOSTSTACKER_BUTTON);
    self.booststackerButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.booststackerButton.SetOnSelectHandler(self.onButtonSelectHandler);



    Text::Info info;
    RKSYS::Mgr* rksysMgr = RKSYS::Mgr::sInstance;
    u32 vr = 0;
    if(rksysMgr->curLicenseId >= 0) {
        RKSYS::LicenseMgr& license = rksysMgr->licenses[rksysMgr->curLicenseId];
        vr = license.vr.points;
    }
    info.intToPass[0] = vr;
    self.ottButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.countdownButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.bombblastButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.accelerationButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.bananaslipButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.randomitemsButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.unfairitemsButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.bsmadnessButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.mushroomdashButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.bumperkartsButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.itemrampageButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.itemrainButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.shellbreakButton.SetTextBoxMessage("go", BMG_RATING, &info);
    self.booststackerButton.SetTextBoxMessage("go", BMG_RATING, &info);
}
kmCall(0x8064c294, ExpWFCModeSel::InitOTTButton);

void ExpWFCModeSel::OnActivatePatch() {
    register ExpWFCModeSel* page;
    asm(mr page, r29;);
    register Pages::GlobeSearch* search;
    asm(mr search, r30;);
    const bool isHidden = search->searchType == 1 ? false : true; //make the button visible if continental was clicked
    page->ottButton.isHidden = isHidden;
    page->ottButton.manipulator.inaccessible = isHidden;
    page->nextPage = PAGE_NONE;
    PushButton* button = &page->vsButton;
    u32 bmgId = UI::BMG_RACE_WITH11P;
    switch(page->lastClickedButton) { //case 1 is already default
        case 2:
            button = &page->battleButton;
            bmgId = UI::BMG_BATTLE_WITH6P;
            break;
        case ottButtonId:
            if(!isHidden) {
                button = &page->ottButton;
                bmgId = UI::BMG_OTT_WW_BOTTOM;
            }
            break;
        case countdownButtonId:
            if(!isHidden) {
                button = &page->countdownButton;
                bmgId = UI::BMG_COUNTDOWN_WW_BOTTOM;
            }
            break;
        case bombblastButtonId:
            if(!isHidden) {
                button = &page->bombblastButton;
                bmgId = UI::BMG_BOMBBLAST_WW_BOTTOM;
            }
            break;
        case accelerationButtonId:
            if(!isHidden) {
                button = &page->accelerationButton;
                bmgId = UI::BMG_ACCELERATION_WW_BOTTOM;
            }
            break;
        case bananaslipButtonId:
            if(!isHidden) {
                button = &page->bananaslipButton;
                bmgId = UI::BMG_BANANASLIP_WW_BOTTOM;
            }
            break;
            case randomitemsButtonId:
            if(!isHidden) {
                button = &page->randomitemsButton;
                bmgId = UI::BMG_RANDOMITEMS_WW_BOTTOM;
            }
            break;
            case unfairitemsButtonId:
            if(!isHidden) {
                button = &page->unfairitemsButton;
                bmgId = UI::BMG_UNFAIRITEMS_WW_BOTTOM;
            }
            break;
            case bsmadnessButtonId:
            if(!isHidden) {
                button = &page->bsmadnessButton;
                bmgId = UI::BMG_BSMADNESS_WW_BOTTOM;
            }
            break;

            case mushroomdashButtonId:
            if(!isHidden) {
                button = &page->mushroomdashButton;
                bmgId = UI::BMG_MUSHROOMDASH_WW_BOTTOM;
            }
            break;
            case bumperkartsButtonId:
            if(!isHidden) {
                button = &page->bumperkartsButton;
                bmgId = UI::BMG_BUMPERKARTS_WW_BOTTOM;
            }
            break;
        case itemrampageButtonId:
            if(!isHidden) {
                button = &page->itemrampageButton;
                bmgId = UI::BMG_ITEMRAMPAGE_WW_BOTTOM;
            }
            break;
        case itemrainButtonId:
            if(!isHidden) {
                button = &page->itemrainButton;
                bmgId = UI::BMG_ITEMRAIN_WW_BOTTOM;
            }
            break;
        case shellbreakButtonId:
            if(!isHidden) {
                button = &page->shellbreakButton;
                bmgId = UI::BMG_SHELLBREAK_WW_BOTTOM;
            }
            break;
        case booststackerButtonId:
            if(!isHidden) {
                button = &page->booststackerButton;
                bmgId = UI::BMG_BOOSTSTACKER_WW_BOTTOM;
            }
            break;
    }
    page->bottomText.SetMessage(bmgId);
    button->SelectInitial(0);
}
kmCall(0x8064c5f0, ExpWFCModeSel::OnActivatePatch);

void ExpWFCModeSel::OnModeButtonSelect(PushButton& modeButton, u32 hudSlotId) {
    if(modeButton.buttonId == ottButtonId) {
        this->bottomText.SetMessage(BMG_OTT_WW_BOTTOM);
    }
    if(modeButton.buttonId == countdownButtonId) {
        this->bottomText.SetMessage(BMG_COUNTDOWN_WW_BOTTOM);
    }
    if(modeButton.buttonId == bombblastButtonId) {
        this->bottomText.SetMessage(BMG_BOMBBLAST_WW_BOTTOM);
    }
    if(modeButton.buttonId == accelerationButtonId) {
        this->bottomText.SetMessage(BMG_ACCELERATION_WW_BOTTOM);
    }
    if(modeButton.buttonId == bananaslipButtonId) {
        this->bottomText.SetMessage(BMG_BANANASLIP_WW_BOTTOM);
    }
    if(modeButton.buttonId == randomitemsButtonId) {
        this->bottomText.SetMessage(BMG_RANDOMITEMS_WW_BOTTOM);
    }
    if(modeButton.buttonId == unfairitemsButtonId) {
        this->bottomText.SetMessage(BMG_UNFAIRITEMS_WW_BOTTOM);
    }
    if(modeButton.buttonId == bsmadnessButtonId) {
        this->bottomText.SetMessage(BMG_BSMADNESS_WW_BOTTOM);
    }
    if(modeButton.buttonId == mushroomdashButtonId) {
        this->bottomText.SetMessage(BMG_MUSHROOMDASH_WW_BOTTOM);
    }
    if(modeButton.buttonId == bumperkartsButtonId) {
        this->bottomText.SetMessage(BMG_BUMPERKARTS_WW_BOTTOM);
    }
    if(modeButton.buttonId == itemrampageButtonId) {
        this->bottomText.SetMessage(BMG_ITEMRAMPAGE_WW_BOTTOM);
    }
    if(modeButton.buttonId == itemrainButtonId) {
        this->bottomText.SetMessage(BMG_ITEMRAIN_WW_BOTTOM);
    }
    if(modeButton.buttonId == shellbreakButtonId) {
        this->bottomText.SetMessage(BMG_SHELLBREAK_WW_BOTTOM);
    }
    if(modeButton.buttonId == booststackerButtonId) {
        this->bottomText.SetMessage(BMG_BOOSTSTACKER_WW_BOTTOM);
    }
    else WFCModeSelect::OnModeButtonSelect(modeButton, hudSlotId);
}

void ExpWFCModeSel::OnModeButtonClick(PushButton& modeButton, u32 hudSlotId) {
    const u32 prevId = modeButton.buttonId;
    this->lastClickedButton = prevId;
    U8_WWS_CHECK = 0x01;
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
    GameModeOnline = 0x00;
    if(prevId == ottButtonId) {
        U16_GAMEPLAYE = 0x0001;
        System::sInstance->netMgr.region = 0x46;
        GameModeOnline = 0x0E;
    }
    else if(prevId == countdownButtonId) {
        U16_GAMEPLAYC = 0x0001;
        U16_GAMEPLAYC2 = 0x0001;
        GameModeOnline = 0x0C;
        System::sInstance->netMgr.region = 0x47;
    }
    else if(prevId == bombblastButtonId) {
        U16_GAMEPLAY1 = 0x0001;
        System::sInstance->netMgr.region = 0x48;
        GameModeOnline = 0x01;
    }
    else if(prevId == accelerationButtonId) {
        U16_GAMEPLAY2 = 0x0001;
        System::sInstance->netMgr.region = 0x49;
        GameModeOnline = 0x02;
    }
    else if(prevId == bananaslipButtonId) {
        U16_GAMEPLAY3 = 0x0001;
        System::sInstance->netMgr.region = 0x4A;
        GameModeOnline = 0x03;
    }
    else if(prevId == randomitemsButtonId) {
        U16_GAMEPLAY4 = 0x0001;
        System::sInstance->netMgr.region = 0x4B;
        GameModeOnline = 0x04;
    }
    else if(prevId == unfairitemsButtonId) {
        U16_GAMEPLAY5 = 0x0001;
        System::sInstance->netMgr.region = 0x4C;
        GameModeOnline = 0x05;
    }
    else if(prevId == bsmadnessButtonId) {
        U16_GAMEPLAY6 = 0x0001;
        System::sInstance->netMgr.region = 0x4D;
        GameModeOnline = 0x06;
    }
    else if(prevId == mushroomdashButtonId) {
        U16_GAMEPLAY7 = 0x0001;
        System::sInstance->netMgr.region = 0x4E;
        GameModeOnline = 0x07;
    }
    else if(prevId == bumperkartsButtonId) {
        U16_GAMEPLAY8 = 0x0001;
        System::sInstance->netMgr.region = 0x4F;
        GameModeOnline = 0x08;
    }
    else if(prevId == itemrampageButtonId) {
        U16_GAMEPLAY9 = 0x0001;
        System::sInstance->netMgr.region = 0x50;
        GameModeOnline = 0x09;
    }
    else if(prevId == itemrainButtonId) {
        U16_GAMEPLAYA = 0x0001;
        System::sInstance->netMgr.region = 0x51;
        GameModeOnline = 0x0A;
    }
    else if(prevId == shellbreakButtonId) {
        U16_GAMEPLAYB = 0x0001;
        System::sInstance->netMgr.region = 0x52;
        GameModeOnline = 0x0B;
    }
    else if(prevId == booststackerButtonId) {
        U16_GAMEPLAYD = 0x0001;
        System::sInstance->netMgr.region = 0x53;
        GameModeOnline = 0x0D;
    }
    else {
        System::sInstance->netMgr.region = 0x45;
    }
    WFCModeSelect::OnModeButtonClick(modeButton, hudSlotId);
    modeButton.buttonId = prevId;
}

//change initial button and instruction
//kmWrite32(0x8064bcb4, 0x386306d8);
//kmWrite32(0x8064bcc0, 0x388010d8);
}//namespace UI
}//namespace Pulsar