#include <raylib.h>

#define string const char*

int main() {

    InitWindow(100, 600, "Hello World");
    Color bg = WHITE;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bg);
        if (IsKeyDown(KEY_Q)) {
            bg.r += 1;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}