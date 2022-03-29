/**
 * @file main.cpp
 * @author Zach Cowan, Shaun Fidler, Sydney McLaughlin
 * @brief This file contains the main program for running our "night light"
 * application on our raspberry pi.
 *
 * Our program utilizes 4 devices: a button, a standard LED, a RGB LED, and a
 * photoresistor with an ADC.
 *
 * This program will operate continuously across 3 modes: OFF, AUTO, and ON. In
 * OFF mode, the standard LED will be set to off. In AUTO mode, the standard LED
 * will be on or off based on the state of the photoresistor. If the value from
 * the photoresistor is > 50, the LED will be on and otherwise, will be off. In
 * ON mode, the standard LED will be set to on. At any time, the button may be
 * pressed to toggle between the 3 modes (OFF -> AUTO -> ON). Additionally, the
 * current mode is represented by the color of the RGB LED. RED corresponds to
 * OFF, BLUE to AUTO, and GREEN to ON.
 *
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <wiringPi.h>
#include <ADCDevice.hpp>
#include <chrono>
#include <signal.h>
#include "mode.cpp"
#include "color.cpp"

using namespace std;
using namespace std::chrono;

/**
 * START configuration constants
 * -----------------------------------------------------------------------------
 */

// Determines the "clock" of the pi
#define LOOP_DELAY 30

#define DEBOUNCE 240

// Define all of the pin numbers below
#define PIN_BTN 24

#define PIN_LED 23

#define PIN_R 5
#define PIN_G 6
#define PIN_B 13

#define LED_ON HIGH
#define LED_OFF LOW
#define RGB_ON LOW
#define RGB_OFF HIGH

#define LL_HIGH "HIGH"
#define LL_LOW "LOW"

/**
 * END configuration constants
 * -----------------------------------------------------------------------------
 */

/**
 * START state variables
 * -----------------------------------------------------------------------------
 */

// The current mode of the device
auto currMode = Mode::ON;
auto buttonPressTimestamp = high_resolution_clock::now();
ADCDevice *adc;

/**
 * END state variables
 * -----------------------------------------------------------------------------
 */

/**
 * @brief Handles changing the RGB LED color
 *
 * @param Color The color to set
 */
void changeRGBColor(Color color)
{
    if (color == Color::RED)
    {
        // Change to red
        digitalWrite(PIN_R, RGB_ON);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_OFF);
    }
    else if (color == Color::GREEN)
    {
        // Change to green
        digitalWrite(PIN_R, RGB_OFF);
        digitalWrite(PIN_G, RGB_ON);
        digitalWrite(PIN_B, RGB_OFF);
    }
    else
    {
        // Change to blue
        digitalWrite(PIN_R, RGB_OFF);
        digitalWrite(PIN_G, RGB_OFF);
        digitalWrite(PIN_B, RGB_ON);
    }
}

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
        cout << "Changing mode to AUTO" << endl;
        changeRGBColor(Color::BLUE);
    }
    else if (currMode == Mode::AUTO)
    {
        // Swap to on
        cout << "Changing mode to ON" << endl;
        changeRGBColor(Color::GREEN);
    }
    else
    {
        // Swap to off
        cout << "Changing mode to OFF" << endl;
        changeRGBColor(Color::RED);
    }
}

/**
 * @brief Handles the button press with a debounce
 *
 */
void handleButtonPress()
{
    cout << "Button pressed" << endl;

    auto now = high_resolution_clock::now();
    auto elapsedTimeMs = duration_cast<duration<double>>(now - buttonPressTimestamp).count() * 1000;

    if (elapsedTimeMs >= DEBOUNCE)
    {
        cout << "Button press measured with elapsed time between of " << elapsedTimeMs << "ms" << endl;
        changeMode();
    }

    buttonPressTimestamp = high_resolution_clock::now();
}

/**
 * @brief Gets the Light Level from the sensor using the ADC
 *
 */
string getLightLevel()
{
    int level = adc->analogRead(0);
    return (level < 50) ? LL_HIGH : LL_LOW;
}

/**
 * @brief Sets up raspberry pi board, pins, and interrupt handlers
 *
 */
void setup()
{
    cout << "Starting setup" << endl;
    // Setup btn
    pinMode(PIN_BTN, INPUT);
    // Setup green LED
    pinMode(PIN_LED, OUTPUT);
    // Setup RGB LED
    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_G, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    // Setup interrupt handler for button
    wiringPiISR(PIN_BTN, INT_EDGE_RISING, handleButtonPress);
    // Set initial LED value
    digitalWrite(PIN_LED, LED_OFF);
    // Set initial RGB LED values
    changeRGBColor(Color::BLUE);

    // Initialize Light Sensor Components
    adc = new ADCDevice();
    if (adc->detectI2C(0x4b))
    {
        delete adc;
        adc = new ADS7830();
    }
    else
    {
        cout << "No I2C" << endl;
    }
    cout << "Setup complete" << endl;
}

/**
 * @brief Syncs currMode with the color of the RGB LED
 *
 */
void syncMode()
{
    // Read which LED color is "ON"
    if (digitalRead(PIN_R) == RGB_ON)
    {
        // Red is on, set mode to OFF
        currMode = Mode::OFF;
    }
    else if (digitalRead(PIN_G) == RGB_ON)
    {
        // Green is on, set mode to ON
        currMode = Mode::ON;
    }
    else
    {
        // Blue is on, set mode to AUTO
        currMode = Mode::AUTO;
    }
}

/**
 * @brief Defines what the pi should do every "clock" tick
 *
 */
void loop()
{
    syncMode();

    switch (currMode)
    {
    case Mode::OFF:
        // Turn the standard LED off
        digitalWrite(PIN_LED, LED_OFF);
        // Turn the RGB LED to RED to signal OFF
        changeRGBColor(Color::RED);
        break;

    case Mode::AUTO:
        // TODO: turn standard LED on/off based on sensor data
        // TEST THIS
        if (getLightLevel() == LL_HIGH)
        {
            // Turn the standard LED OFF
            digitalWrite(PIN_LED, LED_OFF);
            // cout << "Light is OFF" << endl;
        }
        else
        {
            // Turn the standard LED ON
            digitalWrite(PIN_LED, LED_ON);
            // cout << "Light is ON" << endl;
        }
        // Turn the RGB LED to BLUE to signal AUTO
        changeRGBColor(Color::BLUE);
        break;

    case Mode::ON:
        // Turn the standard LED to ON
        digitalWrite(PIN_LED, LED_ON);
        // Turn the RGB LED to GREEN to signal ON
        changeRGBColor(Color::GREEN);
        break;

    default:
        cerr << "Error: default case" << endl;
        break;
    }
}

/**
 * @brief Handles resetting the state of the LEDs before exiting
 *
 */
void cleanup()
{
    digitalWrite(PIN_R, RGB_OFF);
    digitalWrite(PIN_G, RGB_OFF);
    digitalWrite(PIN_B, RGB_OFF);
    digitalWrite(PIN_LED, OFF);
}

void handleSigInt(int s)
{
    cout << "Caught signal " << s << endl;
    cleanup();
    exit(0);
}

/**
 * @brief Sets up interrupt handler for ctrl+c
 *
 */
void setupSigIntHandler()
{
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = handleSigInt;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

int main()
{
    // Setup wiringPi
    if (wiringPiSetupGpio() < 0)
    {
        cout << "Failed to setup wiringPi" << endl;
        return 1;
    }
    // Setup board
    setup();
    // Setup ctrl+c catcher
    setupSigIntHandler();
    // Start the program
    while (true)
    {
        loop();
        delay(LOOP_DELAY);
    }

    return 0;
}
