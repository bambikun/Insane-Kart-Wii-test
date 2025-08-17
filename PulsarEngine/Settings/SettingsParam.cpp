#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>
#include <Settings/SettingsParam.hpp>

namespace Pulsar {

namespace Settings {

u8 Params::radioCount[Params::pageCount] ={
    6, 0, 1, 8, 6, //menu, race, host, OTT, KO
    6, 4, 8, 8, 6, 5, 4, 5, 2//Add user radio count here

};
u8 Params::scrollerCount[Params::pageCount] ={ 2, 8, 3, 0, 2, 1, 3, 0, 0, 1, 0, 2, 0, 2 }; //menu, race, host, OTT, KO
u8 Params::buttonsPerPagePerRow[Params::pageCount][Params::maxRadioCount] = //first row is PulsarSettingsType, 2nd is rowIdx of radio
{
    { 3, 2, 2, 2, 2, 2, 0, 0 }, //Misc
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //Colors
    { 2, 0, 0, 0, 0, 0, 0, 0 }, //Visuals
    { 2, 2, 2, 2, 2, 2, 2, 2 }, //Race 1
    { 2, 2, 2, 2, 2, 2, 0, 0 }, //Race 2
    { 2, 2, 3, 2, 2, 3, 0, 0 }, //Race 3
    { 2, 2, 2, 2, 0, 0, 0, 0 }, //Race 4
    { 2, 2, 2, 2, 4, 2, 3, 2 }, //Accessibility
    { 3, 2, 2, 2, 2, 2, 2, 2 }, //Sound 1
    { 2, 2, 2, 2, 2, 2, 0, 0 }, //Sound 2
    { 2, 2, 2, 2, 2, 0, 0, 0 }, //Online
    { 2, 4, 2, 2, 0, 0, 0, 0 }, //Host
    { 2, 2, 2, 2, 2, 0, 0, 0 }, //OTT
    { 2, 2, 0, 0, 0, 0, 0, 0 } //KO


 
};
u8 Params::optionsPerPagePerScroller[Params::pageCount][Params::maxScrollerCount] =
{
    { 4, 3, 0, 0, 0, 0, 0, 0 }, //Misc
    {16,16,16,16,16,16,16,16 }, //Colors
    { 9, 5, 6, 0, 0, 0, 0, 0 }, //Visuals
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //Race 1
    { 9, 2, 0, 0, 0, 0, 0, 0 }, //Race 2
    { 2, 0, 0, 0, 0, 0, 0, 0 }, //Race 3
    { 4, 4, 3, 2, 2, 0, 0, 0 }, //Race 4
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //Accessiblilty
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //Sound 1
    { 6, 0, 0, 0, 0, 0, 0, 0 }, //Sound 2
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //Online
    { 7,15, 0, 0, 0, 0, 0, 0 }, //Host
    { 0, 0, 0, 0, 0, 0, 0, 0 }, //OTT
    { 4, 4, 0, 0, 0, 0, 0, 0 } //KO


 

};

}//namespace Settings
}//namespace Pulsar



