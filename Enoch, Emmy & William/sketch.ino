#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT22 Settings
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// PIR Sensor
#define PIR_PIN 13

// LDR
#define LDR_PIN 34

// LEDs
#define GREEN_LED 18
#define RED_LED 19

// Buzzer
#define BUZZER 23

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(PIR_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Classroom Monitor");
  display.display();

  delay(2000);
}

void loop() {

  // Read DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read PIR
  int motion = digitalRead(PIR_PIN);

  // Read LDR
  int lightValue = analogRead(LDR_PIN);

  String occupancyStatus;
  String lightStatus;

  // Occupancy
  if (motion == HIGH) {
    occupancyStatus = "Present";
    digitalWrite(GREEN_LED, HIGH);
  } else {
    occupancyStatus = "Empty";
    digitalWrite(GREEN_LED, LOW);
  }

  // Light Level
  if (lightValue > 2000) {
    lightStatus = "Bright";
  } else {
    lightStatus = "Dim";
  }

  // Temperature Alert
  bool alert = false;

  if (temperature > 30 || temperature < 18) {
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 1000);
    alert = true;
  } else {
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);
  }

  // Dark Room Alert
  if (lightValue < 1000) {
    digitalWrite(RED_LED, HIGH);

    if (!alert) {
      tone(BUZZER, 800);
    }
  }

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("CLASSROOM STATUS");

  display.setCursor(0, 15);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 28);
  display.print("Hum : ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 41);
  display.print("Light: ");
  display.println(lightStatus);

  display.setCursor(0, 54);
  display.print("Occup: ");
  display.println(occupancyStatus);

  display.display();

  // Serial Monitor
  Serial.println("----- Classroom Data -----");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light Value: ");
  Serial.println(lightValue);

  Serial.print("Occupancy: ");
  Serial.println(occupancyStatus);

  delay(2000);
}