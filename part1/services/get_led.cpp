#include "get_led.h"

/**
 * @brief Get the status of the standard LED
 * 
 * Entity: LED_1
 * Service Description: 
 * This service interfaces with the Green LED found in our Atlas Thing. 
 * It does a read on the GPIO pin powering the LED to determine its current 
 * operational state, either ON or OFF. 
 * 
 * Once read in, the service returns the integer 1 to represent the LED 
 * being ON (Reading HIGH) and a 0 for when the LED is OFF (Reading LOW)
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
