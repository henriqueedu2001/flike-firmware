#include <digital_key.h>
#include <binutils.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mbedtls/cipher.h"
#include "mbedtls/cmac.h"

#define AES_CMAC_KEY_SIZE_IN_BITS 256
#define AES_CMAC_TAG_SIZE_IN_BYTES 16
#define PAYLOAD_SIZE_IN_BYTES 32

uint8_t aes_cmac_key[32] = {
    0x38, 0xf9, 0xde, 0xf2, 0xcf, 0x55, 0x06, 0x1d,
    0xad, 0xa9, 0xe0, 0xc5, 0x6d, 0xde, 0x09, 0xb4,
    0x48, 0x50, 0xd4, 0x80, 0xd8, 0xc3, 0x89, 0x3f,
    0xbd, 0x37, 0x38, 0xe2, 0xe7, 0x98, 0x8c, 0xb9
};

/**
 * @brief Validates the digital key by calculating the AES-CMAC of the payload and comparing it with the tag
 * @param message The digital key message containing the payload and the tag
 * @param messageLength The length of the digital key message
 * @return true if the digital key is valid, false otherwise
 */
bool validateDigitalKey(const uint8_t *message, size_t messageLength) {
    bool validity = true;

    uint8_t mac[16];
    uint8_t payload[32];
    uint8_t tag[16];

    memcpy(payload, message, PAYLOAD_SIZE_IN_BYTES);
    memcpy(tag, message + PAYLOAD_SIZE_IN_BYTES, AES_CMAC_TAG_SIZE_IN_BYTES);
    AES_CMAC(aes_cmac_key, payload, PAYLOAD_SIZE_IN_BYTES, mac);

    for(int i = 0; i < AES_CMAC_TAG_SIZE_IN_BYTES; i++)
        if(mac[i] != tag[i]) validity = false;
    
    return validity;
}

/**
 * @brief Calculates the AES-CMAC of the message using the provided private key
 * @param privateKey The private key used for the AES-CMAC calculation
 * @param message The message for which the AES-CMAC will be calculated
 * @param messageLength The length of the message
 * @param mac The output buffer where the calculated AES-CMAC will be stored
 */
void AES_CMAC(uint8_t *privateKey, uint8_t *message, int messageLength, uint8_t *mac) {
    const mbedtls_cipher_info_t *cipher_info;
    cipher_info = mbedtls_cipher_info_from_type(MBEDTLS_CIPHER_AES_256_ECB);
    if(cipher_info == NULL) return;
    mbedtls_cipher_cmac(cipher_info, privateKey, AES_CMAC_KEY_SIZE_IN_BITS, message, messageLength, mac);
    Serial.print("---\n");
    printBinary(message, messageLength);
    printBinary(privateKey, 32);
    printBinary(mac, AES_CMAC_TAG_SIZE_IN_BYTES);
    Serial.print("---\n");
}
