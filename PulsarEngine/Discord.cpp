#include <Dolphin/DolphinIOS.hpp>
#include <UI/UI.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKSYS/RKSYSMgr.hpp>
#include <Core/rvl/DWC/DWCAccount.hpp>


namespace Discord {

    static bool hasWrittenClientID = false;
    static int frameCount = 0;
    static u64 startTimeStamp = 0;
    SectionId prevSectionId = SECTION_NONE;
    
    // Removes 00 1A escapes from the BMG text
    void CleanBMGMessage(wchar_t* dest, const wchar_t* src) {
        int inc = 0;
        for (int i = 0; i < 0x100 && src[i]; i++) {
            if (src[i] == 0x001a) {
                u8 size = *(u8*)(&src[i + 1]);
                i += (size / 2) - 1;
            } else {
                dest[inc] = src[i];
                inc++;
            }
        }
    }
    
    void DiscordRichPresence(Section* _this) {
        _this->Update();
        if (!Dolphin::IsEmulator()) {
            return;
        }
    
        if (_this->sectionId == prevSectionId && ((frameCount++ % 900) != 0)) {
            return;
        }
    
        if (!hasWrittenClientID) {
            Dolphin::SetDiscordClient("1343655848446001283");
            hasWrittenClientID = true;
        }
    
        char* state = "";
        char* details = "In a Menu";
        char* largeImageText = "";
        char* smallImageKey = "";
        int minPlayers = 0;
        int maxPlayers = 0;
    
        RKSYS::Mgr* rksysMgr = RKSYS::Mgr::sInstance;
        u32 vr = 0, br = 0;
        u64 fc = 0;
        if(rksysMgr && rksysMgr->curLicenseId >= 0) {
            RKSYS::LicenseMgr& license = rksysMgr->licenses[rksysMgr->curLicenseId];
            vr = license.vr.points;
            br = license.br.points;
            fc = DWC::CreateFriendKey(&license.dwcAccUserData);
        }
    
        if (fc) {
            u32 fcParts[3];
            for (int j = 0; j < 3; ++j) {
                fcParts[j] = fc % 10000;
                fc /= 10000;
            }
    
            char fcText[32];
            snprintf(fcText, 32, "Friend Code: %04u-%04u-%04u", fcParts[2], fcParts[1], fcParts[0]);
            largeImageText = fcText;
        }
    
        if (_this->sectionId != prevSectionId) {
            Dolphin::GetSystemTime(startTimeStamp);
            prevSectionId = _this->sectionId;
        }
    
        wchar_t trackNameW[0x100];
        char trackName[0x100];
    
        memset(trackNameW, 0, 0x100);
    
        u32 bmgId = Pulsar::UI::GetCurTrackBMG();
        const wchar_t* msg = Pulsar::UI::GetCustomMsg(bmgId);
        if (msg && Raceinfo::sInstance && Raceinfo::sInstance->IsAtLeastStage(RACESTAGE_INTRO)) {
            CleanBMGMessage(trackNameW, msg);
            wcstombs(trackName, trackNameW, 32);
            state = trackName;
        }
    
        RKNet::Controller* controller = RKNet::Controller::sInstance;
        if (controller) {
            RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
            maxPlayers = 12;
            minPlayers = sub.playerCount;
        }
    
        prevSectionId = _this->sectionId;
        switch (_this->sectionId) {
            case SECTION_GP:
                details = "In a Grand Prix";
                break;
            case SECTION_TT:
                details = "In Time Trials";
                break;
            case SECTION_P1VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 1P VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 1P VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 1P VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 1P VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 1P VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 1P VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 1P VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 1P VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 1P VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 1P VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 1P VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 1P VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 1P VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 1P VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 1P VS (Ultras Allowed)";
                break;
            case SECTION_P2VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 2P VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 2P VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 2P VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 2P VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 2P VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 2P VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 2P VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 2P VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 2P VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 2P VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 2P VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 2P VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 2P VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 2P VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 2P VS (Ultras Allowed)";
                break;
            case SECTION_P3VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 3P VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 3P VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 3P VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 3P VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 3P VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 3P VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 3P VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 3P VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 3P VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 3P VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 3P VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 3P VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 3P VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 3P VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 3P VS (Ultras Allowed)";
                break;
            case SECTION_P4VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 4P VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 4P VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 4P VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 4P VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 4P VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 4P VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 4P VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 4P VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 4P VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 4P VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 4P VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 4P VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 4P VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 4P VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 4P VS (Ultras Allowed)";
                break;
            case SECTION_P1TEAM_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 1P Team VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 1P Team VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 1P Team VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 1P Team VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 1P Team VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 1P Team VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 1P Team VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 1P Team VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 1P Team VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 1P Team VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 1P Team VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 1P Team VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 1P Team VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 1P Team VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 1P Team VS (Ultras Allowed)";
                break;
            case SECTION_P2TEAM_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 2P Team VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 2P Team VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 2P Team VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 2P Team VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 2P Team VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 2P Team VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 2P Team VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 2P Team VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 2P Team VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 2P Team VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 2P Team VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 2P Team VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 2P Team VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 2P Team VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 2P Team VS (Ultras Allowed)";
                break;
            case SECTION_P3TEAM_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 3P Team VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 3P Team VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 3P Team VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 3P Team VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 3P Team VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 3P Team VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 3P Team VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 3P Team VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 3P Team VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 3P Team VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 3P Team VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 3P Team VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 3P Team VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 3P Team VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 3P Team VS (Ultras Allowed)";
                break;
            case SECTION_P4TEAM_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a 4P Team VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a 4P Team VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a 4P Team VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a 4P Team VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a 4P Team VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a 4P Team VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a 4P Team VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a 4P Team VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a 4P Team VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a 4P Team VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a 4P Team VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a 4P Team VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a 4P Team VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a 4P Team VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a 4P Team VS (Ultras Allowed)";
                break;
            case SECTION_P1BATTLE:
                details = "In a 1P Battle";
                break;
            case SECTION_P2BATTLE:
                details = "In a 2P Battle";
                break;
            case SECTION_P3BATTLE:
                details = "In a 3P Battle";
                break;
            case SECTION_P4BATTLE:
                details = "In a 4P Battle";
                break;
            case SECTION_MISSION_MODE:
                details = "In Mission Mode";
                break;
            case SECTION_TOURNAMENT:
                details = "In a Tournament";
                break;
            case SECTION_GP_REPLAY:
                details = "Watching a GP Replay";
                break;
            case SECTION_WATCH_GHOST_FROM_MENU:
                details = "Watching a TT Replay";
                break;
            case SECTION_TT_REPLAY:
                details = "Watching a TT Replay";
                break;
            case SECTION_P1_WIFI:
            case SECTION_P1_WIFI_FROM_FROOM_RACE:
            case SECTION_P1_WIFI_FROM_FIND_FRIEND:
            case SECTION_P2_WIFI:
            case SECTION_P2_WIFI_FROM_FROOM_RACE:
            case SECTION_P2_WIFI_FROM_FIND_FRIEND:
                details = "In a WiFi menu";
                break;
            case SECTION_P1_WIFI_VS_VOTING:
            case SECTION_P2_WIFI_VS_VOTING:
                details = "Voting for a WiFi VS";
                break;
            case SECTION_P1_WIFI_BATTLE_VOTING:
            case SECTION_P2_WIFI_BATTLE_VOTING:
                details = "Voting for a WiFi Battle";
                break;
            case SECTION_P1_WIFI_FROOM_VS_VOTING:
            case SECTION_P2_WIFI_FROOM_VS_VOTING:
                details = "Voting for a VS in a froom";
                break;
            case SECTION_P1_WIFI_FROOM_TEAMVS_VOTING:
            case SECTION_P2_WIFI_FROOM_TEAMVS_VOTING:
                details = "Voting for a Team VS in a froom";

                break;
            case SECTION_P1_WIFI_FROOM_BALLOON_VOTING:
            case SECTION_P2_WIFI_FROOM_BALLOON_VOTING:
                details = "Voting for a Balloon Battle in a froom";
                break;
            case SECTION_P1_WIFI_FROOM_COIN_VOTING:
            case SECTION_P2_WIFI_FROOM_COIN_VOTING:
                details = "Voting for a Coin Runners in a froom";
                break;
            case SECTION_P1_WIFI_VS:
            case SECTION_P2_WIFI_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a WiFi VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a WiFi VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a WiFi VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a WiFi VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a WiFi VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a WiFi VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a WiFi VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a WiFi VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a WiFi VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a WiFi VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a WiFi VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a WiFi VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a WiFi VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a WiFi VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a WiFi VS (Ultras Allowed)";
                break;
            case SECTION_P1_WIFI_BT:
            case SECTION_P2_WIFI_BT:
                details = "Racing a WiFi Battle";
                break;
            case SECTION_P1_WIFI_FRIEND_VS:
            case SECTION_P2_WIFI_FRIEND_VS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a WiFi Friend VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a WiFi Friend VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a WiFi Friend VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a WiFi Friend VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a WiFi Friend VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a WiFi Friend VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a WiFi Friend VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a WiFi Friend VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a WiFi Friend VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a WiFi Friend VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a WiFi Friend VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a WiFi Friend VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a WiFi Friend VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a WiFi Friend VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a WiFi Friend VS (Ultras Allowed)";
                break;
            case SECTION_P1_WIFI_FRIEND_TEAMVS:
            case SECTION_P2_WIFI_FRIEND_TEAMVS:
            if(U16_GAMEPLAY1 == 0x0000 && U16_GAMEPLAY2 == 0x0000 && U16_GAMEPLAY3 == 0x0000 && U16_GAMEPLAY4 == 0x0000 && U16_GAMEPLAY5 == 0x0000 && U16_GAMEPLAY6 == 0x0000 && U16_GAMEPLAY7 == 0x0000 && U16_GAMEPLAY8 == 0x0000 && U16_GAMEPLAY9 == 0x0000 && U16_GAMEPLAYA == 0x0000 && U16_GAMEPLAYB == 0x0000 && U16_GAMEPLAYC == 0x0000 && U16_GAMEPLAYD == 0x0000 && U16_GAMEPLAYE == 0x0000) details = "In a WiFi Friend Team VS (Default)";
            if(U16_GAMEPLAY1 == 0x0001) details = "In a WiFi Friend Team VS (Bob-omb Blast)";
            if(U16_GAMEPLAY2 == 0x0001) details = "In a WiFi Friend Team VS (Infinite Acceleration)";
            if(U16_GAMEPLAY3 == 0x0001) details = "In a WiFi Friend Team VS (Banana Slip)";
            if(U16_GAMEPLAY4 == 0x0001) details = "In a WiFi Friend Team VS (Random Items)";
            if(U16_GAMEPLAY5 == 0x0001) details = "In a WiFi Friend Team VS (Unfair Items)";
            if(U16_GAMEPLAY6 == 0x0001) details = "In a WiFi Friend Team VS (Blue Shell Madness)";
            if(U16_GAMEPLAY7 == 0x0001) details = "In a WiFi Friend Team VS (Mushroom Dash)";
            if(U16_GAMEPLAY8 == 0x0001) details = "In a WiFi Friend Team VS (Bumper Karts)";
            if(U16_GAMEPLAY9 == 0x0001) details = "In a WiFi Friend Team VS (Item Rampage)";
            if(U16_GAMEPLAYA == 0x0001) details = "In a WiFi Friend Team VS (Item Rain)";
            if(U16_GAMEPLAYB == 0x0001) details = "In a WiFi Friend Team VS (Shell Break)";
            if(U16_GAMEPLAYC == 0x0001) details = "In a WiFi Friend Team VS (Countdown)";
            if(U16_GAMEPLAYD == 0x0001) details = "In a WiFi Friend Team VS (Riibalanced)";
            if(U16_GAMEPLAYE == 0x0001) details = "In a WiFi Friend Team VS (Ultras Allowed)";
                break;
            case SECTION_P1_WIFI_FRIEND_BALLOON:
            case SECTION_P2_WIFI_FRIEND_BALLOON:
                details = "Racing a WiFi Friend Balloon Battle";
                break;
            case SECTION_P1_WIFI_FRIEND_COIN:
            case SECTION_P2_WIFI_FRIEND_COIN:
                details = "Racing a WiFi Friend Coin Runners";
                break;
            case SECTION_P1_WIFI_VS_LIVEVIEW:
            case SECTION_P2_WIFI_VS_LIVEVIEW:
                details = "Spectating a WiFi VS";

                break;
            case SECTION_P1_WIFI_BT_LIVEVIEW:
            case SECTION_P2_WIFI_BT_LIVEVIEW:
                details = "Spectating a WiFi Battle";
                break;
            default:
                state = "";
                break;
        }
    
        if (_this->sectionId >= SECTION_P1_WIFI && _this->sectionId <= SECTION_P2_WIFI_FRIEND_COIN) {
            char newDetails[0x100];
            snprintf(newDetails, 0x100, "%s (VR: %d)", details, vr, br);
            details = newDetails;
        }
    
        Dolphin::SetDiscordPresence(
            details,
            state,
            "image_logo",
            largeImageText,
            smallImageKey,
            "",
            startTimeStamp,
            0,
            minPlayers,
            maxPlayers
        );
    }
    
    kmCall(0x80635540, DiscordRichPresence);
    
    } // namespace Discord
