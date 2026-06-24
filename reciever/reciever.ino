#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK   4
#define LORA_MISO  5
#define LORA_MOSI  6
#define LORA_CS    7
#define LORA_RST   8
#define LORA_DIO0  10

void setup() {
  Serial.begin(115200);

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }

  Serial.println("LoRa Receiver Ready");
}

void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    String temp = "";

    while (LoRa.available()) {
      temp += (char)LoRa.read();
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" C");
  }
}