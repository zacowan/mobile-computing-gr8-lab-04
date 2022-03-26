#pragma once

#include <string>

using namespace std;

/**
 * @brief Changes the color of the RBG LED to update the mode of the device.
 *
 * @param newMode the mode to set the device to.
 * A string that is one of "OFF" | "AUTO" | "ON".
 *
 */
void toggleMode(string newMode)
{
    switch (newMode)
    {
    case "OFF":
        // TODO: turn the RGB LED to OFF_COLOR
        break;

    case "AUTO":
        // TODO: turn the RGB LED to AUTO_COLOR
        break;

    case "ON":
        // TODO: turn the RGB LED to ON_COLOR
        break;

    default:
        // Do nothing
        break;
    }
}
