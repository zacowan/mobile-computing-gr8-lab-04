#include <string>
#include <wiringPi.h>

using namespace std;

int PIN_R = 16;
int PIN_G = 20;
int PIN_B = 21;

int RGB_ON = LOW;
int RGB_OFF = HIGH;

/**
 * @brief Get the current mode of the device based on the RGB LED color.
 *
 * @return int, one of 0 | 1 | 2.
 */
string getMode()
{
    // Read which LED color is "ON"
    if (digitalRead(PIN_R) == RGB_ON)
    {
        // Red is on, mode is "OFF"
        return 0;
    }
    else if (digitalRead(PIN_G) == RGB_ON)
    {
        // Green is on, mode is "ON"
        return 1;
    }
    else
    {
        // Blue is on, mode is "AUTO"
        return 2;
    }
}
