from socket import socket, AF_INET, SOCK_STREAM
import json

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
        self.s.sendall(tweet)
        # Not sure if below works
        received = ""
        self.s.recv_into(received)
        print(received)

    def get_light_level(self):
        tweet = construct_tweet("get_light_level")
        self.s.sendall(tweet)
        # Not sure if below works
        received = ""
        self.s.recv_into(received)
        print(received)

    def get_mode(self):
        tweet = construct_tweet("get_mode")
        self.s.sendall(tweet)
        # Not sure if below works
        received = ""
        self.s.recv_into(received)
        print(received)

    def toggle_mode(self, new_mode: str):
        tweet = construct_tweet("toggle_mode", "({})".format(new_mode))
        self.s.sendall(tweet)
        print("Attempted to toggle mode to {}".format(new_mode))


def main():
    t = Tester()

    t.get_led()


if __name__ == "__main__":
    main()
