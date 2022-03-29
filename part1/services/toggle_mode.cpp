#include "constants.h"

/**
 * @brief Changes the color of the RBG LED to update the mode of the device.
 *
 * Entity: button
 * Service description: mimics the functionality of our button, with a higher
 * degree of control. The button cycles between the 3 modes (OFF/AUTO/ON). This
 * service allows a mode to be specified as an int (0 = OFF, 1 = AUTO, 2 = ON)
 * and will set our device into that mode.
 *
 * @param new_mode the mode to set the device to.
 * An integer that is one of 0 | 1 | 2.
 *
 */
void toggleMode(int new_mode)
{
    switch (new_mode)
    {
    case 0:
        // turn the RGB LED to OFF_COLOR
        digitalWrite(constants::PIN_R, constants::RGB_ON);
        digitalWrite(constants::PIN_G, constants::RGB_OFF);
        digitalWrite(constants::PIN_B, constants::RGB_OFF);
        break;

    case 1:
        // turn the RGB LED to AUTO_COLOR
        digitalWrite(constants::PIN_R, constants::RGB_OFF);
        digitalWrite(constants::PIN_G, constants::RGB_OFF);
        digitalWrite(constants::PIN_B, constants::RGB_ON);
        break;

    case 2:
        // turn the RGB LED to ON_COLOR
        digitalWrite(constants::PIN_R, constants::RGB_OFF);
        digitalWrite(constants::PIN_G, constants::RGB_ON);
        digitalWrite(constants::PIN_B, constants::RGB_OFF);
        break;

    default:
        // Do nothing
        break;
    }
}
