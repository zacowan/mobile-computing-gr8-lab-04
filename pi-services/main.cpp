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
#define PIN_BTN 3

#define PIN_LED_OUT 2
#define PIN_LED_IN 10

#define PIN_R_OUT 14
#define PIN_G_OUT 15
#define PIN_B_OUT 18
#define PIN_R_IN 17
#define PIN_G_IN 27
#define PIN_B_IN 22

#define LED_ON HIGH
#define LED_OFF LOW
#define RGB_ON LOW
#define RGB_OFF HIGH

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
    // Swap between OFF (RED) -> AUTO (BLUE) -> ON (GREEN)
    if (currMode == Mode::OFF)
    {
        // Swap to auto
        digitalWrite(PIN_R_OUT, RGB_OFF);
        digitalWrite(PIN_G_OUT, RGB_OFF);
        digitalWrite(PIN_B_OUT, RGB_ON);
    }
    else if (currMode == Mode::AUTO)
    {
        // Swap to on
        digitalWrite(PIN_R_OUT, RGB_OFF);
        digitalWrite(PIN_G_OUT, RGB_ON);
        digitalWrite(PIN_B_OUT, RGB_OFF);
    }
    else
    {
        // Swap to off
        digitalWrite(PIN_R_OUT, RGB_ON);
        digitalWrite(PIN_G_OUT, RGB_OFF);
        digitalWrite(PIN_B_OUT, RGB_OFF);
    }
}

/**
 * @brief Sets up raspberry pi board, pins, and interrupt handlers
 *
 */
void setup()
{
    // Setup btn
    pinMode(PIN_BTN, INPUT);
    // Setup green LED
    pinMode(PIN_LED_IN, INPUT);
    pinMode(PIN_LED_OUT, OUTPUT);
    // Setup RGB LED
    pinMode(PIN_R_IN, INPUT);
    pinMode(PIN_R_OUT, OUTPUT);
    pinMode(PIN_G_IN, INPUT);
    pinMode(PIN_G_OUT, OUTPUT);
    pinMode(PIN_B_IN, INPUT);
    pinMode(PIN_B_OUT, OUTPUT);
    // Setup interrupt handler for button
    wiringPiISR(PIN_BTN, INT_EDGE_RISING, handleWithDebounce(&changeMode, 250, buttonPressTimestamp));
}

/**
 * @brief Updates currMode based on the RBG LED color
 *
 */
void updateMode()
{
    // Read which LED color is "ON" (LOW)
    if (digitalRead(PIN_R_IN) == RGB_ON)
    {
        // Red is on
        currMode = Mode::OFF;
    }
    else if (digitalRead(PIN_G_IN) == RGB_ON)
    {
        // Green is on
        currMode = Mode::ON;
    }
    else
    {
        // Blue is on
        currMode = Mode::AUTO;
    }
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
        // Turn the standard LED off
        digitalWrite(PIN_LED_OUT, LED_OFF);
        // Turn the RGB LED to RED to signal OFF
        digitalWrite(PIN_R_OUT, RGB_ON);
        digitalWrite(PIN_G_OUT, RGB_OFF);
        digitalWrite(PIN_B_OUT, RGB_OFF);
        break;

    case Mode::AUTO:
        // TODO: turn standard LED on/off based on sensor data
        // Turn the RGB LED to BLUE to signal AUTO
        digitalWrite(PIN_R_OUT, RGB_OFF);
        digitalWrite(PIN_G_OUT, RGB_OFF);
        digitalWrite(PIN_B_OUT, RGB_ON);
        break;

    case Mode::ON:
        // Turn the standard LED is on
        digitalWrite(PIN_LED_OUT, LED_ON);
        // Turn the RGB LED to GREEN to signal ON
        digitalWrite(PIN_R_OUT, RGB_OFF);
        digitalWrite(PIN_G_OUT, RGB_ON);
        digitalWrite(PIN_B_OUT, RGB_OFF);
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
