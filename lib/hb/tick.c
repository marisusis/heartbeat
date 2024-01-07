#include "hb.h"
#include <memory.h>

hb_tick* hb_tick_malloc() {
    hb_tick* tick = malloc(sizeof(hb_tick));
    tick->data = NULL;
    tick->header.data_count = 0;
    return tick;
}

void hb_tick_free(hb_tick* tick) {
    if (tick->data != NULL) {
        free(tick->data);
    }

    free(tick);
}

hb_tick hb_parse_tick(uint8_t* data, size_t len) {
    hb_tick tick;

    tick.header = parse_tick_header(data);
    printf("Tick header magic: %x\n", tick.header.magic);
    printf("Tick header timestamp: %d\n", tick.header.utc_timestamp);
    printf("Tick header checksum: %x\n", tick.header.checksum);
    printf("Tick header data count: %d\n", tick.header.data_count);

    tick.data = malloc(tick.header.data_count * sizeof(uint16_t));

    data += sizeof(hb_tick_header);

    for (size_t i = 0; i < tick.header.data_count; i++) {
        // tick.data[i] = bytes_to_uint16(data);
        // printf("%d\n", i);
    }

    return tick;
}


hb_tick_header parse_tick_header(uint8_t* data) {
    hb_tick_header header;
    header.magic = bytes_to_uint16(data);
    header.utc_timestamp = bytes_to_uint32(data += sizeof(uint16_t));
    header.checksum = bytes_to_uint16(data += sizeof(uint32_t));
    header.data_count = bytes_to_uint32(data += sizeof(uint16_t));
    return header;
}

void tick_header_to_bytes(hb_tick_header header, uint8_t* bytes) {
    uint16_to_bytes(header.magic, bytes);
    uint32_to_bytes(header.utc_timestamp, bytes += sizeof(uint16_t));
    uint16_to_bytes(header.checksum, bytes += sizeof(uint32_t));
    uint32_to_bytes(header.data_count, bytes += sizeof(uint16_t));
}