#include <iostream>
#include "get_led.h"
#include "get_light_level.h"
#include "get_mode.h"
#include "toggle_mode.h"

using namespace std;

#define DELAY_TIME 5000;

string mode_num_to_text(int mode){
    switch(mode){
        case 0:
            return "OFF";
        case 1:
            return "AUTO";
        case 2:
            return "ON";
    }

    return "";
}

int main()
{
    // Setup wiringPi
    if (wiringPiSetupGpio() < 0)
    {
        cout << "Failed to setup wiringPi" << endl;
        return 1;
    }
    // Test the services

    // Toggle to Mode 1 (AUTO)
    cout << "-- Toggling to Mode 1 (AUTO) --" << endl;
    toggleMode(1);

    delay(500);

    // Get the Current Mode of the Atlas Thing
    int current_mode = getMode();
    cout << "The Current Mode is " << mode_num_to_text(current_mode) << endl;

    // Get the LED Status
    cout << "The LED is currently " << ((getLED() == 1) ? "ON" : "OFF") << endl;

    // Get the Current Light Level and Print whether LOW or HIGH
    int light_level = getLightLevel();
    cout << "The Current Light Level is " << light_level << endl;
    cout << "We interpret this as a " << ((light_level < 50) ? "HIGH" : "LOW") << " amount of light." << endl;

    delay(5000);

    // Toggle to Mode 2 (ON)
    cout << "-- Toggling to Mode 2 (ON) --" << endl;
    toggleMode(2);

    // Get the LED Status
    cout << "The LED is currently " << ((getLED() == 1) ? "ON" : "OFF") << endl;
    
    delay(5000);

    // Toggle to Mode 0 (OFF)
    cout << "-- Toggling to Mode 0 (OFF) --" << endl;
    toggleMode(0);

    delay(500);

    // Get the LED Status
    cout << "The LED is currently " << ((getLED() == 1) ? "ON" : "OFF") << endl;

    return 0;
}