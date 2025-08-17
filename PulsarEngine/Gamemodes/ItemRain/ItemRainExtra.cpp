#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <kamek.hpp>
#include <MKVN.hpp>

namespace Pulsar {
namespace ItemRain {

// Allow POWs and Shocks to affect other players on their screens.
asmFunc ItemRainOnlineFix() {
    ASM(
        loc_0x0:
            addi r3, r4, 200;
            lis r12, 0x8000;
            lbz r12, 0x120C(r12);
            cmpwi r12, 0;
            beq loc_0x2C;
            lbz r3, 27(r27);
            cmpwi r3, 0x7;
            beq+ loc_0x24;
            cmpwi r3, 0x3;
            beq+ loc_0x24;
            cmpwi r3, 0x4;
            beq+ loc_0x24;
            addi r3, r4, 0xC8;
            b loc_0x2C;

        loc_0x24:
            mr r3, r4;
            b loc_0x2C;

        loc_0x2C:
    )
}
kmCall(0x8065BB40, ItemRainOnlineFix);

void ItemRainFix() {
    ItemRainOnlineFixHook = 0x00;
    if (RKNet::Controller::sInstance->roomType == RKNet::ROOMTYPE_FROOM_HOST || 
        RKNet::Controller::sInstance->roomType == RKNet::ROOMTYPE_FROOM_NONHOST || 
        RKNet::Controller::sInstance->roomType == RKNet::ROOMTYPE_NONE) {
        if (U16_GAMEPLAYC == 0x0001) {
            ItemRainOnlineFixHook = 0x00FF0100;
        }
    }
}
static PageLoadHook FixItemRain(ItemRainFix);

} // namespace ItemRain
} // namespace Pulsar