#include "constants.h"

/**
 * @brief Get the current mode of the device based on the RGB LED color.
 *
 * @return int, one of 0 ("OFF") | 1 ("AUTO") | 2 ("ON")
 */
int getMode()
{
    // Read which LED color is "ON"
    if (digitalRead(constants::PIN_R) == constants::RGB_ON)
    {
        // Red is on, mode is "OFF"
        return 0;
    }
    else if (digitalRead(constants::PIN_G) == constants::RGB_ON)
    {
        // Green is on, mode is "ON"
        return 2;
    }
    else
    {
        // Blue is on, mode is "AUTO"
        return 1;
    }
}
