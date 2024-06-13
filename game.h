#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include "player.h"

class Game
{
protected:
    struct Cell
    {
        int x{};
        int y{};
        bool blank{ true };
        bool mouseCollision{ false };
        Rectangle rec{};
    };
public:
    Game(float screenWidth, float screenHeight);
    void updateRes(float newScreenWidth, float newScreenHeight);
    void draw();
    bool isCellEmpty(Cell cell) { return cell.blank; };
    void tick(Player player);
    std::vector<std::vector<Cell>> getGrid() { return grid; }
    void setPlayerColor(Player player, Color color);
private:
    static const int COLS{ 7 };
    static const int ROWS{ 6 };
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
};

#endif