import paho.mqtt.client as mqtt
import json


def on_connect(mqttc, obj, flags, rc):
    print("Connected!")


mqttc = mqtt.Client("Publisher")
mqttc.on_connect = on_connect

mqttc.connect("192.168.0.100", 2000)

mqttc.loop_start()

while True:
    q = input("Led: ")
    if q == "on":
        mqttc.publish("led", json.dumps({"state": True}))
    elif q == "off":
        mqttc.publish("led", json.dumps({"state": False}))
