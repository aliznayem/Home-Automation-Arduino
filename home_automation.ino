#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

String readString;
int tempPin = A6;
int lightSensorPin = A5;
int fanPin = 5;
int lightPin = 4;
int dimLightPin = 3;
int plugPin = 13;
int buzzarPin = 11;
boolean autofan, autolight, autodim;
String light = "Light    :OFF", fan = "Fan      :OFF", dim = "Dim      :OFF", plug = "External :OFF";
unsigned long currentMillis;
//unsigned long currentMillisSleep;
long sleepPresent = 0;
long sleepPresentf = 0;
long previousMillis = 0;
long interval = 500;
int sleep = 0;
int sleepf = 0;

// Software SPI (slower updates, more flexible pin options):
// pin 6 - Serial clock out (SCLK)
// pin 7 - Serial data out (DIN)
// pin 8 - Data/Command select (D/C)
// pin 9 - LCD chip select (CS)
// pin 10 - LCD reset (RST)
Adafruit_PCD8544 tDisplay = Adafruit_PCD8544(6, 7, 8, 9, 10);

void setup() {
  Serial.begin(9600);
  tDisplay.begin();
  tDisplay.setContrast(60);
  tDisplay.clearDisplay();
  tDisplay.setTextSize(1);
  tDisplay.setTextColor(BLACK);
  tDisplay.setCursor(20,15);
  tDisplay.print("ASSALAMU-");
  tDisplay.setCursor(20,24);
  tDisplay.print("ALAIKUM!");
  tDisplay.display();
  delay(2000);
  tDisplay.clearDisplay();
  pinMode(tempPin, INPUT);
  pinMode(lightSensorPin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(dimLightPin, OUTPUT);
  pinMode(plugPin, OUTPUT);
  digitalWrite(fanPin, HIGH);
  digitalWrite(lightPin, HIGH);
  digitalWrite(dimLightPin, HIGH);
  digitalWrite(plugPin, HIGH);
}

void loop() {
  float tempC = (5.0 * analogRead(tempPin) * 100.0) / 1024;
  int lReading = analogRead(lightSensorPin);
  
  currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    tDisplay.clearDisplay();
    tDisplay.setCursor(15,0);
    tDisplay.print("Temp: ");
    tDisplay.print(int(tempC));
    tDisplay.println("C");
    tDisplay.println("-------------");
    if(autolight) tDisplay.println("Light (Auto)");
    else tDisplay.println(light);
    if(autofan) tDisplay.println("Fan (Auto)");
    else tDisplay.println(fan);
    if(autodim) tDisplay.println("Dim (Auto)");
    else tDisplay.println(dim);
    tDisplay.println(plug);
    tDisplay.display();
  }
  
  while(Serial.available()) {
    delay(3);
    char c = Serial.read();
    readString += c;
  }
  if(readString.length()>0) {
    if(readString == "lon") {
      Serial.println("Light is ON");
      digitalWrite(lightPin, LOW);
      digitalWrite(dimLightPin, HIGH);
      tone(buzzarPin, 440, 100);
      light = "Light    :ON";
    
    }
    else if(readString == "loff") {
      Serial.println("Light is OFF");
      digitalWrite(lightPin, HIGH);
      tone(buzzarPin, 440, 100);
      light = "Light    :OFF";
      sleep = 0;
    }
    else if(readString == "don") {
      Serial.println("Dim Light is ON");
      digitalWrite(dimLightPin, LOW);
      digitalWrite(lightPin, HIGH);
      tone(buzzarPin, 440, 100);
      dim = "Dim      :ON";
    }
    else if(readString == "doff") {
      Serial.println("Dim Light is OFF");
      digitalWrite(dimLightPin, HIGH);
      tone(buzzarPin, 440, 100);
      dim = "Dim      :OFF";
    }
    else if(readString == "fon") {
      Serial.println("Fan is ON");
      digitalWrite(fanPin, LOW);
      tone(buzzarPin, 440, 100);
      fan = "Fan      :ON";
    }
    else if(readString == "foff") {
      Serial.println("Fan is OFF");
      digitalWrite(fanPin, HIGH);
      tone(buzzarPin, 440, 100);
      fan = "Fan      :OFF";
      sleepf = 0;
    }
    else if(readString == "eon") {
      Serial.println("Plug Switch is ON");
      digitalWrite(plugPin, LOW);
      tone(buzzarPin, 440, 100);
      plug = "External :ON";
    }
    else if(readString == "eoff") {
      Serial.println("Plug Switch is OFF");
      digitalWrite(plugPin, HIGH);
      tone(buzzarPin, 440, 100);
      plug = "External :OFF";
    }
    else if(readString == "afan") {
      Serial.println("Autofan Mode is Activated!");
      digitalWrite(fanPin, HIGH);
      autofan = true;
    }
    else if(readString == "afanoff") {
      Serial.println("Autofan Mode is Deactivated");
      autofan = false;
    }
    else if(readString == "alight") {
      Serial.println("Autolight Mode is Activated!");
      digitalWrite(lightPin, HIGH);
      autolight = true;
      autodim = false;
    }
    else if(readString == "alightoff") {
      Serial.println("Autolight Mode is Deactivated");
      autolight = false;
    }
    else if(readString == "adim") {
      Serial.println("Autodimlight Mode is Activated!");
      digitalWrite(dimLightPin, HIGH);
      autodim = true;
      autolight = false;
    }
     else if(readString == "adimoff") {
      Serial.println("Autodimlight Mode is Deactivated");
      autodim = false;
     }
    else if(readString == "lon15") {
      digitalWrite(lightPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Light is ON for 15 minutes");
      light = "Light    :ON";
      sleep = 15;
      sleepPresent = millis();
    }
    else if(readString == "lon30") {
      digitalWrite(lightPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Light is ON for 30 minutes");
      light = "Light    :ON";
      sleep = 30;
      sleepPresent = millis();
    }
    else if(readString == "lon45") {
      digitalWrite(lightPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Light is ON for 45 minutes");
      light = "Light    :ON";
      sleep = 45;
      sleepPresent = millis();
    }
    else if(readString == "lon60") {
      digitalWrite(lightPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Light is ON for 60 minutes");
      light = "Light    :ON";
      sleep = 60;
      sleepPresent = millis();
    }
    else if(readString == "fon15") {
      digitalWrite(fanPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Fan is ON for 15 minutes");
      fan = "Fan      :ON";
      sleepf = 15;
      sleepPresentf = millis();
    }
    else if(readString == "fon30") {
      digitalWrite(fanPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Fan is ON for 30 minutes");
      fan = "Fan      :ON";
      sleepf = 30;
      sleepPresentf = millis();
    }
    else if(readString == "fon45") {
      digitalWrite(fanPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Fan is ON for 45 minutes");
      fan = "Fan      :ON";
      sleepf = 45;
      sleepPresentf = millis();
    }
    else if(readString == "fon60") {
      digitalWrite(fanPin, LOW);
      tone(buzzarPin, 440, 100);
      Serial.println("Fan is ON for 60 minutes");
      fan = "Fan      :ON";
      sleepf = 60;
      sleepPresentf = millis();
    }
    else if(readString == "soff") {
      sleep = 0;
      sleepf = 0;
    }
    else if(readString == "temp") {
      Serial.print("Temperature is ");
      Serial.print(tempC);
      Serial.println(" degree Celcius");
    }
    else Serial.println("Please Enter Right Command!");
    readString="";
  }
  if(autofan == true) {
    if(int(tempC) > 25) {
      digitalWrite(fanPin, LOW);
    }
    else {
      digitalWrite(fanPin, HIGH);
    }
  }
  if(autolight == true) {
    if(lReading < 100) {
      digitalWrite(lightPin, LOW);
    }
  }
  if(autodim == true) {
    if(lReading < 100) {
      digitalWrite(dimLightPin, LOW);
    }
  }
  if(sleep>0) {
    if(currentMillis - sleepPresent + 500 > sleep*1000.0*60.0) { 
      digitalWrite(lightPin, HIGH);
      tone(buzzarPin, 440, 100);
      light = "Light    :OFF";
      sleep = 0;
    }
  }
  if(sleepf>0) {
    if(currentMillis - sleepPresentf + 500 > sleepf*1000.0*60.0) { 
      digitalWrite(fanPin, HIGH);
      tone(buzzarPin, 440, 100);
      fan = "Fan      :OFF";
      sleepf = 0;
    }
  }
}
