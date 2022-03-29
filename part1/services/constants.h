#include <wiringPi.h>
#include <wiringPiI2C.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    constexpr int PIN_LED { 23 };
    constexpr int PIN_R { 5 };
    constexpr int PIN_G { 6 };
    constexpr int PIN_B { 13 };

    constexpr int RGB_ON { LOW };
    constexpr int RGB_OFF { HIGH };
}
#endif