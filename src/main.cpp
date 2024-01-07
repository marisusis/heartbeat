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

    

    hb_file_close(file);

    SetTargetFPS(120);

}