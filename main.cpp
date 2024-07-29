#include <iostream>
#include <vector>

#include "Game.h"
#include "MainMenu.h"
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
    textureManager.init();

    // Init players
    std::vector<Player> players{Player(1), Player(2)};

    // Init game class
    Game game(textureManager, static_cast<float>(screenWidth), static_cast<float>(screenHeight), players);
    int randPlayerIndex = GetRandomValue(0, 1);
    game.setTurnPlayer(players[randPlayerIndex]);
    game.setPlayerIndex(randPlayerIndex);

    // Init Main Menu
    MainMenu menu{textureManager};
    Vector2 mousePos{};

    SetTargetFPS(60);
    while (!menu.exitWindow) {
        //--------------------------------------------------------------------------------------/
        // Logic
        //--------------------------------------------------------------------------------------/
        mousePos = GetMousePosition();
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) menu.exitWindowRequest = true;
        if (menu.exitWindowRequest) {
            menu.off();
            game.pause();
            // Exit_2
            if (CheckCollisionPointRec(GetMousePosition(), menu.getMenuList()[4].getRec()) &&
                IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                menu.exitWindow = true;
            }
            // Back_2
            if (CheckCollisionPointRec(GetMousePosition(), menu.getMenuList()[5].getRec()) &&
                IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                menu.exitWindowRequest = false;
            }
        }
        if (game.newGameRequest) {
            menu.off();
            game.pause();
            // New_Game_2
            if (CheckCollisionPointRec(GetMousePosition(), menu.getMenuList()[6].getRec()) &&
                IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                game.reset(players);
                int randPlayerIndex = GetRandomValue(0, 1);
                game.setTurnPlayer(players[randPlayerIndex]);
                game.setPlayerIndex(randPlayerIndex);
                game.newGameRequest = false;
            }
            // Back_2
            if (CheckCollisionPointRec(GetMousePosition(), menu.getMenuList()[5].getRec()) &&
                IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                game.newGameRequest = false;
            }
        }
        //--------------------------------------------------------------------------------------/
        // Window Resizing
        //--------------------------------------------------------------------------------------/
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        if (IsWindowResized() && !IsWindowFullscreen()) {
            game.updateRes(screenWidth, screenHeight);
            menu.updateRes();
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
            ToggleFullscreen();
            game.updateRes(screenWidth, screenHeight);
            menu.updateRes();
        }
        //--------------------------------------------------------------------------------------/
        // Draw
        //--------------------------------------------------------------------------------------/
        BeginDrawing();
        ClearBackground(BLACK);
        switch (currentScreen) {
            case LOGO: {
                DrawText("CONNECT 4", 20, 20, 40, RED);
                framesCounter++;
                if (framesCounter > 120) {
                    currentScreen = TITLE;
                    framesCounter = 0;
                }
                break;
            }
            case TITLE: {
                DrawText("CONNECT 4", 20, 20, 40, RED);
                DrawText("PRESS ENTER OR TAP TO START", 120, 220, 20, RED);
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
                    currentScreen = GAMEPLAY;
                }
                break;
            }
            case GAMEPLAY: {
                //--------------------------------------------------------------------------------------/
                // Game On
                //--------------------------------------------------------------------------------------/
                DrawText(std::string("Player 1 coins left: ").append(std::to_string(players[0].getNumOfCoinsLeft())).c_str(), 20, screenHeight - 50, 24, players[0].getPlayerColor());
                DrawText(std::string("Player 2 coins left: ").append(std::to_string(players[1].getNumOfCoinsLeft())).c_str(), 20, screenHeight - 25, 24, players[1].getPlayerColor());
                game.draw();
                if (!game.getGameState().paused && !game.getGameState().gameover) {
                    game.tick(mousePos, players);
                }
                //--------------------------------------------------------------------------------------/
                // Game Over
                //--------------------------------------------------------------------------------------/
                if (!game.getGameState().gameover) {
                    DrawText(std::string("Turn: ").append(game.getTurnPlayer().getName()).c_str(), 20, 20, 40, game.getTurnPlayer().getPlayerColor());
                } else {
                    DrawRectangle(0.f, 0.f, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                    if (game.getGameState().winner.getPlayerNumber() == 1 || game.getGameState().winner.getPlayerNumber() == 2) {
                        DrawText(std::string("Winner: ").append(game.getGameState().winner.getName()).c_str(), 20, 20, 40, game.getGameState().winner.getPlayerColor());
                    } else {
                        DrawText(std::string("There are no more turns left.\n\nYou're both losers!").c_str(),
                                 (screenWidth * 0.625) / 2,
                                 (screenHeight * 0.625) / 2,
                                 24, BLUE);
                    }
                }
                //--------------------------------------------------------------------------------------/
                // Game Menu
                //--------------------------------------------------------------------------------------/
                menu.getMenu().draw({}, {}, WHITE);
                // Toggle the menu button
                if (CheckCollisionPointRec(GetMousePosition(), menu.getMenu().getRec()) &&
                    IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    menu.toggle();
                }
                // Pause the game and draw the menu item list
                if (menu.isActive()) {
                    game.pause();
                    DrawRectangle(0.f, 0.f, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                    for (auto& button : menu.getMenuList()) {
                        if (button.getOption() == 1 ||
                            button.getOption() == 2 ||
                            button.getOption() == 3) {
                            button.draw({}, {}, WHITE);
                            if (CheckCollisionPointRec(GetMousePosition(), button.getRec()) &&
                                IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                                // New game button
                                if (button.getOption() == 1) {
                                    game.newGameRequest = true;
                                }
                                // Exit Button
                                if (button.getOption() == 2) {
                                    menu.exitWindowRequest = true;
                                }
                                // Back Button
                                if (button.getOption() == 3) {
                                    menu.toggle();
                                    game.newGameRequest = false;
                                    menu.exitWindowRequest = false;
                                }
                            }
                        }
                    }
                }
                if (!menu.isActive() && !menu.exitWindowRequest && !game.newGameRequest) {
                    game.unpause();
                }
                if (menu.exitWindowRequest) {
                    game.pause();
                    DrawRectangle(0.f, 0.f, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                    menu.getMenuList()[4].draw({}, {}, WHITE);
                    menu.getMenuList()[5].draw({}, {}, WHITE);
                }
                if (game.newGameRequest) {
                    game.pause();
                    DrawRectangle(0.f, 0.f, screenWidth, screenHeight, ColorAlpha(BLACK, 0.4f));
                    menu.getMenuList()[6].draw({}, {}, WHITE);  // new game button
                    menu.getMenuList()[5].draw({}, {}, WHITE);  // back button
                }
                // unpause game after starting -- This is at the end of the draw execution to prevent the ticking function
                // from activating if the first player clicks in the middle of the playable screen.
                if (players[0].getNumOfCoinsLeft() == 21 &&
                    players[1].getNumOfCoinsLeft() == 21 &&
                    !menu.isActive())
                    game.unpause();
                break;
            }
            default:
                break;
        }
        EndDrawing();
    }
    //--------------------------------------------------------------------------------------/

    textureManager.unloadTextures();
    CloseWindow();
}