"""
This file tests the services associated with our IoT thing.

Summary:
    1. The mode is set to AUTO.
    2. The current mode is checked (should be AUTO).
    3. The light level from the photoresistor is checked.
    4. The status of the LED (ON/OFF) is checked (should be ON if light level is
    > 50).
    5. The mode is set to ON.
    6. The status of the LED is checked (should be ON).
    7. The mode is set to OFF.
    8. The status of the LED is checked (should be OFF).

"""
from socket import socket, AF_INET, SOCK_STREAM
import json
from time import sleep

# ########## CONSTANTS ##########
HOST_IP = "192.168.0.111"
PORT = 6668
THING_ID = "StrawberryThing01"
SPACE_ID = "StrawberrySmartSpace"
# ###############################


def setup_connection():
    s1 = socket(AF_INET, SOCK_STREAM)
    s1.connect((HOST_IP, PORT))

    return s1


def construct_tweet(service_name: str, service_inputs: str = "()") -> str:
    tweet = {
        "Tweet Type": "Service call",
        "Thing ID": THING_ID,
        "Space ID": SPACE_ID,
        "Service Name": service_name,
        "Service Inputs": service_inputs
    }

    return json.dumps(tweet)


def led_status_int_to_str(status: int) -> str:
    if status == 0:
        return "OFF"
    else:
        return "ON"


def mode_int_to_str(mode: int) -> str:
    if mode == 0:
        return "OFF"
    elif mode == 1:
        return "AUTO"
    else:
        return "ON"


class Tester():
    def __init__(self) -> None:
        self.s = setup_connection()

    def get_led(self):
        tweet = construct_tweet("get_led")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)
        print(f"Current LED status -> {led_status_int_to_str(data)}")

    def get_light_level(self):
        tweet = construct_tweet("get_light_level")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)
        print(f"Current light level -> {data}")

    def get_mode(self):
        tweet = construct_tweet("get_mode")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)
        print(f"Current mode -> {mode_int_to_str(data)}")

    def toggle_mode(self, new_mode: int):
        tweet = construct_tweet("toggle_mode", "({})".format(new_mode))
        self.s.sendall(str.encode(tweet))
        print("Attempted to toggle mode to {}".format(new_mode))


def main():
    t = Tester()

    # Set the current mode to AUTO
    t.toggle_mode(1)
    sleep(0.5)
    # Get the current mode
    t.get_mode()
    # Check the current light level
    t.get_light_level()
    # Check the status of the LED
    t.get_led()
    sleep(5)
    # Change the mode to "ON"
    t.toggle_mode(2)
    sleep(0.5)
    # Check the status of the LED
    t.get_led()
    sleep(5)
    # Change the mode to "OFF"
    t.toggle_mode(0)
    sleep(0.5)
    # Check the status of the LED
    t.get_led()
    sleep(5)


if __name__ == "__main__":
    main()
