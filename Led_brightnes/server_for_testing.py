import paho.mqtt.client as mqtt
import json
from flask import Flask, request

app = Flask(__name__)


def on_connect(mqttc, obj, flags, rc):
    print("Connected!")


mqttc = mqtt.Client("Publisher")
mqttc.on_connect = on_connect

mqttc.connect("192.168.1.191", 2000)

mqttc.loop_start()


@app.route('/led', methods=['POST'])
def led():
    value = request.get_json()

    mqttc.publish("led", json.dumps({"state": value.get("status")}))

    return value, 200


app.run(host='192.168.1.191', port=2500)
