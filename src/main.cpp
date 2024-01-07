#include <cstdio>
#include <string>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "hb.h"

int main(int argc, char** argv) {
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(800, 450, "heartbeat");

    SetTargetFPS(120);

    hb_tick* tick = hb_tick_malloc();

    uint16_t a = 1024;
    uint16_t b = 123;
    // uint16_t b = bytes_to_uint16(uint16_to_bytes(a));
    std::printf("a: %d, b: %d\n", a, b);
}