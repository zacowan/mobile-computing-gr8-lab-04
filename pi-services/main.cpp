#include <iostream>
#include <wiringPi.h>
#include "mode.cpp"
#include "handle_with_debounce.cpp"

using namespace std;

/**
 * START configuration constants
 * -----------------------------------------------------------------------------
 */

// Determines the "clock" of the pi
#define LOOP_DELAY 100

// Define all of the pin numbers below
#define PIN_BTN 27
#define PIN_R_IN 1
#define PIN_G_IN 2
#define PIN_B_IN 3

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
volatile high_resolution_clock buttonPressTimestamp = high_resolution_clock::now();

/**
 * END state variables
 * -----------------------------------------------------------------------------
 */

/**
 * @brief Changes the RGB LED color after a button press to change the mode
 *
 */
void changeMode()
{
    cout << "Changed mode" << endl;
}

/**
 * @brief Sets up raspberry pi board, pins, and interrupt handlers
 *
 */
void setup()
{
    // TODO: setup input pins for monitoring sensor data and voltage on RGB LED
    // Setup interrupt handler for button
    wiringPiISR(PIN_BTN, INT_EDGE_RISING, handleWithDebounce(&changeMode, 250, buttonPressTimestamp));
}

/**
 * @brief Updates currMode based on the RBG LED color
 *
 */
void updateMode()
{
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
