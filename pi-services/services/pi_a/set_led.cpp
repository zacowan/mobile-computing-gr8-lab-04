#include <string>
#include <wiringPi.h>

using namespace std;

#define PIN_LED 23

/**
 * @brief Set the led status to ON/OFF
 *
 * @param status one of "ON" || "OFF"
 */
void set_led(string status)
{
    if (status == "ON")
    {
        digitalWrite(PIN_LED, HIGH);
    }
    else
    {
        digitalWrite(PIN_LED, LOW);
    }
}
