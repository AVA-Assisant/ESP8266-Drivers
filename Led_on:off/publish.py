

import paho.mqtt.client as mqtt
import json


# def on_connect(mqttc, obj, flags, rc):
#     print("rc: " + str(rc))


# def on_message(mqttc, obj, msg):
#     print(msg.topic + " " + str(msg.payload))


# def on_publish(mqttc, obj, mid):
#     print("mid: " + str(mid))


# def on_subscribe(mqttc, obj, mid, granted_qos):
#     print("Subscribed: " + str(mid) + " " + str(granted_qos))


# def on_log(mqttc, obj, level, string):
#     print(string)


mqttc = mqtt.Client("Publisher")
# mqttc.on_message = on_message
# mqttc.on_connect = on_connect
# mqttc.on_publish = on_publish
# mqttc.on_subscribe = on_subscribe

mqttc.connect("192.168.1.191", 2000)

mqttc.loop_start()

while True:
    q = input("Led: ")
    if q == "on":
        mqttc.publish("led", json.dumps({"state": True}))
    elif q == "off":
        mqttc.publish("led", json.dumps({"state": False}))
