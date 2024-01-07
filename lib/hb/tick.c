#include "hb.h"
#include <memory.h>

hb_tick* hb_tick_malloc() {
    hb_tick* tick = malloc(sizeof(hb_tick));
    tick->data = NULL;
    tick->data_count = 0;
    return tick;
}

void hb_tick_free(hb_tick* tick) {
    if (tick->data != NULL) {
        free(tick->data);
    }

    free(tick);
}

hb_tick* hb_parse_tick(uint8_t* data, size_t len) {
    hb_tick* tick = hb_tick_malloc();

    for (size_t i = 0; i < len; i += 2) {
        tick->data[tick->data_count++] = (data[i] << 8) | data[i + 1];
    }

    return tick;
}

// hb_tick* hb_parse_tick(char* line, size_t len) {
//     size_t index = 0;
//     size_t data_index = 0;
//     uint16_t* data = malloc(len / 5 * sizeof(uint16_t));

//     if (data == NULL) {
//         exit(1);
//     }

//     hb_tick* tick = hb_tick_malloc();

//     // Parse time
//     while (line[index] != ',') {
//         index++;
//     }

//     index++;

//     // max number is 1024
//     while (index < len) {
//         char parsed_number[4];
//         memset(parsed_number, 0, 4);
//         uint8_t parse_index = 0;

//         while (line[index] != ',' && index < len) {
//             parsed_number[parse_index++] = line[index];
//             index++;
//         }

//         data[data_index++] = (uint16_t) atoi(parsed_number);
        
//         index++;
//     }

//     tick->data = data;
//     tick->data_count = data_index;

//     return tick;
// }

