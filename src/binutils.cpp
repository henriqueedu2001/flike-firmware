#include <binutils.h>

/**
 * @brief Prints the binary data in hexadecimal format to the serial output
 * @param data The binary data to be printed
 * @param length The length of the binary data
 */
void printBinary(uint8_t *data, size_t length) {
    for(int i = 0; i < length; i++) {
        uint8_t payloadByte = data[i];
        if(payloadByte <= 15) Serial.print("0"); /* 0 left padding for 0 to F */
        Serial.print(payloadByte, HEX);
        Serial.print(" ");
    }
    Serial.println();
}