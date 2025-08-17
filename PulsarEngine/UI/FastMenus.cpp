#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <Settings/Settings.hpp>
#include <MKVN.hpp>

namespace Pulsar {
namespace UI {
//Adapted from east_'s code
static void FasterMenusOnSceneChange(SectionMgr* sectionMgr, u32 delay, u32 color) {
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC, SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_ENABLED) delay = 0;
    sectionMgr->RequestSceneChange(delay, color);
}
kmCall(0x80602510, FasterMenusOnSceneChange);

//Adapted from east_'s code
static void FasterMenuPatchTransitionDelay() {
    const u8 val = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MISC, SETTINGMENU_RADIO_FASTMENUS);
    float transitionDelay = 176.0f;
    F32_MENUSPEED = 0.0f;
    if(val == MENUSETTING_FASTMENUS_ENABLED) {
        transitionDelay -= transitionDelay;
        F32_MENUSPEED = 300.0f;
    }
    Page::transitionDelay = transitionDelay;
};
static Settings::Hook FasterMenus(FasterMenuPatchTransitionDelay);
BootHook FasterMenusBoot(FasterMenuPatchTransitionDelay, 3);

}//namespace UI
}//namespace Pulsar