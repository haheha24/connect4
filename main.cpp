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
        {
            mousePos = GetMousePosition();

            if (IsWindowResized() && !IsWindowFullscreen())
            {
                screenWidth = GetScreenWidth();
                screenHeight = GetScreenHeight();
                game.updateRes(screenWidth, screenHeight);
            }
            if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
            {
                ToggleFullscreen();
                game.updateRes(GetScreenWidth(), GetScreenHeight());
            }
            //--------------------------------------------------------------------------------------/
            // Draw
            //--------------------------------------------------------------------------------------/
            ClearBackground(BLACK);
            BeginDrawing();
            if (game.getGameState().gameover)
            {
                if (game.getGameState().winner == 1 || game.getGameState().winner == 2)
                {
                    DrawText(std::string("Player ").append(std::to_string(game.getGameState().winner)).append(" wins!").c_str(),
                        (screenWidth * 0.625) / 2,
                        (screenHeight * 0.625) / 2,
                        24,
                        players[game.getGameState().winner - 1].getPlayerColor());
                }
                else
                {
                    DrawText(std::string("There are no more turns left.\n\nEveryone's a loser!").c_str(),
                        (screenWidth * 0.625) / 2,
                        (screenHeight * 0.625) / 2,
                        24, BLUE);
                }

            }
            else
            {
                // player turn text
                DrawText(std::string("Turn: ").append(game.getTurnPlayer().getName()).c_str(), 20, 20, 40, game.getTurnPlayer().getPlayerColor());
                DrawText(std::string("Player 1 coins left: ").append(std::to_string(players[0].getCoins())).c_str(), 20, screenHeight - 50, 24, players[0].getPlayerColor());
                DrawText(std::string("Player 2 coins left: ").append(std::to_string(players[1].getCoins())).c_str(), 20, screenHeight - 25, 24, players[1].getPlayerColor());
                // DRAW EVERYTHING 
                game.draw();
                // game actions
                game.tick(mousePos, players);
            }
            EndDrawing();
        }
        //--------------------------------------------------------------------------------------/
    }
    textureManager.unloadTextures();
    CloseWindow();
}