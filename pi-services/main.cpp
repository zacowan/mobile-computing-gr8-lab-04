#include <iostream>
#include <wiringPi.h>
#include "mode.cpp"

using namespace std;

/**
 * START configuration constants
 * -----------------------------------------------------------------------------
 */

// Determines the "clock" of the pi
#define LOOP_DELAY 100

// Define all of the pin numbers below
#define A_PIN 27

/**
 * END configuration constants
 * -----------------------------------------------------------------------------
 */

/**
 * START state variables
 * -----------------------------------------------------------------------------
 */

// The current mode of the device
volatile Mode currMode = Mode::AUTO;

/**
 * END state variables
 * -----------------------------------------------------------------------------
 */

/**
 * @brief Sets up raspberry pi board, pins, and interrupt handlers
 *
 */
void setup()
{
    // TODO: setup input pins for monitoring sensor data and voltage on RGB LED
    // TODO: setup interrupt handler for button
}

/**
 * @brief Updates currMode based on the RBG LED color
 *
 */
void updateMode()
{
    // TODO
}

/**
 * @brief Defines what the pi should do every "clock" tick
 *
 */
void loop()
{
    updateMode();

    switch (currMode)
    {
    case Mode::OFF:
        // TODO: turn the standard LED is off
        // TODO: turn the RGB LED to OFF_COLOR
        break;

    case Mode::AUTO:
        // TODO: turn standard LED on/off based on sensor data
        // TODO: turn the RGB LED to AUTO_COLOR
        break;

    case Mode::ON:
        // TODO: turn the standard LED is on
        // TODO: turn the RGB LED to ON_COLOR
        break;

    default:
        cerr << "Error: default case" << endl;
        break;
    }
}

int main()
{
    // Setup wiringPi
    if (wiringPiSetup() < 0)
    {
        cout << "Failed to setup wiringPi" << endl;
        return 1;
    }
    // Setup board
    setup();
    // Start the program
    while (true)
    {
        loop();
        delay(LOOP_DELAY);
    }

    return 0;
}
