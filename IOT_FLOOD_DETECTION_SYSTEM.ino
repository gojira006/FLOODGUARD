#define BLYNK_TEMPLATE_ID           "TMPL6k3_0ix74"
#define BLYNK_TEMPLATE_NAME         "IOT FLOOD DETECTION"
#define BLYNK_AUTH_TOKEN            "dwx6pPAnQV0uhYblpS48dE1F5XZcGkrV"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>


// Set password to "" for open networks.
char ssid[] = "PLDTHOMEFIBR24390";
char pass[] = "PLDTWIFIgnb2c";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 38400

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

// Define pin assignments
const int trigPin = 12;
const int echoPin = 10;
const int waterSensorPin = A0;

// Define constants // Speed of sound in cm/microsecond
const float SOUND_SPEED = 0.034;
const int MAX_DISTANCE = 10;    // Maximum distance for the HC-SR04 sensor in cm
const int MAX_WATER_LEVEL = 700;  // Maximum water level reading from the HW-038 sensor
const int MAX_WATER_HEIGHT_CM = 10;

const int LOW_RISK_THRESHOLD = 15;
const int MODERATE_RISK_THRESHOLD = 50;
const int HIGH_RISK_THRESHOLD = 70;

// Variables for sensor readings
char floodRisk[30];
long duration;
float cm;
double waterLevel;
double waterPercentage;
double waterLevelPercentage;  
double waterHeightCM;

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
  timer.setInterval(1000L, myTimer); 
}


void loop()
{
  readDistance();
  Blynk.run();
  timer.run();
}


void readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  cm = duration * SOUND_SPEED / 2;
  waterLevelPercentage = map(cm, 0, MAX_DISTANCE, 100, 0);
}


void myTimer(){

  if (waterLevelPercentage < LOW_RISK_THRESHOLD) {
    strcpy(floodRisk, "NORMAL");
  } else if (waterLevelPercentage >= LOW_RISK_THRESHOLD && waterLevelPercentage < MODERATE_RISK_THRESHOLD) {
    strcpy(floodRisk, "LOW FLOOD RISK");
  } else if (waterLevelPercentage >= MODERATE_RISK_THRESHOLD && waterLevelPercentage < HIGH_RISK_THRESHOLD) {
    strcpy(floodRisk, "MODERATE FLOOD RISK");
  } else {
    strcpy(floodRisk, "HIGH FLOOD RISK");
  }

  Serial.print("Water level (HW-038): ");
  Serial.print(waterLevel);
  Serial.print("Water level (HC-SR04): ");
  Serial.print(waterLevelPercentage);
  Serial.println("%");
  Serial.println(floodRisk);
 
  waterLevel = analogRead(waterSensorPin);
  //waterPercentage = (waterLevel / (float)MAX_WATER_LEVEL) * 100.0;
  waterHeightCM = map(waterLevel, 0, MAX_WATER_LEVEL, 0, MAX_WATER_HEIGHT_CM);

  Blynk.virtualWrite(V0, waterLevel);
  Blynk.virtualWrite(V1, floodRisk);

  
}

