#ifndef _HB_HB_H_
#define _HB_HB_H_

#include <stdlib.h>
#include <stdio.h>

#define HB_FILE_CODE 0x69
#define HB_HEADER_LINE 0xa1

typedef struct hb_tick {
    uint32_t timestamp;
    uint32_t data_count;
    uint16_t* data;
} hb_tick;

hb_tick* hb_tick_malloc();
void hb_tick_free(hb_tick* tick);
hb_tick* hb_parse_tick(uint8_t* data, size_t len);

typedef struct hb_file {
    FILE* source_file;
} hb_file;

hb_file* hb_file_malloc();
void hb_file_free(hb_file* file);
void hb_file_close(hb_file* file);
hb_file* hb_file_open(char* filename);

typedef struct hb_record {
    
} hb_record;

#endif