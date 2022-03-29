#include "constants.h"

/**
 * @brief Get the current mode of the device based on the RGB LED color.
 *
 * Entity: RGB_LED_1
 * Service description: reads the color of the LED and returns an abstraction
 * that indicates what mode our program is currently in. If the LED is RED, the
 * mode is "OFF" (represented by 0). If the LED is BLUE, the mode is "AUTO" (
 * represented by 1). If the LED is GREEN, the mode is "ON" (represented by 2).
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
