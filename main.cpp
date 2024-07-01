#include "raylib.h"
#include "textureLoader.h"
#include "game.h"
#include "player.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Connect 4");

    // Load Textures
    TextureLoader textureManager;

    // Init players
    std::vector<Player> players{ Player(1), Player(2) };

    // Init game class
    Game game(textureManager, static_cast<float>(screenWidth), static_cast<float>(screenHeight), players);

    Vector2 mousePos{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Logic
        //--------------------------------------------------------------------------------------/
        mousePos = GetMousePosition();

        // collision check for clickable column area to drop coin

        if (IsWindowResized() && !IsWindowFullscreen())
        {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            game.updateRes(screenWidth, screenHeight);
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
        {
            ToggleFullscreen();
        }

        //--------------------------------------------------------------------------------------/
        // Draw
        //--------------------------------------------------------------------------------------/
        ClearBackground(BLACK);
        BeginDrawing();

        // player turn text
        DrawText(std::string("Turn: ").append(game.getTurnPlayer().getName()).c_str(), 20, 20, 40, RED);
        // DRAW EVERYTHING
        game.draw();
        // game actions
        game.tick(mousePos, players);

        EndDrawing();
        //--------------------------------------------------------------------------------------/
    }
    textureManager.unloadTextures();
    CloseWindow();
}