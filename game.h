#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include "player.h"
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Game
{
protected:
    struct Cell
    {
        int row{};
        int column{};
        bool blank{ true };
        Rectangle rec{};
    };
public:
    Game(float screenWidth, float screenHeight);
    void addPlayer(Player player) { players.insert({ numOfPlayers, player }); }
    void updateRes(float newScreenWidth, float newScreenHeight);
    void draw(Player player);
    bool isCellEmpty(Cell cell) { return cell.blank; };
    void tick(Player player);
    std::vector<std::vector<Cell>> getGrid() { return grid; }
    void setPlayerColor(Player player, Color color);
    Player getTurnPlayer() { return turnPlayer; }
    int setTurnPlayer(Player player) { turnPlayer = player; }
private:
    int numOfPlayers{ 2 };
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
    std::vector<Cell> cell{};
    std::vector<std::vector<Cell>> grid;
    std::vector<Rectangle> columns;
    struct PlayerColor {
        bool available{ true };
        Color color;
    };
    static const int sizeOfPlayerColors{ 3 };
    PlayerColor colors[sizeOfPlayerColors];
    map<int, Player> players{};
    Player turnPlayer;
};

#endif