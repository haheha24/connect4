#include "game.h"

Game::Game(float screenWidth, float screenHeight) : screenWidth(screenWidth),
                                                    screenHeight(screenHeight)
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (Cell){
                .x = i,
                .y = j,
                .rec =
                    Rectangle{
                        static_cast<float>(recSrc.x + (i * recSrc.width)),
                        static_cast<float>(recSrc.y + (j * recSrc.height)),
                        static_cast<float>(recSrc.width / COLS),
                        static_cast<float>(recSrc.height / ROWS)},
            };
        }
    }
};

void Game::update(float newScreenWidth, float newScreenHeight)
{
    // UPDATE VALUES
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    width = screenWidth * 0.75f;
    height = screenHeight * 0.75f;
    screenPos = Vector2{(screenWidth - width) / 2.f, (screenHeight - height) / 2.f};
    recSrc = Rectangle{
        screenPos.x,
        screenPos.y,
        width,
        height};

    // UPDATE 2D GRID ARRAY
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (Cell){
                .rec =
                    Rectangle{
                        static_cast<float>(recSrc.x + (i * recSrc.width)),
                        static_cast<float>(recSrc.y + (j * recSrc.height)),
                        static_cast<float>(recSrc.width / COLS),
                        static_cast<float>(recSrc.height / ROWS)},
            };
        }
    }
};

void Game::draw()
{
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            DrawRectangleLines(recSrc.x + (i * grid[i][j].rec.width),
                               recSrc.y + (j * grid[i][j].rec.height),
                               grid[i][j].rec.width,
                               grid[i][j].rec.height,
                               BLACK);
            DrawCircle(recSrc.x + (i * grid[i][j].rec.width) + (grid[i][j].rec.width / 2),
                       recSrc.y + (j * grid[i][j].rec.height) + (grid[i][j].rec.height / 2),
                       ((grid[i][j].rec.width + grid[i][j].rec.height) / 2) * 0.33f,
                       WHITE); // will have to draw these white circles after the falling coin for visual effect of going down a hole.
        }
    }
};