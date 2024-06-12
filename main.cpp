#include "raylib.h"
#include "game.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Connect 4");

    Game game(static_cast<float>(screenWidth), static_cast<float>(screenHeight));
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Logic
        //--------------------------------------------------------------------------------------/
        if (IsWindowResized() && !IsWindowFullscreen())
        {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
        {
            ToggleFullscreen();
        }

        if (IsWindowResized() || IsWindowFullscreen())
        {
            game.update(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
        }

        //--------------------------------------------------------------------------------------/
        ClearBackground(BLACK);
        BeginDrawing();

        game.draw();

        EndDrawing();
    }
    CloseWindow();
}