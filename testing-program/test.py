"""
This file tests the services associated with our IoT thing.

Summary:
    1. The current mode is checked (should be AUTO).
    2. The light level from the photoresistor is checked.
    3. The status of the LED (ON/OFF) is checked (should be ON if light level is
    > 50).
    4. The mode is set to ON.
    5. The status of the LED is checked (should be ON).
    6. The mode is set to OFF.
    7. The status of the LED is checked (should be OFF).

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


class Tester():
    def __init__(self) -> None:
        self.s = setup_connection()

    def get_led(self):
        tweet = construct_tweet("get_led")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)

    def get_light_level(self):
        tweet = construct_tweet("get_light_level")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)

    def get_mode(self):
        tweet = construct_tweet("get_mode")
        self.s.sendall(str.encode(tweet))
        data, addr = self.s.recvfrom(1024)  # buffer size is 1024 bytes
        print(data)

    def toggle_mode(self, new_mode: str):
        tweet = construct_tweet("toggle_mode", "({})".format(new_mode))
        self.s.sendall(str.encode(tweet))
        print("Attempted to toggle mode to {}".format(new_mode))


def main():
    t = Tester()

    # Get the current mode
    t.get_mode()
    # Check the current light level
    t.get_light_level()
    # Check the status of the LED
    t.get_led()
    sleep(5)
    # Change the mode to "ON"
    t.toggle_mode(2)
    # Check the status of the LED
    t.get_led()
    sleep(5)
    # Change the mode to "OFF"
    t.toggle_mode(0)
    # Check the status of the LED
    t.get_led()
    sleep(5)


if __name__ == "__main__":
    main()
