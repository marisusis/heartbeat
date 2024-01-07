#include "hb.h"

hb_file* hb_file_open(char* filename) {
    FILE* file = fopen(filename, "rwb");

    if (file == NULL) {
        return NULL;
    }

    hb_file* hb_file = malloc(sizeof(hb_file));
    hb_file->source_file = file;


    // HANDLE FILE HEADER
    uint8_t* file_header_bytes = malloc(sizeof(hb_file_header));
    if (fread(file_header_bytes, sizeof(hb_file_header), 1, file) < 1) {
        fclose(file);
        return NULL;
    }
    hb_file->header = parse_file_header(file_header_bytes);
    free(file_header_bytes);

    hb_file->ticks = malloc(hb_file->header.tick_count * sizeof(hb_tick));

    printf("File: %s\n", filename);
    printf("Magic: %x\n", hb_file->header.magic);
    printf("File Version: %d.%d\n", hb_file->header.version >> 8, hb_file->header.version & 0xff);
    printf("Tick Count: %d\n", hb_file->header.tick_count);

    // HANDLE TICKS
    for (size_t i = 0; i < hb_file->header.tick_count; i++) {
        uint8_t* tick_header_bytes = malloc(sizeof(hb_tick_header));
        if (fread(tick_header_bytes, sizeof(hb_tick_header), 1, file) < 1) {
            hb_file_close(hb_file);
            return NULL;
        }
        hb_tick_header tick_header = parse_tick_header(tick_header_bytes);
        free(tick_header_bytes);

        printf("Tick: %d\n", i);
        printf("Tick Header Magic: %x\n", tick_header.magic);
        printf("Tick Header Timestamp: %d\n", tick_header.utc_timestamp);
        printf("Tick Header Checksum: %x\n", tick_header.checksum);
        printf("Tick Header Data Count: %d\n", tick_header.data_count);

        // fseek(file, tick_header.data_count * 2, SEEK_CUR);
        printf("ticks: %x\n", hb_file->ticks);
        hb_tick tick;
        tick.header = tick_header;
        tick.data = malloc(tick_header.data_count * sizeof(uint16_t));
        // Get each value
        for (size_t j = 0; j < tick_header.data_count; j++) {
            uint16_t a;
            if (fread(&a, sizeof(uint16_t), 1, file) < 1) {
                printf("Error reading tick data!\n");
            }
        }

        hb_file->ticks[i] = tick;
    }

    uint8_t* tick_header_bytes = malloc(sizeof(hb_tick_header));
    if (fread(tick_header_bytes, sizeof(hb_tick_header), 1, file) < 1) {
        hb_file_close(hb_file);
        return NULL;
    }
    hb_tick_header tick_header = parse_tick_header(tick_header_bytes);
    free(tick_header_bytes);



    return hb_file;
}

void hb_file_close(hb_file* file) {
    fclose(file->source_file);
    hb_file_free(file);
}

hb_file* hb_file_malloc() {
    hb_file* hb_file = malloc(sizeof(hb_file));
    hb_file->source_file = NULL;
    return hb_file;
}

void hb_file_free(hb_file* file) {
    free(file);
}

hb_file_header parse_file_header(uint8_t* data) {
    hb_file_header header;
    header.magic = bytes_to_uint16(data);
    data += sizeof(uint16_t);
    header.version = bytes_to_uint16(data);
    data += sizeof(uint16_t);
    header.tick_count = bytes_to_uint32(data);
    return header;
}


void file_header_to_bytes(hb_file_header header, uint8_t* bytes) {
    uint16_to_bytes(header.magic, bytes);
    bytes += sizeof(uint16_t);
    uint16_to_bytes(header.version, bytes);
    bytes += sizeof(uint16_t);
    uint32_to_bytes(header.tick_count, bytes);
}