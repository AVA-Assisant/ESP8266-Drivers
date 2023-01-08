import paho.mqtt.client as mqtt
import json


def on_connect(mqttc, obj, flags, rc):
    print("Connected!")


mqttc = mqtt.Client("Publisher")
mqttc.on_connect = on_connect

mqttc.connect("192.168.1.191", 2000)

mqttc.loop_start()

while True:
    q = input("Led: ")
    if q == "on":
        mqttc.publish("led", json.dumps({"state": 0}))
    elif q == "off":
        mqttc.publish("led", json.dumps({"state": 255}))
    elif q.isnumeric():
        mqttc.publish("led", json.dumps({"state": q}))
