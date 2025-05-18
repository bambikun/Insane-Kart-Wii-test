#include <kamek.hpp>
#include <MarioKartWii/Audio/AudioManager.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <Sound/MiscSound.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>
#include <MKVN.hpp>


namespace Pulsar {
namespace Sound {
//Custom implementation of music slot expansion; this would break with regs
//kmWrite32(0x8009e0dc, 0x7F87E378); //mr r7, r28 to get string length

static char pulPath[0x100];
s32 CheckBRSTM(const nw4r::snd::DVDSoundArchive* archive, PulsarId id, u8 variantIdx, bool isFinalLap) {

    const char* root = archive->extFileRoot;
    const char* lapSpecifier = isFinalLap ? "_f" : "_n";
    s32 ret = -1;
    char trackName[0x100];
    UI::GetTrackBMG(trackName, id);
    snprintf(pulPath, 0x100, "%sstrm/%s%s.brstm", root, trackName, lapSpecifier);
    ret = DVD::ConvertPathToEntryNum(pulPath);
    if(ret < 0) {
        u32 variantIdx = CupsConfig::sInstance->GetCurVariantIdx();
        if(variantIdx == 0) snprintf(pulPath, 0x50, "%sstrm/%d%s.brstm", root, CupsConfig::ConvertTrack_PulsarIdToRealId(id), lapSpecifier);
        else snprintf(pulPath, 0x50, "%sstrm/%d_%d%s.brstm", root, CupsConfig::ConvertTrack_PulsarIdToRealId(id), variantIdx, lapSpecifier);
        if(id == 0x1066 || id == 0x1067 || id == 0x1068) snprintf(pulPath, 0x50, "%sstrm/3BC%s.brstm", root, lapSpecifier);
        if(id == 0x1042 || id == 0x1041 || id == 0x1040) snprintf(pulPath, 0x50, "%sstrm/3CCL%s.brstm", root, lapSpecifier);
        if(id == 0x103E || id == 0x103D || id == 0x103F) snprintf(pulPath, 0x50, "%sstrm/3DH%s.brstm", root, lapSpecifier);
        if(id == 0x1060 || id == 0x124A || id == 0x1061 || id == 0x105D || id == 0x105E || id == 0x105F) snprintf(pulPath, 0x50, "%sstrm/3DKJ%s.brstm", root, lapSpecifier);
        if(id == 0x1176 || id == 0x105C || id == 0x1048 || id == 0x1046) snprintf(pulPath, 0x50, "%sstrm/3W%s.brstm", root, lapSpecifier);
        if(id == 0x104C || id == 0x1049 || id == 0x104A || id == 0x104D || id == 0x104B || id == 0x103B || id == 0x103C || id == 0x1039 || id == 0x103A) snprintf(pulPath, 0x50, "%sstrm/3C%s.brstm", root, lapSpecifier);
        if(id == 0x104E || id == 0x1050 || id == 0x104F) snprintf(pulPath, 0x50, "%sstrm/3MP%s.brstm", root, lapSpecifier);
        if(id == 0x105A || id == 0x12F0 || id == 0x119D || id == 0x105B) snprintf(pulPath, 0x50, "%sstrm/3NBC%s.brstm", root, lapSpecifier);
        if(id == 0x1056 || id == 0x1055 || id == 0x099B || id == 0x11CA) snprintf(pulPath, 0x50, "%sstrm/3PPS%s.brstm", root, lapSpecifier);
        if(id == 0x1069 || id == 0x106A || id == 0x106B || id == 0x106E || id == 0x106D || id == 0x106C) snprintf(pulPath, 0x50, "%sstrm/3RR%s.brstm", root, lapSpecifier);
        if(id == 0x1051 || id == 0x1052 || id == 0x1054 || id == 0x1053) snprintf(pulPath, 0x50, "%sstrm/3RRM%s.brstm", root, lapSpecifier);
        if(id == 0x1065 || id == 0x09BF || id == 0x1062 || id == 0x1063 || id == 0x1064 || id == 0x1237) snprintf(pulPath, 0x50, "%sstrm/3RIW%s.brstm", root, lapSpecifier);
        if(id == 0x1043 || id == 0x1044) snprintf(pulPath, 0x50, "%sstrm/3SGB%s.brstm", root, lapSpecifier);
        if(id == 0x1057 || id == 0x1058 || id == 0x1059 || id == 0x13AF) snprintf(pulPath, 0x50, "%sstrm/3WS%s.brstm", root, lapSpecifier);
        if(id == 0x1010 || id == 0x1012 || id == 0x1014 || id == 0x1011 || id == 0x1013 || id == 0x13AC) snprintf(pulPath, 0x50, "%sstrm/DAF%s.brstm", root, lapSpecifier);
        if(id == 0x1132 || id == 0x1020 || id == 0x101E || id == 0x101F || id == 0x1021) snprintf(pulPath, 0x50, "%sstrm/DBC%s.brstm", root, lapSpecifier);
        if(id == 0x0FED || id == 0x1163 || id == 0x0FEC || id == 0x0FEA || id == 0x0FEE || id == 0x0FEB || id == 0x0FEF || id == 0x1115 || id == 0x1028 || id == 0x1029 || id == 0x120C) snprintf(pulPath, 0x50, "%sstrm/DCCB%s.brstm", root, lapSpecifier);
        if(id == 0x1116) snprintf(pulPath, 0x50, "%sstrm/DDS%s.brstm", root, lapSpecifier);
        if(id == 0x1001 || id == 0x1002 || id == 0x1003 || id == 0x1004 || id == 0x102E) snprintf(pulPath, 0x50, "%sstrm/DDKP%s.brstm", root, lapSpecifier);
        if(id == 0x1032 || id == 0x1031 || id == 0x102F || id == 0x1030) snprintf(pulPath, 0x50, "%sstrm/DDC%s.brstm", root, lapSpecifier);
        if(id == 0x0FE9 || id == 0x0FE5 || id == 0x0FE4 || id == 0x0FE6 || id == 0x0FE8 || id == 0x0FE7 || id == 0x100D || id == 0x100F || id == 0x1009 || id == 0x100E || id == 0x100B || id == 0x100A || id == 0x100C || id == 0x1117 || id == 0x138D) snprintf(pulPath, 0x50, "%sstrm/DC%s.brstm", root, lapSpecifier);
        if(id == 0x102C || id == 0x102B || id == 0x0FF4 || id == 0x0FF7 || id == 0x0FF5 || id == 0x0FF8 || id == 0x0FF9 || id == 0x0FF6 || id == 0x0FFA || id == 0x102D || id == 0x1136 || id == 0x1019 || id == 0x101C || id == 0x1015 || id == 0x101B || id == 0x1018 || id == 0x1017 || id == 0x1016 || id == 0x101A) snprintf(pulPath, 0x50, "%sstrm/DS%s.brstm", root, lapSpecifier);
        if(id == 0x0FF0 || id == 0x11BD || id == 0x0FF2 || id == 0x0FF1 || id == 0x0FF3) snprintf(pulPath, 0x50, "%sstrm/DLM%s.brstm", root, lapSpecifier);
        if(id == 0x101D) snprintf(pulPath, 0x50, "%sstrm/DPG%s.brstm", root, lapSpecifier);
        if(id == 0x1026 || id == 0x1027 || id == 0x1023 || id == 0x1022 || id == 0x1024 || id == 0x1025) snprintf(pulPath, 0x50, "%sstrm/DRR%s.brstm", root, lapSpecifier);
        if(id == 0x0FFD || id == 0x1000 || id == 0x0FFC || id == 0x0FFF || id == 0x0FFB || id == 0x0FFE) snprintf(pulPath, 0x50, "%sstrm/DSR%s.brstm", root, lapSpecifier);
        if(id == 0x1006 || id == 0x1005 || id == 0x1270 || id == 0x1007 || id == 0x1008 || id == 0x0B88) snprintf(pulPath, 0x50, "%sstrm/DTTC%s.brstm", root, lapSpecifier);
        if(id == 0x0F2F || id == 0x0F2E || id == 0x0F30 || id == 0x125A || id == 0x0F31 || id == 0x0F7F || id == 0x125B || id == 0x0F80 || id == 0x0F81) snprintf(pulPath, 0x50, "%sstrm/GBO%s.brstm", root, lapSpecifier);
        if(id == 0x0F26 || id == 0x0F27 || id == 0x0F23 || id == 0x0F28 || id == 0x1298 || id == 0x0F22 || id == 0x0F24 || id == 0x0F25 || id == 0x0F3C || id == 0x0F3E || id == 0x0F3B || id == 0x0F3A || id == 0x0F40 || id == 0x0F3D || id == 0x0F39 || id == 0x0F3F || id == 0x0F76 || id == 0x12B0 || id == 0x0F84 || id == 0x0F85 || id == 0x0F88 || id == 0x0F87 || id == 0x0F86 || id == 0x0F82 || id == 0x0F83 || id == 0x1108 || id == 0x129E) snprintf(pulPath, 0x50, "%sstrm/GBBC%s.brstm", root, lapSpecifier);
        if(id == 0x0F5A || id == 0x0F5C || id == 0x0F60 || id == 0x0F5D || id == 0x0F5B || id == 0x0F5F || id == 0x0F5E || id == 0x12FD || id == 0x0F1A || id == 0x0F1B) snprintf(pulPath, 0x50, "%sstrm/GBW%s.brstm", root, lapSpecifier);
        if(id == 0x0F34 || id == 0x0F32 || id == 0x0F38 || id == 0x0F37 || id == 0x0F35 || id == 0x0F36) snprintf(pulPath, 0x50, "%sstrm/GBCL%s.brstm", root, lapSpecifier);
        if(id == 0x0F78 || id == 0x0F79 || id == 0x0F7E || id == 0x0F7D || id == 0x0F7A || id == 0x05E2 || id == 0x0F77 || id == 0x0F7B || id == 0x0F7C) snprintf(pulPath, 0x50, "%sstrm/GBLP%s.brstm", root, lapSpecifier);
        if(id == 0x0F48 || id == 0x0F46 || id == 0x0F47 || id == 0x0F45 || id == 0x0F41 || id == 0x0F49 || id == 0x0F42 || id == 0x0F43 || id == 0x0F43 || id == 0x0F44 || id == 0x0F2D || id == 0x0F2B || id == 0x0F2A || id == 0x0F29 || id == 0x0F2C || id == 0x0F10 || id == 0x0F16 || id == 0x0F0D || id == 0x0F0A || id == 0x0F0F || id == 0x0F18 || id == 0x0F11 || id == 0x0F19 || id == 0x0F17 || id == 0x0F15 || id == 0x0F0E || id == 0x0F0C || id == 0x0F0B || id == 0x0F13 || id == 0x0F14 || id == 0x0F12) snprintf(pulPath, 0x50, "%sstrm/GBC%s.brstm", root, lapSpecifier);
        if(id == 0x0F94 || id == 0x0F8B || id == 0x0F91 || id == 0x0F93 || id == 0x0F8E || id == 0x0F8C || id == 0x0F89 || id == 0x0F8A || id == 0x0F8F || id == 0x0F95 || id == 0x0F90 || id == 0x0F8D || id == 0x0F92) snprintf(pulPath, 0x50, "%sstrm/GBRR%s.brstm", root, lapSpecifier);
        if(id == 0x0F6F || id == 0x0F70 || id == 0x0F6E || id == 0x0F71 || id == 0x1210) snprintf(pulPath, 0x50, "%sstrm/GBRIR%s.brstm", root, lapSpecifier);
        if(id == 0x0F1D || id == 0x0F1E || id == 0x0F1F || id == 0x0F1C || id == 0x0F21 || id == 0x0F20) snprintf(pulPath, 0x50, "%sstrm/GBRP%s.brstm", root, lapSpecifier);
        if(id == 0x0F4F || id == 0x11A1 || id == 0x0F50 || id == 0x0F53 || id == 0x0F4E || id == 0x0F4D || id == 0x0F4D || id == 0x0F4B || id == 0x0F58 || id == 0x0F59 || id == 0x0F55 || id == 0x0F4A || id == 0x0F56 || id == 0x0F51 || id == 0x0F54 || id == 0x0F57 || id == 0x0F4C || id == 0x0F52) snprintf(pulPath, 0x50, "%sstrm/GBSG%s.brstm", root, lapSpecifier);
        if(id == 0x0F68 || id == 0x0F6B || id == 0x0F69 || id == 0x0CC7 || id == 0x0F6D || id == 0x0F6C || id == 0x0F67 || id == 0x119F || id == 0x0F6A) snprintf(pulPath, 0x50, "%sstrm/GBSL%s.brstm", root, lapSpecifier);
        if(id == 0x0F62 || id == 0x0F63 || id == 0x0F64 || id == 0x0F61 || id == 0x0F66 || id == 0x0F65) snprintf(pulPath, 0x50, "%sstrm/GBSW%s.brstm", root, lapSpecifier);
        if(id == 0x0F74 || id == 0x0F72 || id == 0x0F73 || id == 0x0F75) snprintf(pulPath, 0x50, "%sstrm/GBYD%s.brstm", root, lapSpecifier);
        if(id == 0x0F9E || id == 0x119E || id == 0x0909 || id == 0x0FA1 || id == 0x0F9F || id == 0x126A || id == 0x0FA3 || id == 0x0FA0 || id == 0x0FA2 || id == 0x0FA5 || id == 0x0FA4) snprintf(pulPath, 0x50, "%sstrm/GBP%s.brstm", root, lapSpecifier);
        if(id == 0x0FCE || id == 0x1178 || id == 0x0FCF || id == 0x0FD0) snprintf(pulPath, 0x50, "%sstrm/GBSC%s.brstm", root, lapSpecifier);
        if(id == 0x0FB4 || id == 0x0FB2 || id == 0x0FB3 || id == 0x0FB5) snprintf(pulPath, 0x50, "%sstrm/GW%s.brstm", root, lapSpecifier);
        if(id == 0x0FD7 || id == 0x0FB8 || id == 0x0FB7) snprintf(pulPath, 0x50, "%sstrm/GSL%s.brstm", root, lapSpecifier);
        if(id == 0x0FC8 || id == 0x0FC7 || id == 0x0FC9 || id == 0x0FCB || id == 0x0FCC || id == 0x0FCD) snprintf(pulPath, 0x50, "%sstrm/GM%s.brstm", root, lapSpecifier);
        if(id == 0x0FAA || id == 0x0FA7 || id == 0x0FA8 || id == 0x0FA6 || id == 0x0FAB || id == 0x0FA9) snprintf(pulPath, 0x50, "%sstrm/GDDD%s.brstm", root, lapSpecifier);
        if(id == 0x0F97 || id == 0x11AD || id == 0x0F99 || id == 0x0F9A || id == 0x0F9D || id == 0x0F9B || id == 0x0F98 || id == 0x0F9C || id == 0x0FB1 || id == 0x0FB0 || id == 0x0FC1 || id == 0x0FC0 || id == 0x0FBF || id == 0x0FBE || id == 0x0FC2 || id == 0x0FC3 || id == 0x13AB) snprintf(pulPath, 0x50, "%sstrm/GC%s.brstm", root, lapSpecifier);
        if(id == 0x1192 || id == 0x0FAF || id == 0x0FAD || id == 0x0FAC || id == 0x0FAE) snprintf(pulPath, 0x50, "%sstrm/GMB%s.brstm", root, lapSpecifier);
        if(id == 0x0FBC || id == 0x0FBD || id == 0x0FBA || id == 0x0FB9) snprintf(pulPath, 0x50, "%sstrm/GMC%s.brstm", root, lapSpecifier);
        if(id == 0x1234 || id == 0x0FD2 || id == 0x0FD4 || id == 0x0FD6 || id == 0x11C2 || id == 0x0FD1 || id == 0x0FD3 || id == 0x0FD5) snprintf(pulPath, 0x50, "%sstrm/GRR%s.brstm", root, lapSpecifier);
        if(id == 0x0FB6 || id == 0x11CD || id == 0x1160 || id == 0x0FC4 || id == 0x0FC5 || id == 0x0FC6) snprintf(pulPath, 0x50, "%sstrm/GS%s.brstm", root, lapSpecifier);
        if(id == 0x0FDB || id == 0x0FDA) snprintf(pulPath, 0x50, "%sstrm/GPDK%s.brstm", root, lapSpecifier);
        if(id == 0x0FDE || id == 0x0FDF) snprintf(pulPath, 0x50, "%sstrm/GPB%s.brstm", root, lapSpecifier);
        if(id == 0x0FDC || id == 0x113A) snprintf(pulPath, 0x50, "%sstrm/GPW%s.brstm", root, lapSpecifier);
        if(id == 0x0FD9 || id == 0x0FD8) snprintf(pulPath, 0x50, "%sstrm/GPM%s.brstm", root, lapSpecifier);
        if(id == 0x0FDD) snprintf(pulPath, 0x50, "%sstrm/GPP%s.brstm", root, lapSpecifier);
        if(id == 0x0FE0 || id == 0x0FE1) snprintf(pulPath, 0x50, "%sstrm/GPR%s.brstm", root, lapSpecifier);
        if(id == 0x0FE2 || id == 0x0FE3) snprintf(pulPath, 0x50, "%sstrm/GPWL%s.brstm", root, lapSpecifier);
        if(id == 0x0EFB || id == 0x0EFD || id == 0x0EFF || id == 0x0EFC || id == 0x0EFE) snprintf(pulPath, 0x50, "%sstrm/NBB%s.brstm", root, lapSpecifier);
        if(id == 0x0EF6 || id == 0x0EF5) snprintf(pulPath, 0x50, "%sstrm/NBC%s.brstm", root, lapSpecifier);
        if(id == 0x0EE5 || id == 0x0EE4 || id == 0x0EE6 || id == 0x0EE8 || id == 0x0EE7 || id == 0x124E) snprintf(pulPath, 0x50, "%sstrm/NCM%s.brstm", root, lapSpecifier);
        if(id == 0x0EDF || id == 0x0EDE || id == 0x0EDB || id == 0x0EE0 || id == 0x0EDC || id == 0x0EE3 || id == 0x0EE2 || id == 0x0EDD || id == 0x0EE1) snprintf(pulPath, 0x50, "%sstrm/NS%s.brstm", root, lapSpecifier);
        if(id == 0x0ED0 || id == 0x0ED1 || id == 0x0ED5 || id == 0x0ED4 || id == 0x0ED3 || id == 0x0ED2 || id == 0x10C9 || id == 0x10C8) snprintf(pulPath, 0x50, "%sstrm/NKD%s.brstm", root, lapSpecifier);
        if(id == 0x0ECC || id == 0x0DD8 || id == 0x0ECE || id == 0x0474 || id == 0x0ECD || id == 0x0ECF) snprintf(pulPath, 0x50, "%sstrm/NKTB%s.brstm", root, lapSpecifier);
        if(id == 0x0EC8 || id == 0x1157 || id == 0x0EC6 || id == 0x0EC7 || id == 0x07AE || id == 0x0EF0 || id == 0x0EF4 || id == 0x0EEF || id == 0x0EF3 || id == 0x0EF1 || id == 0x0EF2 || id == 0x0EEC || id == 0x0EE9 || id == 0x0EED || id == 0x0EEE || id == 0x0EEA || id == 0x0EEB || id == 0x0F33) snprintf(pulPath, 0x50, "%sstrm/NR%s.brstm", root, lapSpecifier);
        if(id == 0x0EC9 || id == 0x0ECA || id == 0x0ECB || id == 0x0EF7 || id == 0x0EF9 || id == 0x0EF8 || id == 0x0EFA) snprintf(pulPath, 0x50, "%sstrm/NF%s.brstm", root, lapSpecifier);
        if(id == 0x0F06 || id == 0x0F01 || id == 0x0F05 || id == 0x0F00 || id == 0x0F08 || id == 0x0F02 || id == 0x0F04 || id == 0x0F03 || id == 0x0F07) snprintf(pulPath, 0x50, "%sstrm/NRR%s.brstm", root, lapSpecifier);
        if(id == 0x0ED7 || id == 0x0ED9 || id == 0x0EDA || id == 0x0ED8 || id == 0x125F || id == 0x0ED6 || id == 0x0F09) snprintf(pulPath, 0x50, "%sstrm/NTP%s.brstm", root, lapSpecifier);
        if(id == 0x10FB || id == 0x10FA || id == 0x10FD || id == 0x10FC || id == 0x0E50 || id == 0x0E4B || id == 0x0E4F || id == 0x0E4D || id == 0x0E4C || id == 0x0E51 || id == 0x0E4E || id == 0x0E6D || id == 0x0E6F || id == 0x0E6B || id == 0x0E69 || id == 0x0E67 || id == 0x0E6A || id == 0x1166 || id == 0x0E6C || id == 0x0E68 || id == 0x0E6E || id == 0x0EBD || id == 0x0EC5 || id == 0x0EC2 || id == 0x0EC4 || id == 0x0EC3) snprintf(pulPath, 0x50, "%sstrm/SCI%s.brstm", root, lapSpecifier);
        if(id == 0x1109 || id == 0x1232 || id == 0x0E24 || id == 0x0E2C || id == 0x0E2B || id == 0x0E29 || id == 0x0E26 || id == 0x0E27 || id == 0x0E2A || id == 0x0E25 || id == 0x0E28 || id == 0x0EB8 || id == 0x0EB9 || id == 0x0EBA || id == 0x0E57 || id == 0x0E53 || id == 0x0E54 || id == 0x0E56 || id == 0x0E55 || id == 0x0EBB || id == 0x0EBC || id == 0x0E89 || id == 0x0E8C || id == 0x0E8D || id == 0x0E8A || id == 0x0E8B || id == 0x0EC0 || id == 0x0EC1) snprintf(pulPath, 0x50, "%sstrm/SDP%s.brstm", root, lapSpecifier);
        if(id == 0x1105 || id == 0x1107 || id == 0x1106 || id == 0x1104 || id == 0x1137 || id == 0x0E34 || id == 0x0E2F || id == 0x0E2D || id == 0x0E35 || id == 0x0E30 || id == 0x0E31 || id == 0x0E32 || id == 0x0E2E || id == 0x0E33 || id == 0x0E52 || id == 0x0E95 || id == 0x0E96 || id == 0x0E92 || id == 0x0E98 || id == 0x0E93 || id == 0x0E94 || id == 0x0E97) snprintf(pulPath, 0x50, "%sstrm/SGV%s.brstm", root, lapSpecifier);
        if(id == 0x10F8 || id == 0x10F9 || id == 0x0E17 || id == 0x0E1E || id == 0x113F || id == 0x0E20 || id == 0x0E1F || id == 0x0E1D || id == 0x0E16 || id == 0x0E14 || id == 0x0E15 || id == 0x0E22 || id == 0x0E1A || id == 0x0E19 || id == 0x0E21 || id == 0x0E23 || id == 0x0E1C || id == 0x0E18 || id == 0x0E1B || id == 0x0E45 || id == 0x0E46 || id == 0x0E4A || id == 0x0E3F || id == 0x0E48 || id == 0x0E40 || id == 0x0E44 || id == 0x0E41 || id == 0x0E47 || id == 0x0E49 || id == 0x0E42 || id == 0x0E43 || id == 0x0E60 || id == 0x0E5F || id == 0x0E62 || id == 0x0E61 || id == 0x0E85 || id == 0x0E87 || id == 0x0E82 || id == 0x0E88 || id == 0x0E83|| id == 0x0E86 || id == 0x0E84) snprintf(pulPath, 0x50, "%sstrm/SMC%s.brstm", root, lapSpecifier);
        if(id == 0x0E38 || id == 0x0E37 || id == 0x0E3E || id == 0x0E3A || id == 0x0E3B || id == 0x12AC || id == 0x0E36 || id == 0x0E3D || id == 0x0E39 || id == 0x0E3C || id == 0x11E3 || id == 0x0E5B || id == 0x0E59 || id == 0x0E5E || id == 0x11D5 || id == 0x0E5D || id == 0x0E5C || id == 0x0E58 || id == 0x0E5A || id == 0x11E0 || id == 0x0E7E || id == 0x0E7C || id == 0x0E79 || id == 0x0E81 || id == 0x120A || id == 0x0E7D || id == 0x0E7B || id == 0x0E7A || id == 0x0E7F || id == 0x0E78 || id == 0x0E80) snprintf(pulPath, 0x50, "%sstrm/SBC%s.brstm", root, lapSpecifier);
        if(id == 0x0E63 || id == 0x0E65 || id == 0x0E64 || id == 0x0E66 || id == 0x0E90 || id == 0x0E8F || id == 0x0E8E || id == 0x0E91) snprintf(pulPath, 0x50, "%sstrm/SKB%s.brstm", root, lapSpecifier);
        if(id == 0x10FE || id == 0x10FF || id == 0x1100 || id == 0x0EAF || id == 0x11AA || id == 0x0EA8 || id == 0x0EA3 || id == 0x0EAB || id == 0x0EB2 || id == 0x0EB4 || id == 0x0EA2 || id == 0x0EA9 || id == 0x0EAC || id == 0x121F || id == 0x0EA1 || id == 0x0EAA || id == 0x0EA4 || id == 0x0EB5 || id == 0x0EB6 || id == 0x0EB3 || id == 0x0A16 || id == 0x0EAE || id == 0x0EAD || id == 0x0EA5 || id == 0x0EB0 || id == 0x0EB1 || id == 0x0EA6 || id == 0x0EA7 || id == 0x0FCA || id == 0x139A) snprintf(pulPath, 0x50, "%sstrm/SRR%s.brstm", root, lapSpecifier);
        if(id == 0x1269 || id == 0x1102 || id == 0x1101 || id == 0x1103 || id == 0x0E77 || id == 0x0E70 || id == 0x0E72 || id == 0x0E74 || id == 0x0E73 || id == 0x0E71 || id == 0x0E75 || id == 0x0E76 || id == 0x0EBE || id == 0x0EBF || id == 0x0E9D || id == 0x0E99 || id == 0x0E9E || id == 0x0E9B || id == 0x0E9C || id == 0x0E9A || id == 0x0EA0 || id == 0x0E9F) snprintf(pulPath, 0x50, "%sstrm/SVL%s.brstm", root, lapSpecifier);
        if(id == 0x1138 || id == 0x109D || id == 0x109E) snprintf(pulPath, 0x50, "%sstrm/SSW%s.brstm", root, lapSpecifier);
        if(id == 0x10A0 || id == 0x10A1 || id == 0x10A2) snprintf(pulPath, 0x50, "%sstrm/SSCS%s.brstm", root, lapSpecifier);
        if(id == 0x109F) snprintf(pulPath, 0x50, "%sstrm/SYI%s.brstm", root, lapSpecifier);
        if(id == 0x10DF || id == 0x10E1 || id == 0x10E0 || id == 0x10E2) snprintf(pulPath, 0x50, "%sstrm/TAD%s.brstm", root, lapSpecifier);
        if(id == 0x10EC || id == 0x10EB || id == 0x10EA || id == 0x10EE || id == 0x10ED || id == 0x10EF) snprintf(pulPath, 0x50, "%sstrm/TATD%s.brstm", root, lapSpecifier);
        if(id == 0x10E3 || id == 0x10E4 || id == 0x10E5 || id == 0x10E6) snprintf(pulPath, 0x50, "%sstrm/TBR%s.brstm", root, lapSpecifier);
        if(id == 0x10D1 || id == 0x1122 || id == 0x10D2 || id == 0x10D4 || id == 0x10D3 || id == 0x10D5) snprintf(pulPath, 0x50, "%sstrm/TBB%s.brstm", root, lapSpecifier);
        if(id == 0x10BE || id == 0x10BF || id == 0x1146 || id == 0x10BD || id == 0x10C1 || id == 0x1147 || id == 0x10C0 || id == 0x10C3 || id == 0x1148 || id == 0x10C2) snprintf(pulPath, 0x50, "%sstrm/TLL%s.brstm", root, lapSpecifier);
        if(id == 0x1126 || id == 0x10CB || id == 0x10CA || id == 0x10CD || id == 0x10CC || id == 0x10CF || id == 0x10CE) snprintf(pulPath, 0x50, "%sstrm/TLAL%s.brstm", root, lapSpecifier);
        if(id == 0x10F4 || id == 0x10F5 || id == 0x10F6 || id == 0x10F7) snprintf(pulPath, 0x50, "%sstrm/TMD%s.brstm", root, lapSpecifier);
        if(id == 0x10D0) snprintf(pulPath, 0x50, "%sstrm/TMM%s.brstm", root, lapSpecifier);
        if(id == 0x10A5 || id == 0x10A6 || id == 0x10A8 || id == 0x10A7 || id == 0x10AA || id == 0x10A9 || id == 0x10AC || id == 0x10AB) snprintf(pulPath, 0x50, "%sstrm/TNYM%s.brstm", root, lapSpecifier);
        if(id == 0x10D6 || id == 0x10D7) snprintf(pulPath, 0x50, "%sstrm/TNH%s.brstm", root, lapSpecifier);
        if(id == 0x10B8 || id == 0x10B7 || id == 0x10B6 || id == 0x10BA || id == 0x10B9 || id == 0x10BC || id == 0x10BB) snprintf(pulPath, 0x50, "%sstrm/TPP%s.brstm", root, lapSpecifier);
        if(id == 0x10E7 || id == 0x1120 || id == 0x10E8 || id == 0x10E9) snprintf(pulPath, 0x50, "%sstrm/TPPC%s.brstm", root, lapSpecifier);
        if(id == 0x10F3) snprintf(pulPath, 0x50, "%sstrm/TPPP%s.brstm", root, lapSpecifier);
        if(id == 0x10F0 || id == 0x10F1 || id == 0x10F2) snprintf(pulPath, 0x50, "%sstrm/TRA%s.brstm", root, lapSpecifier);
        if(id == 0x10DC || id == 0x10DB || id == 0x10DD || id == 0x10DE) snprintf(pulPath, 0x50, "%sstrm/TSS%s.brstm", root, lapSpecifier);
        if(id == 0x10D8 || id == 0x10D9 || id == 0x10DA) snprintf(pulPath, 0x50, "%sstrm/TSYS%s.brstm", root, lapSpecifier);
        if(id == 0x10AF || id == 0x10AE || id == 0x10AD || id == 0x10B1 || id == 0x10B0 || id == 0x10B3 || id == 0x10B2 || id == 0x10B5 || id == 0x10B4) snprintf(pulPath, 0x50, "%sstrm/TTB%s.brstm", root, lapSpecifier);
        if(id == 0x112A || id == 0x112A || id == 0x10C4 || id == 0x10C5 || id == 0x10C6 || id == 0x10C7) snprintf(pulPath, 0x50, "%sstrm/TVV%s.brstm", root, lapSpecifier);
        if(id == 0x112F) snprintf(pulPath, 0x50, "%sstrm/WDKS%s.brstm", root, lapSpecifier);
        if(id == 0x1327) snprintf(pulPath, 0x50, "%sstrm/WRR%s.brstm", root, lapSpecifier);
        if(id == 0x1096 || id == 0x1097) snprintf(pulPath, 0x50, "%sstrm/WACSP%s.brstm", root, lapSpecifier);
        if(id == 0x1099) snprintf(pulPath, 0x50, "%sstrm/WACA%s.brstm", root, lapSpecifier);
        if(id == 0x1098) snprintf(pulPath, 0x50, "%sstrm/WACS%s.brstm", root, lapSpecifier);
        if(id == 0x109A) snprintf(pulPath, 0x50, "%sstrm/WACW%s.brstm", root, lapSpecifier);
        if(id == 0x109C || id == 0x12A7) snprintf(pulPath, 0x50, "%sstrm/WBB%s.brstm", root, lapSpecifier);
        if(id == 0x1089 || id == 0x120B || id == 0x108A) snprintf(pulPath, 0x50, "%sstrm/WBDD%s.brstm", root, lapSpecifier);
        if(id == 0x108B || id == 0x108C || id == 0x139B) snprintf(pulPath, 0x50, "%sstrm/WBC%s.brstm", root, lapSpecifier);
        if(id == 0x1088 || id == 0x1398) snprintf(pulPath, 0x50, "%sstrm/WCC%s.brstm", root, lapSpecifier);
        if(id == 0x1084 || id == 0x1083) snprintf(pulPath, 0x50, "%sstrm/WDS%s.brstm", root, lapSpecifier);
        if(id == 0x1090) snprintf(pulPath, 0x50, "%sstrm/WDD%s.brstm", root, lapSpecifier);
        if(id == 0x1085) snprintf(pulPath, 0x50, "%sstrm/WE%s.brstm", root, lapSpecifier);
        if(id == 0x108F || id == 0x108E || id == 0x129F) snprintf(pulPath, 0x50, "%sstrm/WEA%s.brstm", root, lapSpecifier);
        if(id == 0x1093 || id == 0x1094) snprintf(pulPath, 0x50, "%sstrm/WHC%s.brstm", root, lapSpecifier);
        if(id == 0x1092) snprintf(pulPath, 0x50, "%sstrm/WIIO%s.brstm", root, lapSpecifier);
        if(id == 0x107A || id == 0x107B) snprintf(pulPath, 0x50, "%sstrm/WMC%s.brstm", root, lapSpecifier);
        if(id == 0x1072 || id == 0x1071 || id == 0x123A) snprintf(pulPath, 0x50, "%sstrm/WMKS%s.brstm", root, lapSpecifier);
        if(id == 0x121D || id == 0x1087 || id == 0x1086) snprintf(pulPath, 0x50, "%sstrm/WMW%s.brstm", root, lapSpecifier);
        if(id == 0x1188 || id == 0x1091) snprintf(pulPath, 0x50, "%sstrm/WMUC%s.brstm", root, lapSpecifier);
        if(id == 0x108D) snprintf(pulPath, 0x50, "%sstrm/WURR%s.brstm", root, lapSpecifier);
        if(id == 0x107F || id == 0x1081 || id == 0x1080) snprintf(pulPath, 0x50, "%sstrm/WSGF%s.brstm", root, lapSpecifier);
        if(id == 0x1082) snprintf(pulPath, 0x50, "%sstrm/WSA%s.brstm", root, lapSpecifier);
        if(id == 0x109B) snprintf(pulPath, 0x50, "%sstrm/WSBS%s.brstm", root, lapSpecifier);
        if(id == 0x1233 || id == 0x1075 || id == 0x1076) snprintf(pulPath, 0x50, "%sstrm/WSSC%s.brstm", root, lapSpecifier);
        if(id == 0x1077 || id == 0x1078 || id == 0x1079) snprintf(pulPath, 0x50, "%sstrm/WTR%s.brstm", root, lapSpecifier);
        if(id == 0x107D || id == 0x107C || id == 0x123E) snprintf(pulPath, 0x50, "%sstrm/WTH%s.brstm", root, lapSpecifier);
        if(id == 0x107E) snprintf(pulPath, 0x50, "%sstrm/WTM%s.brstm", root, lapSpecifier);
        if(id == 0x1074 || id == 0x1073) snprintf(pulPath, 0x50, "%sstrm/WWP%s.brstm", root, lapSpecifier);
        if(id == 0x1095) snprintf(pulPath, 0x50, "%sstrm/WWW%s.brstm", root, lapSpecifier);
        if(U16_MISSION_MODE_FIX == 0x0001) snprintf(pulPath, 0x50, "%sstrm/MR%s.brstm", root, lapSpecifier);
        U32_TEST_IDS = id;
        ret = DVD::ConvertPathToEntryNum(pulPath);
    }
    return ret;
}

nw4r::ut::FileStream* MusicSlotsExpand(nw4r::snd::DVDSoundArchive* archive, void* buffer, int size,
    const char* extFilePath, u32 r7, u32 length) {

    const char firstChar = extFilePath[0xC];
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const PulsarId track = cupsConfig->GetWinning();

    if(U8_BRSTMS == 0x01 || U16_MISSION_MODE_FIX == 0x0001) {
        if((firstChar == 'n' || firstChar == 'S' || firstChar == 'r')) {
        const SectionId section = SectionMgr::sInstance->curSection->sectionId;
        register SoundIDs toPlayId;
        asm(mr toPlayId, r20;);
        const char* customBGPath = nullptr;
        if(toPlayId == SOUND_ID_KC) { //files are guaranteed to exist because it's been checked before
            if(section >= SECTION_MAIN_MENU_FROM_BOOT && section <= SECTION_MAIN_MENU_FROM_LICENSE) customBGPath = titleMusicFile;
            else if(section >= SECTION_SINGLE_P_FROM_MENU && section <= SECTION_SINGLE_P_LIST_RACE_GHOST || section == SECTION_LOCAL_MULTIPLAYER) customBGPath = offlineMusicFile;
            else if(section >= SECTION_P1_WIFI && section <= SECTION_P2_WIFI_FROOM_COIN_VOTING) customBGPath = wifiMusicFile;
        }
        if(customBGPath != nullptr) extFilePath = customBGPath;
        else if(!CupsConfig::IsReg(track)) {
            bool isFinalLap = false;
            register u32 strLength;
            asm(mr strLength, r28;);
            const char finalChar = extFilePath[strLength];
            if(finalChar == 'f' || finalChar == 'F') isFinalLap = true;

            bool found = false;
            const u8 variantIdx = cupsConfig->GetCurVariantIdx();
            if(CheckBRSTM(archive, track, variantIdx, isFinalLap) >= 0) found = true;
            else if(isFinalLap) {
                if(CheckBRSTM(archive, track, variantIdx, false) >= 0) found = true;
                if(found) Audio::Manager::sInstance->soundArchivePlayer->soundPlayerArray->soundList.GetFront().ambientParam.pitch = 1.1f;
            }
            if(found) extFilePath = pulPath;
        }
    }
    }
    return archive->OpenExtStream(buffer, size, extFilePath, 0, length);
}
kmCall(0x8009e0e4, MusicSlotsExpand);

}//namespace Sound
}//namespace Pulsar