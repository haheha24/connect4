#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "raylib.h"
#include "player.h"
#include "cell.h"

class Player; // forward declare
class Cell;

class Game
{
public:
    Game(float screenWidth, float screenHeight, std::vector<Player>& players, std::vector<Texture2D>& coins);
    void updateRes(float newScreenWidth, float newScreenHeight);
    void draw();
    void tick(Vector2 mousePos, std::vector<Player>& players);
    void setPlayerColor(Player& player, int n);
    Player getTurnPlayer() { return turnPlayer; }
    void setTurnPlayer(Player player) { turnPlayer = player; }
    void setPlayerIndex(int idx) { playerIndex = idx; }
    int getPlayerIndex() { return playerIndex; }

private:
    static constexpr int COLS{ 7 };
    static constexpr int ROWS{ 6 };
    float screenWidth{};
    float screenHeight{};
    float width{ screenWidth * 0.75f };
    float height{ screenHeight * 0.75f };
    Vector2 screenPos{ (screenWidth - width) / 2.f, (screenHeight - height) / 2.f };
    Rectangle recSrc{
        screenPos.x,
        screenPos.y,
        width,
        height };
    std::vector<std::vector<Cell>> grid2d;
    Player turnPlayer{};
    int playerIndex{ 0 };
    struct PlayerColor
    {
        bool available{ true };
        Color color;
        Texture2D coin;
    };
    static const int sizeOfPlayerColors{ 2 };
    PlayerColor colors[sizeOfPlayerColors];
    std::vector<Texture2D> coins{};
};

#endif