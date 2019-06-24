import paho.mqtt.client as mqtt
import json
import time

class Talker(object):

    def __init__(self, ip):
        self.t_client = mqtt.Client()
        self.t_client.connect(host=ip, port=1883)

    def send_data(self, speed, dir):
        topic = 'control'
        data = {"spd": speed, "dir": dir}

        self.t_client.publish(topic, json.dumps(data), qos=0)


def on_message(client, userdata, message):
    print(message.payload)


class Listener(object):

    def __init__(self, ip):
        self.l_client = mqtt.Client()
        self.l_client.on_message = on_message
        self.l_client.connect(host=ip, port=1883)

        topic = 'control'
        self.l_client.subscribe(topic, qos=0)


if __name__ == "__main__":
    pub = Talker('127.0.0.1')

    while(True):
        pub.send_data(100, -100)

        time.sleep(0.1)





