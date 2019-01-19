#define BLYNK_PRINT Serial

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ONE_WIRE_PIN D4

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

char auth[] = "r2p3r1qp85574s22968o6q43oqopo0rn";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "JYNA1-643Y3E";
char pass[] = "7RsWvO7SD23NatS5";

const int buttonPin = D1;

int buttonCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

BlynkTimer timer;
void myTimerEvent()
{
    Blynk.virtualWrite(V5, sensors.getTempCByIndex(0));
    Blynk.virtualWrite(V6, sensors.getTempCByIndex(1));
    Blynk.virtualWrite(V7, buttonCounter);
}

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  if (buttonCounter == 300) {
    Blynk.email("Poszlo 300", "Doladuj do pieca");
    Blynk.notify(String("Poszlo 300, doladuj"));
    buttonCounter++;
    }

  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState){
    Serial.println("Elo");
    if (buttonState == HIGH) {
      buttonCounter++;
    }
  }

  lastButtonState = buttonState;
  delay(50);

  sensors.requestTemperatures();
  Blynk.run();
  timer.run();
}


BLYNK_WRITE(V2) {
 int pinValue = param.asInt();
 if (pinValue == 1) {
 buttonCounter = 0;
 }
}
