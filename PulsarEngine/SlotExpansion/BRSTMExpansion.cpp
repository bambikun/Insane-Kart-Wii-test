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
    const char* soundName = "0";
    s32 ret = -1;
    char trackName[0x100];
    UI::GetTrackBMG(trackName, id);
    snprintf(pulPath, 0x100, "%sstrm/%s%s.brstm", root, trackName, lapSpecifier);
    ret = DVD::ConvertPathToEntryNum(pulPath);
    if(ret < 0) {
        u32 variantIdx = CupsConfig::sInstance->GetCurVariantIdx();
        if(variantIdx == 0) snprintf(pulPath, 0x50, "%sstrm/%d%s.brstm", root, CupsConfig::ConvertTrack_PulsarIdToRealId(id), lapSpecifier);
        //else snprintf(pulPath, 0x50, "%sstrm/%d_%d%s.brstm", root, CupsConfig::ConvertTrack_PulsarIdToRealId(id), variantIdx, lapSpecifier);

    switch(id) {
        case 0x1066:
        case 0x1067:
        case 0x1068:
        soundName = "3BC"; 
        break;

        case 0x1042:
        case 0x1041:
        case 0x1040: 
        soundName = "3CCL"; 
        break;

        case 0x103E:
        case 0x103D:
        case 0x103F:
        soundName = "3DH";
        break;

        case 0x1060:
        case 0x124A:
        case 0x1061:
        case 0x105D:
        case 0x105E:
        case 0x105F:
        soundName = "3DKJ";
        break;

        case 0x1176:
        case 0x105C:
        case 0x1048:
        case 0x1046:
        case 0x13B0:
        soundName = "3W";
        break;

        case 0x104C:
        case 0x1049:
        case 0x104A:
        case 0x104D:
        case 0x104B:
        case 0x103B:
        case 0x103C:
        case 0x1039:
        case 0x103A:
        soundName = "3C";
        break;

        case 0x104E:
        case 0x1050:
        case 0x104F:
        soundName = "3MP";
        break;

        case 0x105A:
        case 0x12F0:
        case 0x119D:
        case 0x105B:
        soundName = "3NBC";
        break;

        case 0x1056:
        case 0x1055:
        case 0x099B:
        case 0x11CA:
        soundName = "3PPS";
        break;

        case 0x1069:
        case 0x106A:
        case 0x106B:
        case 0x106E:
        case 0x106D:
        case 0x106C:
        case 0x1390:
        soundName = "3RR";
        break;

        case 0x1051:
        case 0x1052:
        case 0x1054:
        case 0x1053:
        soundName = "3RRM";
        break;

        case 0x1065:
        case 0x09BF:
        case 0x1062:
        case 0x1063:
        case 0x1064:
        case 0x1237:
        soundName = "3RIW";
        break;

        case 0x1043:
        case 0x1044:
        soundName = "3SGB";
        break;

        case 0x1057:
        case 0x1058:
        case 0x1059:
        case 0x13AF:
        soundName = "3WS";
        break;

        case 0x1010:
        case 0x1012:
        case 0x1014:
        case 0x1011:
        case 0x1013:
        case 0x13AC:
        case 0x1355:
        soundName = "DAF";
        break;

        case 0x1132:
        case 0x1020:
        case 0x101E:
        case 0x101F:
        case 0x1021:
        soundName = "DBC";
        break;

        case 0x0FED:
        case 0x1163:
        case 0x0FEC:
        case 0x0FEA:
        case 0x0FEE:
        case 0x0FEB:
        case 0x0FEF:
        case 0x1115:
        case 0x1028:
        case 0x1029:
        case 0x120C:
        soundName = "DCCB";
        break;

        case 0x1116:
        soundName = "DDS";

        break;
        case 0x1001:
        case 0x1002:
        case 0x1003:
        case 0x1004:
        case 0x102E:
        soundName = "DDKP";
        break;

        case 0x1032:
        case 0x1031:
        case 0x102F:
        case 0x1030:
        soundName = "DDC";
        break;

        case 0x0FE9:
        case 0x0FE5:
        case 0x0FE4:
        case 0x0FE6:
        case 0x0FE8:
        case 0x0FE7:
        case 0x100D:
        case 0x100F:
        case 0x1009:
        case 0x100E:
        case 0x100B:
        case 0x100A:
        case 0x100C:
        case 0x1117:
        case 0x138D:
        case 0x13C1:
        case 0x13E1:
        soundName = "DC";
        break;

        case 0x102C:
        case 0x102B:
        case 0x0FF4:
        case 0x0FF7:
        case 0x0FF5:
        case 0x0FF8:
        case 0x0FF9:
        case 0x0FF6:
        case 0x0FFA:
        case 0x102D:
        case 0x1136:
        case 0x1019:
        case 0x101C:
        case 0x1015:
        case 0x101B:
        case 0x1018:
        case 0x1017:
        case 0x1016:
        case 0x101A:
        soundName = "DS";
        break;

        case 0x0FF0:
        case 0x11BD:
        case 0x0FF2:
        case 0x0FF1:
        case 0x0FF3:
        soundName = "DLM";
        break;

        case 0x101D:
        soundName = "DPG";
        break;

        case 0x1026:
        case 0x1027:
        case 0x1023:
        case 0x1022:
        case 0x1024:
        case 0x1025:
        soundName = "DRR";
        break;

        case 0x0FFD:
        case 0x1000:
        case 0x0FFC:
        case 0x0FFF:
        case 0x0FFB:
        case 0x0FFE:
        soundName = "DSR";
        break;

        case 0x1006:
        case 0x1005:
        case 0x1270:
        case 0x1007:
        case 0x1008:
        case 0x0B88:
        soundName = "DTTC";
        break;

        case 0x0F2F:
        case 0x0F2E:
        case 0x0F30:
        case 0x125A:
        case 0x0F31:
        case 0x0F7F:
        case 0x125B:
        case 0x0F80:
        case 0x0F81:
        soundName = "GBO";
        break;

        case 0x0F26:
        case 0x0F27:
        case 0x0F23:
        case 0x0F28:
        case 0x1298:
        case 0x0F22:
        case 0x0F24:
        case 0x0F25:
        case 0x0F3C:
        case 0x0F3E:
        case 0x0F3B:
        case 0x0F3A:
        case 0x0F40:
        case 0x0F3D:
        case 0x0F39:
        case 0x0F3F:
        case 0x0F76:
        case 0x12B0:
        case 0x0F84:
        case 0x0F85:
        case 0x0F88:
        case 0x0F87:
        case 0x0F86:
        case 0x0F82:
        case 0x0F83:
        case 0x1108:
        case 0x129E:
        case 0x13B7:
        case 0x13E0:
        soundName = "GBBC";
        break;

        case 0x0F5A:
        case 0x0F5C:
        case 0x0F60:
        case 0x0F5D:
        case 0x0F5B:
        case 0x0F5F:
        case 0x0F5E:
        case 0x12FD:
        case 0x0F1A:
        case 0x0F1B:
        case 0x1347:
        soundName = "GBW";
        break;

        case 0x0F34:
        case 0x0F32:
        case 0x0F38:
        case 0x0F37:
        case 0x0F35:
        case 0x0F36:
        soundName = "GBCL";
        break;

        case 0x0F78:
        case 0x0F79:
        case 0x0F7E:
        case 0x0F7D:
        case 0x0F7A:
        case 0x05E2:
        case 0x0F77:
        case 0x0F7B:
        case 0x0F7C:
        soundName = "GBLP";
        break;

        case 0x0F48:
        case 0x0F46:
        case 0x0F47:
        case 0x0F45:
        case 0x0F41:
        case 0x0F49:
        case 0x0F42:
        case 0x0F43:
        case 0x0F44:
        case 0x0F2D:
        case 0x0F2B:
        case 0x0F2A:
        case 0x0F29:
        case 0x0F2C:
        case 0x0F10:
        case 0x0F16:
        case 0x0F0D:
        case 0x0F0A:
        case 0x0F0F:
        case 0x0F18:
        case 0x0F11:
        case 0x0F19:
        case 0x0F17:
        case 0x0F15:
        case 0x0F0E:
        case 0x0F0C:
        case 0x0F0B:
        case 0x0F13:
        case 0x0F14:
        case 0x0F12:
        soundName = "GBC";
        break;

        case 0x0F94:
        case 0x0F8B:
        case 0x0F91:
        case 0x0F93:
        case 0x0F8E:
        case 0x0F8C:
        case 0x0F89:
        case 0x0F8A:
        case 0x0F8F:
        case 0x0F95:
        case 0x0F90:
        case 0x0F8D:
        case 0x0F92:
        soundName = "GBRR";
        break;

        case 0x0F6F:
        case 0x0F70:
        case 0x0F6E:
        case 0x0F71:
        case 0x1210:
        soundName = "GBRIR";
        break;

        case 0x0F1D:
        case 0x0F1E:
        case 0x0F1F:
        case 0x0F1C:
        case 0x0F21:
        case 0x0F20:
        soundName = "GBRP";
        break;

        case 0x0F4F:
        case 0x11A1:
        case 0x0F50:
        case 0x0F53:
        case 0x0F4E:
        case 0x0F4D:
        case 0x0F4B:
        case 0x0F58:
        case 0x0F59:
        case 0x0F55:
        case 0x0F4A:
        case 0x0F56:
        case 0x0F51:
        case 0x0F54:
        case 0x0F57:
        case 0x0F4C:
        case 0x0F52:
        case 0x1430:
        soundName = "GBSG";
        break;

        case 0x0F68:
        case 0x0F6B:
        case 0x0F69:
        case 0x0CC7:
        case 0x0F6D:
        case 0x0F6C:
        case 0x0F67:
        case 0x119F:
        case 0x0F6A:
        soundName = "GBSL";
        break;

        case 0x0F62:
        case 0x0F63:
        case 0x0F64:
        case 0x0F61:
        case 0x0F66:
        case 0x0F65:
        case 0x0CC5:
        soundName = "GBSW";
        break;

        case 0x0F74:
        case 0x0F72:
        case 0x0F73:
        case 0x0F75:
        case 0x1441:
        soundName = "GBYD";
        break;

        case 0x0F9E:
        case 0x119E:
        case 0x0909:
        case 0x0FA1:
        case 0x0F9F:
        case 0x126A:
        case 0x0FA3:
        case 0x0FA0:
        case 0x0FA2:
        case 0x0FA5:
        case 0x0FA4:
        case 0x13CD:
        soundName = "GBP";
        break;

        case 0x0FCE:
        case 0x1178:
        case 0x0FCF:
        case 0x0FD0:
        soundName = "GBSC";
        break;

        case 0x0FB4:
        case 0x0FB2:
        case 0x0FB3:
        case 0x0FB5:
        soundName = "GW";
        break;

        case 0x0FD7:
        case 0x0FB8:
        case 0x0FB7:
        soundName = "GSL";
        break;

        case 0x0FC8:
        case 0x0FC7:
        case 0x0FC9:
        case 0x0FCB:
        case 0x0FCC:
        case 0x0FCD:
        soundName = "GM";
        break;

        case 0x0FAA:
        case 0x0FA7:
        case 0x0FA8:
        case 0x0FA6:
        case 0x0FAB:
        case 0x0FA9:
        soundName = "GDDD";
        break;

        case 0x0F97:
        case 0x11AD:
        case 0x0F99:
        case 0x0F9A:
        case 0x0F9D:
        case 0x0F9B:
        case 0x0F98:
        case 0x0F9C:
        case 0x0FB1:
        case 0x0FB0:
        case 0x0FC1:
        case 0x0FC0:
        case 0x0FBF:
        case 0x0FBE:
        case 0x0FC2:
        case 0x0FC3:
        case 0x13AB:
        soundName = "GC";
        break;

        case 0x1192:
        case 0x0FAF:
        case 0x0FAD:
        case 0x0FAC:
        case 0x0FAE:
        soundName = "GMB";
        break;

        case 0x0FBC:
        case 0x0FBD:
        case 0x0FBA:
        case 0x0FB9:
        soundName = "GMC";
        break;

        case 0x1234:
        case 0x0FD2:
        case 0x0FD4:
        case 0x0FD6:
        case 0x11C2:
        case 0x0FD1:
        case 0x0FD3:
        case 0x0FD5:
        soundName = "GRR";
        break;

        case 0x0FB6:
        case 0x11CD:
        case 0x1160:
        case 0x0FC4:
        case 0x0FC5:
        case 0x0FC6:
        soundName = "GS";
        break;

        case 0x0FDB:
        case 0x0FDA:
        soundName = "GPDK";
        break;

        case 0x0FDE:
        case 0x0FDF:
        soundName = "GPB";
        break;

        case 0x0FDC:
        case 0x113A:
        soundName = "GPW";
        break;

        case 0x0FD9:
        case 0x0FD8:
        soundName = "GPM";
        break;

        case 0x0FDD:
        soundName = "GPP";
        break;

        case 0x0FE0:
        case 0x0FE1:
        soundName = "GPR";
        break;

        case 0x0FE2:
        case 0x0FE3:
        soundName = "GPWL";
        break;

        case 0x0EFB:
        case 0x0EFD:
        case 0x0EFF:
        case 0x0EFC:
        case 0x0EFE:
        soundName = "NBB";
        break;

        case 0x0EF6:
        case 0x0EF5:
        soundName = "NBC";
        break;

        case 0x0EE5:
        case 0x0EE4:
        case 0x0EE6:
        case 0x0EE8:
        case 0x0EE7:
        case 0x124E:
        soundName = "NCM";
        break;

        case 0x0EDF:
        case 0x0EDE:
        case 0x0EDB:
        case 0x0EE0:
        case 0x0EDC:
        case 0x0EE3:
        case 0x0EE2:
        case 0x0EDD:
        case 0x0EE1:
        soundName = "NS";
        break;

        case 0x0ED0:
        case 0x0ED1:
        case 0x0ED5:
        case 0x0ED4:
        case 0x0ED3:
        case 0x0ED2:
        case 0x10C9:
        case 0x10C8:
        soundName = "NKD";
        break;

        case 0x0ECC:
        case 0x0DD8:
        case 0x0ECE:
        case 0x0474:
        case 0x0ECD:
        case 0x0ECF:
        soundName = "NKTB";
        break;

        case 0x0EC8:
        case 0x1157:
        case 0x0EC6:
        case 0x0EC7:
        case 0x07AE:
        case 0x0EF0:
        case 0x0EF4:
        case 0x0EEF:
        case 0x0EF3:
        case 0x0EF1:
        case 0x0EF2:
        case 0x0EEC:
        case 0x0EE9:
        case 0x0EED:
        case 0x0EEE:
        case 0x0EEA:
        case 0x0EEB:
        case 0x0F33:
        soundName = "NR";
        break;

        case 0x0EC9:
        case 0x0ECA:
        case 0x0ECB:
        case 0x0EF7:
        case 0x0EF9:
        case 0x0EF8:
        case 0x0EFA:
        soundName = "NF";
        break;

        case 0x0F06:
        case 0x0F01:
        case 0x0F05:
        case 0x0F00:
        case 0x0F08:
        case 0x0F02:
        case 0x0F04:
        case 0x0F03:
        case 0x0F07:
        soundName = "NRR";
        break;

        case 0x0ED7:
        case 0x0ED9:
        case 0x0EDA:
        case 0x0ED8:
        case 0x125F:
        case 0x0ED6:
        case 0x0F09:
        soundName = "NTP";
        break;

        case 0x10FB:
        case 0x10FA:
        case 0x10FD:
        case 0x10FC:
        case 0x0E50:
        case 0x0E4B:
        case 0x0E4F:
        case 0x0E4D:
        case 0x0E4C:
        case 0x0E51:
        case 0x0E4E:
        case 0x0E6D:
        case 0x0E6F:
        case 0x0E6B:
        case 0x0E69:
        case 0x0E67:
        case 0x0E6A:
        case 0x1166:
        case 0x0E6C:
        case 0x0E68:
        case 0x0E6E:
        case 0x0EBD:
        case 0x0EC5:
        case 0x0EC2:
        case 0x0EC4:
        case 0x0EC3:
        soundName = "SCI";
        break;

        case 0x1109:
        case 0x1232:
        case 0x0E24:
        case 0x0E2C:
        case 0x0E2B:
        case 0x0E29:
        case 0x0E26:
        case 0x0E27:
        case 0x0E2A:
        case 0x0E25:
        case 0x0E28:
        case 0x0EB8:
        case 0x0EB9:
        case 0x0EBA:
        case 0x0E57:
        case 0x0E53:
        case 0x0E54:
        case 0x0E56:
        case 0x0E55:
        case 0x0EBB:
        case 0x0EBC:
        case 0x0E89:
        case 0x0E8C:
        case 0x0E8D:
        case 0x0E8A:
        case 0x0E8B:
        case 0x0EC0:
        case 0x0EC1:
        soundName = "SDP";
        break;

        case 0x1105:
        case 0x1107:
        case 0x1106:
        case 0x1104:
        case 0x1137:
        case 0x0E34:
        case 0x0E2F:
        case 0x0E2D:
        case 0x0E35:
        case 0x0E30:
        case 0x0E31:
        case 0x0E32:
        case 0x0E2E:
        case 0x0E33:
        case 0x0E52:
        case 0x0E95:
        case 0x0E96:
        case 0x0E92:
        case 0x0E98:
        case 0x0E93:
        case 0x0E94:
        case 0x0E97:
        soundName = "SGV";
        break;

        case 0x10F8:
        case 0x10F9:
        case 0x0E17:
        case 0x0E1E:
        case 0x113F:
        case 0x0E20:
        case 0x0E1F:
        case 0x0E1D:
        case 0x0E16:
        case 0x0E14:
        case 0x0E15:
        case 0x0E22:
        case 0x0E1A:
        case 0x0E19:
        case 0x0E21:
        case 0x0E23:
        case 0x0E1C:
        case 0x0E18:
        case 0x0E1B:
        case 0x0E45:
        case 0x0E46:
        case 0x0E4A:
        case 0x0E3F:
        case 0x0E48:
        case 0x0E40:
        case 0x0E44:
        case 0x0E41:
        case 0x0E47:
        case 0x0E49:
        case 0x0E42:
        case 0x0E43:
        case 0x0E60:
        case 0x0E5F:
        case 0x0E62:
        case 0x0E61:
        case 0x0E85:
        case 0x0E87:
        case 0x0E82:
        case 0x0E88:
        case 0x0E83:
        case 0x0E86:
        case 0x0E84:
        soundName = "SMC";
        break;

        case 0x0E38:
        case 0x0E37:
        case 0x0E3E:
        case 0x0E3A:
        case 0x0E3B:
        case 0x12AC:
        case 0x0E36:
        case 0x0E3D:
        case 0x0E39:
        case 0x0E3C:
        case 0x11E3:
        case 0x0E5B:
        case 0x0E59:
        case 0x0E5E:
        case 0x11D5:
        case 0x0E5D:
        case 0x0E5C:
        case 0x0E58:
        case 0x0E5A:
        case 0x11E0:
        case 0x0E7E:
        case 0x0E7C:
        case 0x0E79:
        case 0x0E81:
        case 0x120A:
        case 0x0E7D:
        case 0x0E7B:
        case 0x0E7A:
        case 0x0E7F:
        case 0x0E78:
        soundName = "SBC";
        break;

        case 0x0E63:
        case 0x0E65:
        case 0x0E64:
        case 0x0E66:
        case 0x0E90:
        case 0x0E8F:
        case 0x0E8E:
        case 0x0E91:
        soundName = "SKB";
        break;

        case 0x10FE:
        case 0x10FF:
        case 0x1100:
        case 0x0EAF:
        case 0x11AA:
        case 0x0EA8:
        case 0x0EA3:
        case 0x0EAB:
        case 0x0EB2:
        case 0x0EB4:
        case 0x0EA2:
        case 0x0EA9:
        case 0x0EAC:
        case 0x121F:
        case 0x0EA1:
        case 0x0EAA:
        case 0x0EA4:
        case 0x0EB5:
        case 0x0EB6:
        case 0x0EB3:
        case 0x0A16:
        case 0x0EAE:
        case 0x0EAD:
        case 0x0EA5:
        case 0x0EB0:
        case 0x0EB1:
        case 0x0EA6:
        case 0x0EA7:
        case 0x0FCA:
        case 0x139A:
        soundName = "SRR";
        break;

        case 0x1269:
        case 0x1102:
        case 0x1101:
        case 0x1103:
        case 0x0E77:
        case 0x0E70:
        case 0x0E72:
        case 0x0E74:
        case 0x0E73:
        case 0x0E71:
        case 0x0E75:
        case 0x0E76:
        case 0x0EBE:
        case 0x0EBF:
        case 0x0E9D:
        case 0x0E99:
        case 0x0E9E:
        case 0x0E9B:
        case 0x0E9C:
        case 0x0E9A:
        case 0x0EA0:
        case 0x0E9F:
        soundName = "SVL";
        break;

        case 0x1138:
        case 0x109D:
        case 0x109E:
        soundName = "SSW";
        break;

        case 0x10A0:
        case 0x10A1:
        case 0x10A2:
        soundName = "SSCS";
        break;

        case 0x109F:
        soundName = "SYI";
        break;

        case 0x10DF:
        case 0x10E1:
        case 0x10E0:
        case 0x10E2:
        soundName = "TAD";
        break;

        case 0x10EC:
        case 0x10EB:
        case 0x10EA:
        case 0x10EE:
        case 0x10ED:
        case 0x10EF:
        soundName = "TATD";
        break;

        case 0x10E3:
        case 0x10E4:
        case 0x10E5:
        case 0x10E6:
        soundName = "TBR";
        break;

        case 0x10D1:
        case 0x1122:
        case 0x10D2:
        case 0x10D4:
        case 0x10D3:
        case 0x10D5:
        soundName = "TBB";
        break;

        case 0x10BE:
        case 0x10BF:
        case 0x1146:
        case 0x10BD:
        case 0x10C1:
        case 0x1147:
        case 0x10C0:
        case 0x10C3:
        case 0x1148:
        case 0x10C2:
        soundName = "TLL";
        break;

        case 0x1126:
        case 0x10CB:
        case 0x10CA:
        case 0x10CD:
        case 0x10CC:
        case 0x10CF:
        case 0x10CE:
        soundName = "TLAL";
        break;

        case 0x10F4:
        case 0x10F5:
        case 0x10F6:
        case 0x10F7:
        soundName = "TMD";
        break;

        case 0x10D0:
        soundName = "TMM";
        break;

        case 0x10A5:
        case 0x10A6:
        case 0x10A8:
        case 0x10A7:
        case 0x10AA:
        case 0x10A9:
        case 0x10AC:
        case 0x10AB:
        soundName = "TNYM";
        break;

        case 0x10D6:
        case 0x10D7:
        soundName = "TNH";
        break;

        case 0x10B8:
        case 0x10B7:
        case 0x10B6:    
        case 0x10BA:
        case 0x10B9:
        case 0x10BC:
        case 0x10BB:
        soundName = "TPP";
        break;

        case 0x10E7:
        case 0x1120:
        case 0x10E8:
        case 0x10E9:
        soundName = "TPPC";
        break;

        case 0x10F3:
        soundName = "TPPP";
        break;

        case 0x10F0:
        case 0x10F1:
        case 0x10F2:
        soundName = "TRA";
        break;

        case 0x10DC:
        case 0x10DB:
        case 0x10DD:
        case 0x10DE:
        soundName = "TSS";
        break;

        case 0x10D8:
        case 0x10D9:
        case 0x10DA:
        soundName = "TSYS";
        break;

        case 0x10AF:
        case 0x10AE:
        case 0x10AD:
        case 0x10B1:
        case 0x10B0:
        case 0x10B3:
        case 0x10B2:
        case 0x10B5:
        case 0x10B4:
        soundName = "TTB";
        break;

        case 0x112A:
        case 0x10C4:
        case 0x10C5:
        case 0x10C6:
        case 0x10C7:
        soundName = "TVV";
        break;

        case 0x112F:
        soundName = "WDKS";
        break;

        case 0x1327:
        soundName = "WRR";
        break;

        case 0x1096:
        case 0x1097:
        soundName = "WACSP";
        break;

        case 0x1099:
        soundName = "WACA";
        break;

        case 0x1098:
        soundName = "WACS";
        break;

        case 0x109A:
        soundName = "WACW";
        break;

        case 0x109C:
        case 0x12A7:
        soundName = "WBB";
        break;

        case 0x1089:
        case 0x120B:
        case 0x108A:
        soundName = "WBDD";
        break;

        case 0x108B:
        case 0x108C:
        case 0x139B:
        soundName = "WBC";
        break;

        case 0x1088:
        case 0x1398:
        soundName = "WCC";
        break;

        case 0x1084:
        case 0x1083:
        soundName = "WDS";
        break;

        case 0x1090:
        soundName = "WDD";
        break;

        case 0x1085:
        soundName = "WE";
        break;

        case 0x108F:
        case 0x108E:
        case 0x129F:
        soundName = "WEA";
        break;

        case 0x1093:
        case 0x1094:
        soundName = "WHC";
        break;

        case 0x1092:
        soundName = "WIIO";
        break;

        case 0x107A:
        case 0x107B:
        soundName = "WMC";
        break;

        case 0x1072:
        case 0x1071:
        case 0x123A:
        soundName = "WMKS";
        break;

        case 0x121D:
        case 0x1087:
        case 0x1086:
        soundName = "WMW";
        break;

        case 0x1188:
        case 0x1091:
        case 0x141D:
        soundName = "WMUC";
        break;

        case 0x108D:
        soundName = "WURR";
        break;

        case 0x107F:
        case 0x1081:
        case 0x1080:
        soundName = "WSGF";
        break;

        case 0x1082:
        soundName = "WSA";
        break;

        case 0x109B:
        soundName = "WSBS";
        break;

        case 0x1233:
        case 0x1075:
        case 0x1076:
        soundName = "WSSC";
        break;

        case 0x1077:
        case 0x1078:
        case 0x1079:
        soundName = "WTR";
        break;

        case 0x107D:
        case 0x107C:
        case 0x123E:
        soundName = "WTH";
        break;

        case 0x107E:
        soundName = "WTM";
        break;

        case 0x1074:
        case 0x1073:
        soundName = "WWP";
        break;

        case 0x1095:
        soundName = "WWW";
        break;

        case 0x1449:
        case 0x144A:
        case 0x144B:
        soundName = "SWMBC";
        break;

        case 0x144C:
        case 0x1451:
        case 0x1454:
        soundName = "SWCC";
        break;

        case 0x144D:
        soundName = "SWWS";
        break;

        case 0x144E:
        case 0x144F:
        soundName = "SWDS";
        break;

        case 0x1450:
        soundName = "SWFO";
        break;

        case 0x1452:
        soundName = "SWCCF";
        break;

        case 0x1453:
        soundName = "SWBC";
        break;
    }

        if(U16_MISSION_MODE_FIX == 0x0001) snprintf(pulPath, 0x50, "%sstrm/MR%s.brstm", root, lapSpecifier);
        else snprintf(pulPath, 0x50, "%sstrm/%s%s.brstm", root, soundName, lapSpecifier);
        ret = DVD::ConvertPathToEntryNum(pulPath);
    }
    return ret;
}

nw4r::ut::FileStream* MusicSlotsExpand(nw4r::snd::DVDSoundArchive* archive, void* buffer, int size,
    const char* extFilePath, u32 r7, u32 length) {

    const char firstChar = extFilePath[0xC];
    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const PulsarId track = cupsConfig->GetWinning();

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
        else if(!CupsConfig::IsReg(track) ) {
            if(U8_BRSTMS == 0x01 || U16_MISSION_MODE_FIX == 0x0001) {
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