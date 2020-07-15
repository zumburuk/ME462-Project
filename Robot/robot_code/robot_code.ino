/*
 * This code allows NodeMCU to connect to an MQTT Broker and controls the robot.
 * 
 */

#include <PubSubClient.h>  // Required for MQTT communication protocol - https://pubsubclient.knolleary.net/
#include <ESP8266WiFi.h>   // Required for NodeMCU wifi communications - https://arduino-esp8266.readthedocs.io/

int motorA_phase = 15;   // D8 pin - Determines the motor direction
int motorA_enable = 13;  // D7 pin - Determines the motor speed via PWM signal
int motorB_phase = 12;   // D6 pin
int motorB_enable = 14;  // D5 pin
int rgb_R = 4;   // D2 pin - RGB Led R pin
int rgb_G = 5;   // D1 pin - RGB Led G pin
int rgb_B = 16;  // D0 pin - RGB Led B pin

// Define variables to store information about the states the motors
int motorA_direction;
int motorA_speed;
int motorB_direction;
int motorB_speed;

/*
 * Confıgure these to suit your setup
 */
const char* mqtt_server = "192.168.1.107";  // Mosquitto broker IP address
const char* ssid = "CANBOLAT_plus";   // Router SSID
const char* password = "canbolat19";  // Router password


WiFiClient esp; // Creates a client that can connect to a specified internet IP address and port as defined in client.connect()

void callback(char* topic, byte* payload, unsigned int length);  // (necessary to prevent compiling error)

PubSubClient client(mqtt_server, 1883, callback, esp);  // Creates a fully configured client instance.


void setup()
{
  Serial.begin(115200);  // Start serial communication for debugging purposes

  pinMode(motorA_enable, OUTPUT);
  pinMode(motorA_phase, OUTPUT);
  pinMode(motorB_enable, OUTPUT);
  pinMode(motorB_phase, OUTPUT);
  pinMode(rgb_R, OUTPUT);
  pinMode(rgb_G, OUTPUT);
  pinMode(rgb_B, OUTPUT);
  digitalWrite(rgb_R, HIGH);
  digitalWrite(rgb_G, HIGH);
  digitalWrite(rgb_B, HIGH);

  connectToWifi();    // Run the function that establishes a wifi connection
  connectToBroker();  // Run the function that establishes a connection to MQTT broker/server

  delay(100); // Wait a bit before starting the main loop
}


void loop()
{
  if (WiFi.status() != WL_CONNECTED)  // Reconnect if wifi connection is lost
  {
    Serial.println("Wifi connection is lost. Re-connecting...");
    connectToWifi();
    // indicate the status using RGB LED
  }
  if (client.connected() == false)  // Reconnect if mqtt connection is lost
  {
    Serial.println("MQTT connection is lost. Re-connecting...");
    connectToBroker();
    // indicate the status using RGB LED
  }

  client.loop();  // This should be called regularly to allow the client to process incoming messages and maintain its connection to the server

  delay(10);  // Must delay to allow ESP8266 WIFI functions to run ?
}

void connectToWifi()
{
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  
  while (WiFi.status() != WL_CONNECTED) // Wait until the wifi connection is established
  {
  	digitalWrite(rgb_G, LOW);  // Blink in green
    delay(100);
    digitalWrite(rgb_G, HIGH);
    delay(100);
    Serial.print(".");
  }
  Serial.print("\nWiFi connected. ");
  Serial.print("IP address is: ");
  Serial.println(WiFi.localIP());

  digitalWrite(rgb_G, LOW);  // Indicate succesful connection in green for a few seconds
  delay(3000);
  digitalWrite(rgb_G, HIGH);
}

void connectToBroker()
{
  if (WiFi.status() == WL_CONNECTED)  // Check Wifi connection before attemping to connect to MQTT
  {
    while (!client.connected())  // Loop until we're connected to the MQTT server
    {
      Serial.print("\nAttempting MQTT connection to ");
      Serial.print(mqtt_server);
      String clientID = "me462_esp8266-"; clientID += String(random(0xffff), HEX);  // Generate a random client ID

      if (client.connect(clientID.c_str()))  // If client is connected
      {
        Serial.println("\tMQTT Connected");
        client.subscribe("topic_name");  // Subscribe to a topic
      }
      else
      {
        Serial.println(" ----> FAILED. Re-trying... ");
        delay(1000);
        //abort();
      }
    }
  }
  else
  {
    Serial.println("Wifi connection is lost. Re-connecting...");
    connectToWifi();
  }
}


/*
 * This function is called when new messages arrive at the client.
 *  - topic (const char[]) - the topic the message arrived on
 *  - payload (byte[]) - the message payload
 *  - length (unsigned int) - the length of the message payload
 */
void callback(char* topic, byte* payload, unsigned int length) // This function is called when new messages arrive at the client.
{
	motorA_direction = payload[0]-48;
	motorB_direction = payload[3]-48;
  motorA_speed = (payload[1]-48)*10 + (payload[2]-48);
  motorB_speed = (payload[4]-48)*10 + (payload[5]-48);


  Serial.println(motorA_direction);
  Serial.println(motorA_speed);

  Serial.println(motorB_direction);
  Serial.println(motorB_speed);


  //Here, do what needs to be done according to the message 

  digitalWrite(motorA_phase, motorA_direction);  // Set the direction of motor A
  analogWrite(motorA_enable, motorA_speed);      // Set the speed of motor A

  digitalWrite(motorB_phase, motorB_direction);  // Set the direction of motor B
  analogWrite(motorB_enable, motorB_speed);      // Set the speed of motor B

  digitalWrite(rgb_R,HIGH);
  digitalWrite(rgb_G,HIGH);
  digitalWrite(rgb_B,HIGH);

}
