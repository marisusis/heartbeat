#ifndef _HB_HB_H_
#define _HB_HB_H_

#include <stdlib.h>
#include <stdio.h>

#define HB_FILE_CODE 0x73
#define HB_HEADER_LINE 0xa1

#ifdef __cplusplus
extern "C" {
#endif

void uint16_to_bytes(uint16_t number, uint8_t* bytes);
void uint32_to_bytes(uint32_t number, uint8_t* bytes);
void uint64_to_bytes(uint64_t number, uint8_t* bytes);
uint16_t bytes_to_uint16(uint8_t* bytes);
uint32_t bytes_to_uint32(uint8_t* bytes);
uint64_t bytes_to_uint64(uint8_t* bytes); 

typedef struct hb_file_header {
    uint16_t magic;
    uint16_t version;
    uint32_t tick_count;
} hb_file_header;

hb_file_header parse_file_header(uint8_t* data);
void file_header_to_bytes(hb_file_header header, uint8_t* bytes);


typedef struct hb_tick_header {
    uint16_t magic;
    uint32_t utc_timestamp;
    uint16_t checksum;
    uint32_t data_count;
} hb_tick_header;

hb_tick_header parse_tick_header(uint8_t* data);
void tick_header_to_bytes(hb_tick_header header, uint8_t* bytes);

typedef struct hb_tick {
    hb_tick_header header;
    uint16_t* data;
} hb_tick;

hb_tick* hb_tick_malloc();
void hb_tick_free(hb_tick* tick);
hb_tick hb_parse_tick(uint8_t* data, size_t len);

typedef struct hb_file {
    FILE* source_file;
    hb_file_header header;
    hb_tick* ticks;
} hb_file;

hb_file* hb_file_malloc();
void hb_file_free(hb_file* file);
void hb_file_close(hb_file* file);
hb_file* hb_file_open(char* filename);

typedef struct hb_record {
    
} hb_record;

#ifdef __cplusplus
}
#endif

#endif