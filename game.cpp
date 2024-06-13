#include "game.h"

Game::Game(float screenWidth, float screenHeight) :
    screenWidth(screenWidth),
    screenHeight(screenHeight)
{
    for (int i = 0; i < COLS; i++)
    {
        // setup the grid
        grid.push_back(std::vector<Cell>(cell));
        for (int j = 0; j < ROWS; j++)
        {
            grid[i].push_back({
                    .x = j, // row
                    .y = i, // col
                    .rec = Rectangle{
                        static_cast<float>(recSrc.x + (i * recSrc.width)),
                        static_cast<float>(recSrc.y + (j * recSrc.height)),
                        static_cast<float>(recSrc.width / COLS),
                        static_cast<float>(recSrc.height / ROWS)},
                });
        }

        //setup tracking for player turn using this as collision rect against mouse and other animations
        columns.push_back(Rectangle{
            .x = static_cast<float>(recSrc.x + (i * recSrc.width)),
            .y = static_cast<float>(recSrc.y),
            .width = static_cast<float>(recSrc.width / COLS),
            .height = static_cast<float>(recSrc.height)
            });
    }
    colors[0] = { true, RED };
    colors[1] = { true, YELLOW };
    colors[2] = { true, GREEN };
    colors[3] = { true, ORANGE };

};

void Game::updateRes(float newScreenWidth, float newScreenHeight)
{
    // UPDATE VALUES
    screenWidth = newScreenWidth;
    screenHeight = newScreenHeight;
    width = screenWidth * 0.75f;
    height = screenHeight * 0.75f;
    screenPos = Vector2{ (screenWidth - width) / 2.f, (screenHeight - height) / 2.f };
    recSrc = Rectangle{
        screenPos.x,
        screenPos.y,
        width,
        height };

    // UPDATE 2D GRID ARRAY
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j].rec = { Rectangle{
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
    for (auto rec : columns)
    {
        DrawRectangle(rec.x, rec.y, rec.width, rec.height, RED);
    }

};

void Game::tick(Player player) {
    // need to check each cell if mouse is clicking it
    for (int i = 0; i < COLS; i++)
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), columns[i]))
        {
            for (int j = ROWS; j > 0; j--)
            {
                if (grid[i][j].blank)
                {
                    //always want pos x to be 0, while getting the bottom of a cell that is blank, BUT needs to be the last blank cell position.
                    DrawCircle(
                        recSrc.x + (recSrc.width / 2) + (i * recSrc.width),
                        grid[i][j].rec.y + grid[i][j].rec.height, ((grid[i][j].rec.width + grid[i][j].rec.height) / 2) * 0.33f, player.getPlayerColor());
                    player.turn();
                    grid[i][j].blank = false;
                    goto stop;
                }
            }
        }
    }
stop:
    return;
};

void Game::setPlayerColor(Player player, Color color) {
    for (int i = 0; i < sizeOfPlayerColors; i++)
    {
        if (color.r == colors[i].color.r &&
            color.g == colors[i].color.g &&
            color.b == colors[i].color.b &&
            color.a == colors[i].color.a &&
            colors[i].available)
        {
            player.setPlayerColor(color);
            colors[i].available = false;
        }
        else
        {
            colors[i].available = true;
        }
    }

}