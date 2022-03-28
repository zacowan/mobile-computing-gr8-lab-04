#include <string>
#include <wiringPi.h>

using namespace std;

int PIN_R = 5;
int PIN_G = 6;
int PIN_B = 13;

int RGB_ON = LOW;
int RGB_OFF = HIGH;

/**
 * @brief Changes the color of the RBG LED to update the mode of the device.
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
