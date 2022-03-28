"""
This file holds the runtime code for raspberry pi B, with a button, LED,
photoresistor, and RGB LED.

Summary:
    This raspberry pi should control the ON/OFF state of an LED based on 3
    different modes.

    OFF: the LED should constantly be OFF. Indicated by a RED color on the RGB
    LED.

    AUTO: the LED should be OFF if the photoresistor detects that it is LIGHT,
    or ON if the photoresistor detects that it is DARK.
    Indicated by a BLUE color on the RGB LED.

    ON: the LED should constantly be ON. Indicated by a GREEN color on the RGB
    LED.

    The services that will be provided by this pi are:

        get_light_level -> returns the current light level from the
        photoresistor (LIGHT/DARK)
        get_mode -> returns the mode based on the RGB LED (OFF/AUTO/ON)
        get_led -> returns the status of the LED (ON/OFF)
        toggle_mode(newMode) -> switches the mode based on newMode (OFF/AUTO/ON)

"""

import RPi.GPIO as GPIO  # Import Raspberry Pi GPIO library
from time import sleep  # Import the sleep function from the time module

# ########## CONSTANTS ##########
PIN_BTN = 24
PIN_LED = 23
PIN_R = 16
PIN_G = 20
PIN_B = 21
LOOP_DELAY = 10 / 1000  # in s (ms / 1000)
BTN_DEBOUNCE = 250  # in ms

# Helpers
RGB_ON = GPIO.LOW
RGB_OFF = GPIO.HIGH
# ###############################


def change_rgb_color(color):
    """
    Changes the color of the RGB LED.

    Params:
        color (str): one of 'RED' | 'GREEN' | 'BLUE'
    """
    if (color == 'RED'):
        GPIO.output(PIN_R, RGB_ON)
        GPIO.output(PIN_G, RGB_OFF)
        GPIO.output(PIN_B, RGB_OFF)
    elif (color == 'GREEN'):
        GPIO.output(PIN_R, RGB_OFF)
        GPIO.output(PIN_G, RGB_ON)
        GPIO.output(PIN_B, RGB_OFF)
    else:
        # color == 'BLUE'
        GPIO.output(PIN_R, RGB_OFF)
        GPIO.output(PIN_G, RGB_OFF)
        GPIO.output(PIN_B, RGB_ON)


def get_mode():
    """
    Gets the mode based on the RGB LED.

    Returns:
        str: one of 'OFF' | 'AUTO | 'ON'
    """
    if GPIO.input(PIN_R) == RGB_ON:
        # Mode is OFF
        return 'OFF'
    elif GPIO.input(PIN_G) == RGB_ON:
        # Mode is ON
        return 'ON'
    else:
        # Mode is AUTO
        return 'AUTO'


def toggle_mode():
    """
    Changes the current mode between OFF, AUTO, and ON

    Returns:
        str: the resulting mode, one of 'OFF' | 'AUTO' | 'ON'
    """
    curr_mode = get_mode()
    if curr_mode == 'OFF':
        # Change to 'AUTO' by changing RGB color to 'BLUE'
        change_rgb_color('BLUE')
        return 'AUTO'
    elif curr_mode == 'AUTO':
        # Change to 'ON' by changing RGB color to 'GREEN'
        change_rgb_color('GREEN')
        return 'ON'
    else:
        # Change to 'OFF' by changing RGB color to 'RED'
        change_rgb_color('RED')
        return 'OFF'


def handle_button_press(_):
    """Changes the mode based on button press"""
    msg = "Button pressed -> changing mode to {}"
    new_mode = toggle_mode()
    print(msg.format(new_mode))


def setup():
    """Sets up the pi for the program"""
    # Set up board
    GPIO.setwarnings(False)  # Ignore warning for now
    GPIO.setmode(GPIO.BCM)  # Use physical pin numbering
    # Set up pins
    GPIO.setup(PIN_LED, GPIO.OUT, initial=GPIO.LOW)
    GPIO.setup(PIN_BTN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(PIN_R, GPIO.OUT, initial=RGB_OFF)
    GPIO.setup(PIN_G, GPIO.OUT, initial=RGB_ON)
    GPIO.setup(PIN_B, GPIO.OUT, initial=RGB_OFF)
    # Set up button
    GPIO.add_event_detect(PIN_BTN, GPIO.FALLING,
                          callback=handle_button_press, bouncetime=BTN_DEBOUNCE)
    print("Completed setup")


def loop():
    """What should happen during every clock tick."""
    curr_mode = get_mode()
    if curr_mode == 'OFF':
        # Turn standard LED off
        GPIO.output(PIN_LED, GPIO.LOW)
    elif curr_mode == 'AUTO':
        # TODO: turn standard LED on/off based on sensor data
        pass
    else:
        # curr_mode == 'ON'
        # Turn standard LED on
        GPIO.output(PIN_LED, GPIO.HIGH)


def main():
    try:
        setup()
        while True:
            loop()
            sleep(LOOP_DELAY)
    except KeyboardInterrupt:
        print()
        print("Program execution stopped via keyboard")
    except Exception as e:
        print("Exception: {}".format(e))
    finally:
        GPIO.cleanup()


if __name__ == "__main__":
    main()
