#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(int argc, char** argv) {
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(800, 450, "heartbeat");

    SetTargetFPS(120);
}