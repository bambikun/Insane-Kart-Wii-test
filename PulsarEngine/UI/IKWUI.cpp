#include <kamek.hpp>
namespace Pulsar {
namespace UI {

// Remove WW Button [Chadderz]
kmWrite16(0x8064B982, 0x00000005);
kmWrite32(0x8064BA10, 0x60000000);
kmWrite32(0x8064BA38, 0x60000000);
kmWrite32(0x8064BA50, 0x60000000);
kmWrite32(0x8064BA5C, 0x60000000);
kmWrite16(0x8064BC12, 0x00000001);
kmWrite16(0x8064BC3E, 0x00000484);
kmWrite16(0x8064BC4E, 0x000010D7);
kmWrite16(0x8064BCB6, 0x00000484);
kmWrite16(0x8064BCC2, 0x000010D7);

// All Vehicles in Battle [Nameless / Scruffy]
kmWrite32(0x80553F98, 0x3880000A);
kmWrite32(0x8084FEF0, 0x48000044);
kmWrite32(0x80860A90, 0x38600000);

//Instant Course Voting [Ro]
kmWrite32(0x80643BC4, 0x60000000);
kmWrite32(0x80643C2C, 0x60000000);

//WW Bubble Skip [Ro]
kmWrite32(0x806075F4, 0x48000060);
kmWrite8(0x80609647, 0x0000003C);
kmWrite8(0x8060964F, 0x00000010);
kmWrite32(0x8060988C, 0x60000000);

//Always Show Timer on Vote Screen [Chadderz]
kmWrite32(0x80650254, 0x60000000);

//Always Show Timer After Online Race Results [Sponge]
kmWrite32(0x8064DB2C, 0x60000000);

//Game Mode Selection Menu (Toadette Hack Fan)
kmWrite8(0x80899ACA, 0x00000058);
kmWrite8(0x80899AF7, 0x00000058);

}//namespace UI
}//namespace Pulsar