#include "raylib.h"
#include "game.h"
#include "player.h"
#include <vector>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Connect 4");

    //Init game class
    int playerAmount{ 2 };
    Game game(static_cast<float>(screenWidth), static_cast<float>(screenHeight));


    // init players, add to game and set colors.
    for (int i = 1; i < playerAmount; i++){

    }
    std::vector<Player> playerInit(playerAmount);
    int pCount{1};
    for (auto player : playerInit){
        player
    }
    Player playerFirst(1);
    Player playerSecond(2);
    game.addPlayer(playerFirst);
    game.addPlayer(playerSecond);
    game.setPlayerColor(playerFirst, RED);
    game.setPlayerColor(playerSecond, YELLOW);

    game.setTurnPlayer(playerFirst);
    game.getTurnPlayer();

    Vector2 mousePos{};

    std::vector<Rectangle> clickableColumn(Rectangle);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Logic
        //--------------------------------------------------------------------------------------/
        float dT{ GetFrameTime() };
        mousePos = GetMousePosition();


        //collision check for clickable column area to drop coin

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
            game.updateRes(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
        }

        //--------------------------------------------------------------------------------------/
        ClearBackground(BLACK);
        BeginDrawing();

        game.draw(game.getTurnPlayer());

        EndDrawing();
    }
    CloseWindow();
}