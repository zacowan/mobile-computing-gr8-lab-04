"""
This file holds the runtime code for raspberry pi A, with the button and LED.

Summary:
    This raspberry pi should turn a LED on/off with the press of a button. The
    services that will be provided by this pi are:

        get_led -> returns the status of the LED (ON/OFF)
        set_led(state) -> sets the status of the LED (ON/OFF)

Hardware setup:
    An LED should be connected with a resistor to GPIO pin 23 and grounded.
    A button should be connected with GPIO pin 24 and grounded.

"""

import RPi.GPIO as GPIO  # Import Raspberry Pi GPIO library
from time import sleep  # Import the sleep function from the time module

# ########## CONSTANTS ##########
PIN_BTN = 24
PIN_LED = 23
LOOP_DELAY = 10 / 1000  # in s (ms / 1000)
BTN_DEBOUNCE = 250  # in ms
# ###############################


def handle_button_press(pin):
    """Handles changing LED state"""
    msg = "Button pressed -> turning LED {}"
    if GPIO.input(PIN_LED) == GPIO.LOW:
        GPIO.output(PIN_LED, GPIO.HIGH)
        print(msg.format("ON"))
    else:
        GPIO.output(PIN_LED, GPIO.LOW)
        print(msg.format("OFF"))


def setup():
    """Sets up the pi for the program"""
    # Set up board
    GPIO.setwarnings(False)  # Ignore warning for now
    GPIO.setmode(GPIO.BCM)  # Use physical pin numbering
    # Set up pins
    GPIO.setup(PIN_LED, GPIO.OUT, initial=GPIO.LOW)
    GPIO.setup(PIN_BTN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    # Set up button
    GPIO.add_event_detect(PIN_BTN, GPIO.FALLING,
                          callback=handle_button_press, bouncetime=BTN_DEBOUNCE)
    print("Completed setup")


def main():
    try:
        setup()
        while True:
            sleep(LOOP_DELAY)
    except Exception as e:
        print("Exception: {}".format(e))
    finally:
        GPIO.cleanup()


if __name__ == "__main__":
    main()
