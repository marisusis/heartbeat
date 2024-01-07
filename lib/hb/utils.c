#include "hb.h"

void uint16_to_bytes(uint16_t number, uint8_t* bytes) {
    bytes[0] = (number >> 8) & 0xFF; // Extracts the MSB
    bytes[1] = number & 0xFF;        // Extracts the LSB
}

void uint32_to_bytes(uint32_t number, uint8_t* bytes) {
    bytes[0] = (number >> 24) & 0xFF; // Extracts the MSB
    bytes[1] = (number >> 16) & 0xFF; 
    bytes[2] = (number >> 8) & 0xFF;  
    bytes[3] = number & 0xFF;         // Extracts the LSB
}

void uint64_to_bytes(uint64_t number, uint8_t* bytes) {
    bytes[0] = (number >> 56) & 0xFF; // Extracts the MSB
    bytes[1] = (number >> 48) & 0xFF; 
    bytes[2] = (number >> 40) & 0xFF; 
    bytes[3] = (number >> 32) & 0xFF; 
    bytes[4] = (number >> 24) & 0xFF; 
    bytes[5] = (number >> 16) & 0xFF; 
    bytes[6] = (number >> 8) & 0xFF;  
    bytes[7] = number & 0xFF;         // Extracts the LSB
}

uint16_t bytes_to_uint16(uint8_t* bytes) {
    return ((uint16_t)bytes[0] << 8) | (uint16_t)bytes[1];
}

uint32_t bytes_to_uint32(uint8_t* bytes) {
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | (uint32_t)bytes[3];
}

uint64_t bytes_to_uint64(uint8_t* bytes) {
    return ((uint64_t)bytes[0] << 56) | ((uint64_t)bytes[1] << 48) |
           ((uint64_t)bytes[2] << 40) | ((uint64_t)bytes[3] << 32) |
           ((uint64_t)bytes[4] << 24) | ((uint64_t)bytes[5] << 16) |
           ((uint64_t)bytes[6] << 8) | (uint64_t)bytes[7];
}