import RPi.GPIO as GPIO  # Import Raspberry Pi GPIO library
from time import sleep  # Import the sleep function from the time module

pin_r = 14
pin_g = 15
pin_b = 18

GPIO.setwarnings(False)  # Ignore warning for now
GPIO.setmode(GPIO.BCM)  # Use physical pin numbering
# Set pin 12 to be an output pin and set initial value to low (off)
GPIO.setup(pin_r, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(pin_g, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(pin_b, GPIO.OUT, initial=GPIO.LOW)
print("Done with setup")


# def print_curr_status():
#     status = GPIO.input(pin_num_in)
#     if status == GPIO.HIGH:
#         print("HIGH")
#     else:
#         print("LOW")


sleep(5)

GPIO.cleanup()
