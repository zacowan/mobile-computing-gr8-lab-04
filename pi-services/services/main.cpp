#include <iostream>
#include "get_led.cpp"
#include "get_light_level.cpp"
#include "get_mode.cpp"
#include "toggle_mode.cpp"

int main()
{
    // Setup wiringPi
    if (wiringPiSetupGpio() < 0)
    {
        cout << "Failed to setup wiringPi" << endl;
        return 1;
    }
    // Test the services

    return 0;
}
