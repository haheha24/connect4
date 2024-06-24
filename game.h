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
    Game(float screenWidth, float screenHeight);
    void updateRes(float newScreenWidth, float newScreenHeight);
    void draw();
    void tick(Vector2 mousePos);
    std::vector<Player> getPlayers() { return players; }
    void setPlayerColor(Player player, int n);
    Player getTurnPlayer() { return turnPlayer; }
    void setTurnPlayer(Player player) { turnPlayer = player; }
    void setPlayerIndex(int idx) { playerIndex = idx; }
    int getPlayerIndex() { return playerIndex; }

private:
    static constexpr int COLS{7};
    static constexpr int ROWS{6};
    float screenWidth{};
    float screenHeight{};
    float width{screenWidth * 0.75f};
    float height{screenHeight * 0.75f};
    Vector2 screenPos{(screenWidth - width) / 2.f, (screenHeight - height) / 2.f};
    Rectangle recSrc{
        screenPos.x,
        screenPos.y,
        width,
        height};
    std::vector<std::vector<Cell>> grid2d;
    std::vector<Player> players{Player(1), Player(2)};
    Player turnPlayer{};
    int playerIndex{0};
    struct PlayerColor
    {
        bool available{true};
        Color color;
    };
    static const int sizeOfPlayerColors{4};
    PlayerColor colors[sizeOfPlayerColors];
};

#endif