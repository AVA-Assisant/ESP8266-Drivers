#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Karolina/Bartosz";
const char *password = "2007/2011";
const char *mqtt_server = "192.168.1.144";
const char *id = "ESP-1";
int mqtt_port = 2000;
int state;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
    Serial.print(".");
    digitalWrite(BUILTIN_LED, HIGH);
    delay(250);
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(BUILTIN_LED, LOW);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  payload[length] = '\0';
  String strPayload = String((char *)payload);
  Serial.print(strPayload);
  Serial.println();

  DynamicJsonDocument doc(512);
  deserializeJson(doc, strPayload); // deserialize JSON message to DynamicJsonDocument

  state = doc["state"];

  if (state == 1)
  {
    digitalWrite(BUILTIN_LED, LOW);
  }
  else
  {
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(id))
    {
      Serial.println("connected");
      client.subscribe(id);

      digitalWrite(BUILTIN_LED, LOW);
      delay(10);
      digitalWrite(BUILTIN_LED, HIGH);
      delay(70);
      digitalWrite(BUILTIN_LED, LOW);
      delay(10);
      digitalWrite(BUILTIN_LED, HIGH);
      delay(70);
      digitalWrite(BUILTIN_LED, LOW);
      delay(10);
      digitalWrite(BUILTIN_LED, HIGH);

      analogWrite(BUILTIN_LED, state);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      for (int i = 0; i < 6; i++)
      {
        digitalWrite(BUILTIN_LED, HIGH);
        delay(450);
        digitalWrite(BUILTIN_LED, LOW);
        delay(50);
      }
    }
  }
}

void setup()
{

  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  client.connect(id);
  client.subscribe(id);

  digitalWrite(BUILTIN_LED, HIGH);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
