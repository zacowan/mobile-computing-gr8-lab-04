#include <string>
#include <wiringPi.h>

using namespace std;

const int PIN_LED = 23;

/**
 * @brief Get the status of the standard LED
 *
 * @return string, one of "ON" | "OFF"
 */
string get_led()
{
    auto status = digitalRead(PIN_LED);

    if (status == HIGH)
    {
        return "ON";
    }
    else
    {
        return "OFF";
    }
}
