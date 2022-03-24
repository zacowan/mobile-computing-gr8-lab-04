import RPi.GPIO as GPIO  # Import Raspberry Pi GPIO library
from time import sleep  # Import the sleep function from the time module

pin_num = 18
pin_num_in = 17

GPIO.setwarnings(False)  # Ignore warning for now
GPIO.setmode(GPIO.BCM)  # Use physical pin numbering
# Set pin 12 to be an output pin and set initial value to low (off)
GPIO.setup(pin_num, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(pin_num_in, GPIO.IN)
print("Done with setup")


def print_curr_status():
    status = GPIO.input(pin_num_in)
    if status == GPIO.HIGH:
        print("HIGH")
    else:
        print("LOW")


print_curr_status()
sleep(1)
GPIO.output(pin_num, GPIO.HIGH)  # Turn on
print_curr_status()
sleep(1)  # Sleep for 0.2 second
GPIO.output(pin_num, GPIO.LOW)  # Turn off
print_curr_status()

GPIO.cleanup()
