#include <string>
#include <wiringPi.h>

using namespace std;

#define PIN_R 16
#define PIN_G 20
#define PIN_B 21

#define RGB_ON LOW
#define RGB_OFF HIGH

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
        // turn the RGB LED to OFF_COLOR
        digitalWrite(PIN_R, RGB_ON);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_OFF);
        break;

    case "AUTO":
        // turn the RGB LED to AUTO_COLOR
        digitalWrite(PIN_R, RGB_OFF);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_ON);
        break;

    case "ON":
        // turn the RGB LED to ON_COLOR
        digitalWrite(PIN_R, RGB_OFF);
        digitalWrite(PIN_G, RGB_ON);
        digitalWrite(PIN_B, RGB_OFF);
        break;

    default:
        // Do nothing
        break;
    }
}
