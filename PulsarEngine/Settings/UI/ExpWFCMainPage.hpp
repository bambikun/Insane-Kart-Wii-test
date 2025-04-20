#ifndef _PUL_WFC_
#define _PUL_WFC_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/WFCMenu.hpp>
#include <Settings/UI/SettingsPanel.hpp>

//Extends WFCMainMenu to add a settings button
namespace Pulsar {
namespace UI {
class ExpWFCMain : public Pages::WFCMainMenu {
public:
    ExpWFCMain();
    void OnInit() override;
private:
    void OnSettingsButtonClick(PushButton& PushButton, u32 r5);
    void ExtOnButtonSelect(PushButton& pushButton, u32 hudSlotId);
    PtmfHolder_2A<ExpWFCMain, void, PushButton&, u32> onSettingsClick;
    PushButton settingsButton;
public:
    PulPageId topSettingsPage;
};

class ExpWFCModeSel : public Pages::WFCModeSelect {
public:
    ExpWFCModeSel();
    static void InitOTTButton(ExpWFCModeSel& self);
    static void OnActivatePatch();
private:
    void OnModeButtonSelect(PushButton& modeButton, u32 hudSlotId); //8064c718
    void OnModeButtonClick(PushButton& PushButton, u32 r5);
    PushButton ottButton;
    PushButton countdownButton;
    PushButton bombblastButton;
    PushButton accelerationButton;
    PushButton bananaslipButton;
    PushButton randomitemsButton;
    PushButton unfairitemsButton;
    PushButton bsmadnessButton;
    PushButton mushroomdashButton;
    PushButton bumperkartsButton;
    PushButton itemrampageButton;
    PushButton itemrainButton;
    PushButton shellbreakButton;
    PushButton booststackerButton;
    u32 lastClickedButton;
    static const u32 ottButtonId = 4;
    static const u32 countdownButtonId = 5;
    static const u32 bombblastButtonId = 6;
    static const u32 accelerationButtonId = 7;
    static const u32 bananaslipButtonId = 8;
    static const u32 randomitemsButtonId = 9;
    static const u32 unfairitemsButtonId = 10;
    static const u32 bsmadnessButtonId = 11;
    static const u32 mushroomdashButtonId = 12;
    static const u32 bumperkartsButtonId = 13;
    static const u32 itemrampageButtonId = 14;
    static const u32 itemrainButtonId = 15;
    static const u32 shellbreakButtonId = 16;
    static const u32 booststackerButtonId = 17;
};
}//namespace UI
}//namespace Pulsar

#endif