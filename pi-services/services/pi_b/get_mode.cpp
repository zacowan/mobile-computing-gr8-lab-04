#include <string>
#include <wiringPi.h>

using namespace std;

#define PIN_R 16
#define PIN_G 20
#define PIN_B 21

#define RGB_ON LOW
#define RGB_OFF HIGH

/**
 * @brief Get the current mode of the device based on the RGB LED color.
 *
 * @return string, one of "OFF" | "AUTO" | "ON".
 */
string getMode()
{
    // Read which LED color is "ON"
    if (digitalRead(PIN_R) == RGB_ON)
    {
        // Red is on, mode is "OFF"
        return "OFF";
    }
    else if (digitalRead(PIN_G) == RGB_ON)
    {
        // Green is on, mode is "ON"
        return "ON";
    }
    else
    {
        // Blue is on, mode is "AUTO"
        return "AUTO";
    }
}
