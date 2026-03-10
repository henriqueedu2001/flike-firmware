#include <Arduino.h>
#include <qr_code.h>
#include <digital_key.h>

#define BAUD_RATE 115200

#define LED_BUILTIN 4

void setup() {
    Serial.begin(BAUD_RATE);
    pinMode(LED_BUILTIN, OUTPUT);
    setupQRCodeReader();
    resumeQRCodeReading();
}

void loop() {
    QRCodePayload qrcodePayload = readQRCode();
    if(qrcodePayload.successfulRead) {
        printQRCodePayload(qrcodePayload, HEX);
        bool isValid = validateDigitalKey(qrcodePayload.rawPayload, qrcodePayload.payloadLength);
        Serial.print("Digital Key Valid: ");
        Serial.print(isValid ? "Yes\n" : "No\n");
        delay(1000);
    }
}