#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;
#define DEBUG_SW 0
#define S1 32
#define R1 15
#define S2 35
#define R2 2
#define S3 34
#define R3 4
#define S4 39
#define R4 22
#define LED1 26
#define LED2 25
#define LED3 27
#define Buzzer 21
int MODE = 0;


char ssid[] = "Tenda_ACB288";
char pass[] = "prasad07";    // Set password to "" for open networks.
char auth[] = "TtV53cCCXVVnsUvLwfzior_KPLhUmNEq";   // Auth Token in the Blynk App.
int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag2_previous_I = 0;
int switch_ON_Flag3_previous_I = 0;
int switch_ON_Flag4_previous_I = 0;
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); 
  digitalWrite(R1, pinValue);
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(R2, pinValue);
}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  digitalWrite(R3, pinValue);
}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  digitalWrite(R4, pinValue);
}
void with_internet()
{
  if (digitalRead(S1) == HIGH)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(R1, LOW);
      if (DEBUG_SW) Serial.println("Relay1- ON");
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch1 -ON");
  }
  if (digitalRead(S1) == LOW )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(R1, HIGH);
      if (DEBUG_SW) Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch1 OFF");
  }
  if (digitalRead(S2) == HIGH)
  {
    if (switch_ON_Flag2_previous_I == 0 )
    {
      digitalWrite(R2, LOW);
      if (DEBUG_SW)  Serial.println("Relay2- ON");
      Blynk.virtualWrite(V2, 0);
      switch_ON_Flag2_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch2 -ON");
  }
  if (digitalRead(S2) == LOW )
  {
    if (switch_ON_Flag2_previous_I == 1)
    {
      digitalWrite(R2, HIGH);
      if (DEBUG_SW) Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 1);
      switch_ON_Flag2_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch2 OFF");
  }
  if (digitalRead(S3) == HIGH)
  {
    if (switch_ON_Flag3_previous_I == 0 )
    {
      digitalWrite(R3, LOW);
      if (DEBUG_SW) Serial.println("Relay3- ON");
      Blynk.virtualWrite(V3, 0);
      switch_ON_Flag3_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch3 -ON");
  }
  if (digitalRead(S3) == LOW )
  {
    if (switch_ON_Flag3_previous_I == 1)
    {
      digitalWrite(R3, HIGH);
      if (DEBUG_SW) Serial.println("Relay3 OFF");
      Blynk.virtualWrite(V3, 1);
      switch_ON_Flag3_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch3 OFF");
  }
  if (digitalRead(S4) == HIGH)
  {
    if (switch_ON_Flag4_previous_I == 0 )
    {
      digitalWrite(R4, LOW);
      if (DEBUG_SW) Serial.println("Relay4- ON");
      Blynk.virtualWrite(V4, 0);
      switch_ON_Flag4_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch4 -ON");
  }
  if (digitalRead(S4) == LOW )
  {
    if (switch_ON_Flag4_previous_I == 1)
    {
      digitalWrite(R4, HIGH);
      if (DEBUG_SW) Serial.println("Relay4 OFF");
      Blynk.virtualWrite(V4, 1);
      switch_ON_Flag4_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch4 OFF");
  }
}

void without_internet()
{
  digitalWrite(R1, digitalRead(S1));
  digitalWrite(R2, digitalRead(S2));
  digitalWrite(R3, digitalRead(S3));
  digitalWrite(R4, digitalRead(S4));
}

void checkBlynk() { // called every 3 seconds

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    MODE = 1;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  if (isconnected == true) {
    MODE = 0;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  }
}

void setup()
{
  if (DEBUG_SW) Serial.begin(9600);
  pinMode(S1, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(S2, INPUT);
  pinMode(R2, OUTPUT);
  pinMode(S3, INPUT);
  pinMode(R3, OUTPUT);
  pinMode(S4, INPUT);
  pinMode(R4, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, HIGH);
  delay(200);
  digitalWrite(LED3, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(500);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED2, HIGH);
  delay(200);
  digitalWrite(LED3, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynk); // checks if connected to Blynk server every 3 seconds
  Blynk.config(auth); 
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW) Serial.println("Not Connected");
  }
  else
  {
    if (DEBUG_SW) Serial.println(" Connected");
    Blynk.run();
  }
  timer.run();
  if (MODE == 0)
    with_internet();
  else
    without_internet();
}
