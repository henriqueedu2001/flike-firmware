#include <Arduino.h>
#include <qr_code.h>

#define BAUD_RATE 115200

void setup() {
    Serial.begin(BAUD_RATE);
    setupQRCodeReader();
    resumeQRCodeReading();
}

void loop() {
    QRCodePayload qrcodePayload = readQRCode();
    printQRCodePayload(qrcodePayload, HEX);
}