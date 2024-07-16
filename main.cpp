#include "Game.h"
#include "Player.h"
#include "TextureLoader.h"
#include "raylib.h"

typedef enum GameScreen { LOGO = 0,
                          TITLE,
                          GAMEPLAY } GameScreen;

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Connect 4");

    GameScreen currentScreen = LOGO;
    int framesCounter = 0;

    // Load Textures
    TextureLoader textureManager;

    // Init players
    std::vector<Player> players{Player(1), Player(2)};

    // Init game class
    Game game(textureManager, static_cast<float>(screenWidth), static_cast<float>(screenHeight), players);

    Vector2 mousePos{};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        //--------------------------------------------------------------------------------------/
        // Logic
        //--------------------------------------------------------------------------------------/
        mousePos = GetMousePosition();
        //--------------------------------------------------------------------------------------/
        // Window
        //--------------------------------------------------------------------------------------/
        if (IsWindowResized() && !IsWindowFullscreen()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            game.updateRes(screenWidth, screenHeight);
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
            ToggleFullscreen();
            game.updateRes(GetScreenWidth(), GetScreenHeight());
        }
        //--------------------------------------------------------------------------------------/
        // Game Screens
        //--------------------------------------------------------------------------------------/
        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 120) currentScreen = TITLE;
                break;
            }
            case TITLE: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = GAMEPLAY;
                break;
            }
            case GAMEPLAY: {
                game.unpause();
                break;
            }
            default:
                break;
        }
        //--------------------------------------------------------------------------------------/
        // Draw
        //--------------------------------------------------------------------------------------/
        BeginDrawing();
        ClearBackground(BLACK);
        switch (currentScreen) {
            case LOGO: {
                DrawText("CONNECT 4", 20, 20, 40, RED);
                break;
            }
            case TITLE: {
                DrawText("CONNECT 4", 20, 20, 40, RED);
                DrawText("PRESS ENTER OR TAP TO START", 120, 220, 20, RED);
                break;
            }
            case GAMEPLAY: {
                // player turn text
                DrawText(std::string("Turn: ").append(game.getTurnPlayer().getName()).c_str(), 20, 20, 40, game.getTurnPlayer().getPlayerColor());
                DrawText(std::string("Player 1 coins left: ").append(std::to_string(players[0].getNumOfCoinsLeft())).c_str(), 20, screenHeight - 50, 24, players[0].getPlayerColor());
                DrawText(std::string("Player 2 coins left: ").append(std::to_string(players[1].getNumOfCoinsLeft())).c_str(), 20, screenHeight - 25, 24, players[1].getPlayerColor());
                // DRAW EVERYTHING
                game.draw();
                // game actions
                if (game.getGameState().paused == false) game.tick(mousePos, players);
                if (game.getGameState().gameover) {
                    DrawRectangle(0.f, 0.f, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                    if (game.getGameState().winner == 1 || game.getGameState().winner == 2) {
                        DrawText(std::string("Player ").append(std::to_string(game.getGameState().winner)).append(" wins!").c_str(),
                                 (screenWidth * 0.625) / 2,
                                 (screenHeight * 0.625) / 2,
                                 24,
                                 players[game.getGameState().winner - 1].getPlayerColor());
                    } else {
                        DrawText(std::string("There are no more turns left.\n\nEveryone's a loser!").c_str(),
                                 (screenWidth * 0.625) / 2,
                                 (screenHeight * 0.625) / 2,
                                 24, BLUE);
                    }
                }
            }
            default:
                break;
        }
        EndDrawing();
        //--------------------------------------------------------------------------------------/
    }
    textureManager.unloadTextures();
    CloseWindow();
}