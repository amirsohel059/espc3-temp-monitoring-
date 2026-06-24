#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LORA_SCK   4
#define LORA_MISO  5
#define LORA_MOSI  6
#define LORA_CS    7
#define LORA_RST   8
#define LORA_DIO0  10

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  sensors.begin();

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  Serial.println("Starting LoRa...");

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  Serial.println("LoRa init success!");
}

void loop() {

  sensors.requestTemperatures();

  float tempC = sensors.getTempCByIndex(0);

  String msg = String(tempC, 2);

  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();

  Serial.print("Sent Temperature: ");
  Serial.print(tempC);
  Serial.println(" C");

  delay(1000);
}