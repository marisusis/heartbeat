#include <cstdio>
#include <string>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hb.h"

int main(int argc, char** argv) {
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(800, 450, "heartbeat");

    hb_file* file = hb_file_open("./test1.hb");

    for (int i = 0; i < file->header.tick_count; i++) {
        hb_tick tick = file->ticks[i];
        printf("%d: %d\n", i, tick.header.magic);
    }

    SetTargetFPS(120);

}