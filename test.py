import requests
import time
import random

commands = {"left": "a", "forward": "b", "right": "c"}


while True:
    selected = random.choice(list(commands))
    res = requests.post('http://192.168.215.85:32639/car/test', data={"command":selected})
    print(res)
    print("send!")
    time.sleep(5)
