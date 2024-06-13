#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"

class Game
{
public:
    Game(float screenWidth, float screenHeight);
    void update(float newScreenWidth, float newScreenHeight);
    void draw();

protected:
    struct Cell
    {
        int x{};
        int y{};
        bool blank{ true };
        Rectangle rec{};
        Rectangle dest{};
        Texture2D tex{};
    };

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
};

#endif