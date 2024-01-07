#include "hb.h"

hb_file* hb_file_open(char* filename) {
    FILE* file = fopen(filename, "rw");
    hb_file* hb_file = hb_file_malloc();

    

    hb_file->source_file = file;
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
    
}