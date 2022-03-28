#include <string>
#include <wiringPi.h>

using namespace std;

int PIN_R = 16;
int PIN_G = 20;
int PIN_B = 21;

int RGB_ON = LOW;
int RGB_OFF = HIGH;

/**
 * @brief Changes the color of the RBG LED to update the mode of the device.
 *
 * @param newMode the mode to set the device to.
 * An integer that is one of 0 | 1 | 2.
 *
 */
void toggleMode(string newMode)
{
    switch (newMode)
    {
    case 0:
        // turn the RGB LED to OFF_COLOR
        digitalWrite(PIN_R, RGB_ON);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_OFF);
        break;

    case 1:
        // turn the RGB LED to AUTO_COLOR
        digitalWrite(PIN_R, RGB_OFF);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_ON);
        break;

    case 2:
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
