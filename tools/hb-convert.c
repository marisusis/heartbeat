#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>
#include "hb.h"

hb_tick* parse_string_to_tick(char* line, size_t len) {
    size_t index = 0;
    size_t data_index = 0;
    uint16_t* data = malloc(len / 5 * sizeof(uint16_t));

    if (data == NULL) {
        exit(1);
    }

    hb_tick* tick = hb_tick_malloc();

    // Parse time
    while (line[index] != ',') {
        index++;
    }

    index++;

    // max number is 1024
    while (index < len) {
        char parsed_number[4];
        memset(parsed_number, 0, 4);
        uint8_t parse_index = 0;

        while (line[index] != ',' && index < len) {
            parsed_number[parse_index++] = line[index];
            index++;
        }

        data[data_index++] = 123; //(uint16_t) atoi(parsed_number);
        
        index++;
    }

    tick->data = data;
    tick->data_count = data_index;

    return tick;
}

char* uint16_to_hex_string(uint16_t* array, size_t size) {
    // Each uint16_t will need 4 characters for hex representation
    // and 1 character for space or null terminator.
    char* hexString = malloc((size * 5) * sizeof(char));
    if (hexString == NULL) {
        return NULL; // Allocation failed
    }

    for (size_t i = 0; i < size; i++) {
        // Write four hex digits and a space for each 16-bit number.
        sprintf(&hexString[i * 5], "%04X ", array[i]);
    }

    hexString[size * 5 - 1] = '\0'; // Replace the last space with a null terminator.
    return hexString;
}

char* uint8_to_hex_string(uint8_t* array, size_t size) {
    // Each uint8_t will need 2 characters for hex representation
    // and 1 character for space or null terminator.
    char* hexString = malloc((size * 3) * sizeof(char));
    if (hexString == NULL) {
        return NULL; // Allocation failed
    }

    for (size_t i = 0; i < size; i++) {
        // Write two hex digits and a space for each byte.
        // The '%02X' format prints the hex value in two characters, adding a leading zero if necessary.
        sprintf(&hexString[i * 3], "%02X ", array[i]);
    }

    hexString[size * 3 - 1] = '\0'; // Replace the last space with a null terminator.
    return hexString;
}

void parse_line(char* line, size_t len, uint16_t** output, size_t* output_len) {

    uint16_t index = 0;

    uint16_t* data = malloc(len / 5 * sizeof(uint16_t));
    size_t data_index = 0;

    // Parse time
    while (line[index] != ',') {
        index++;
    }

    index++;

    // max number is 1024
    while (index < len) {
        char parsed_number[4];
        memset(parsed_number, 0, 4);
        uint8_t parse_index = 0;

        while (line[index] != ',' && index < len) {
            parsed_number[parse_index++] = line[index];
            index++;
        }

        data[data_index++] = (uint16_t) atoi(parsed_number);
        
        index++;
    }

    *output = data;
    *output_len = data_index;

}

uint8_t* uint16_to_bytes(uint16_t value) {
    uint8_t* bytes = malloc(sizeof(uint8_t) * 2);
    bytes[0] = value >> 8;
    bytes[1] = value & 0xFF;
    return bytes;
}

int main(int argc, char** argv) {

    // First argument should be filename
    if (argc != 3) {
        printf("Must provide input and output filename\n");
        return 1;
    }

    char* input_filename = argv[1];
    char* output_filename = argv[2];

    printf("Using file %s\n", input_filename);

    FILE* input_file = fopen(input_filename, "ro");
    if (input_file == NULL) {
        printf("Unable to open file \"%s\"!\n", input_filename);
        return 1;
    }

    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Unable to open file \"%s\"!\n", output_filename);
        return 1;
    }

    char magic_number[4] = {HB_FILE_CODE, HB_FILE_CODE};
    fwrite(magic_number, sizeof(char), 4, output_file);

    char line_header[2] = {HB_FILE_CODE, HB_HEADER_LINE};

    // TODO maybe expect some sort of header?

    uint8_t* line = NULL;
    size_t len = 0;
    ssize_t read;
    char* parsed = malloc(1000);
    memset(parsed, 0, 1000);

    while ((read = getline(&line, &len, input_file)) != -1) {
        uint16_t* parsed;
        size_t parsed_len = 0;

        hb_tick* tick = parse_string_to_tick(line, (size_t) read);

        fwrite(line_header, sizeof(char), 2, output_file);

        for (size_t i = 0; i < tick->data_count; i++) {
            uint8_t* bytes = uint16_to_bytes(tick->data[i]);
            fwrite(bytes, sizeof(uint8_t), 2, output_file);
            free(bytes);
        }

        // fwrite(tick->data, sizeof(uint16_t), tick->data_count, output_file);

        hb_tick_free(tick);
    }

    free(parsed);
    fclose(input_file);
    fclose(output_file);
}