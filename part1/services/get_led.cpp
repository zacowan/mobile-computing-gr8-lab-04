#include "get_led.h"

/**
 * @brief Get the status of the standard LED
 *
 * @return int, 1 for "ON" | 0 for "OFF"
 */
int getLED()
{
    auto status = digitalRead(constants::PIN_LED);

    if (status == HIGH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
