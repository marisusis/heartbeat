#include "hb.h"

uint8_t* uint16_to_bytes(uint16_t number) {
    static uint8_t bytes[2];
    bytes[0] = (number >> 8) & 0xFF; // Extracts the MSB
    bytes[1] = number & 0xFF;        // Extracts the LSB
    return bytes;
}

uint8_t* uint32_to_bytes(uint32_t number) {
    static uint8_t bytes[4];
    bytes[0] = (number >> 24) & 0xFF; // Extracts the MSB
    bytes[1] = (number >> 16) & 0xFF; 
    bytes[2] = (number >> 8) & 0xFF;  
    bytes[3] = number & 0xFF;         // Extracts the LSB
    return bytes;
}

uint16_t bytes_to_uint16(uint8_t* bytes) {
    return ((uint16_t)bytes[0] << 8) | (uint16_t)bytes[1];
}

uint32_t bytes_to_uint32(uint8_t* bytes) {
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | (uint32_t)bytes[3];
}