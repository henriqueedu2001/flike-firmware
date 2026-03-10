#include <Arduino.h>

bool validateDigitalKey(const uint8_t *message, size_t messageLength);
void AES_CMAC(uint8_t *privateKey, uint8_t *message, int messageLength, uint8_t *mac);
