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
                    .row = j + 1, // col
                    .column = i + 1, // row
                    .rec = Rectangle{
                        static_cast<float>(recSrc.x + (i * recSrc.width / COLS)),
                        static_cast<float>(recSrc.y + (j * recSrc.height)),
                        static_cast<float>(recSrc.width / COLS),
                        static_cast<float>(recSrc.height / ROWS)},
                });
        }
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

void Game::draw(Player player)
{
    Color color{ WHITE };
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            Cell cell = grid[i][j];
            color = !cell.blank ? player.getPlayerColor() : WHITE;
            DrawRectangleLines(recSrc.x + (i * cell.rec.width),
                recSrc.y + (j * cell.rec.height),
                cell.rec.width,
                cell.rec.height,
                BLACK);
            DrawCircle(recSrc.x + (i * cell.rec.width) + (cell.rec.width / 2),
                recSrc.y + (j * cell.rec.height) + (cell.rec.height / 2),
                ((cell.rec.width + cell.rec.height) / 2) * 0.33f,
                color); // will have to draw these white circles after the falling coin for visual effect of going down a hole.
            string posY{ "Col: " };
            posY.append(to_string(cell.column), 0, 10);
            string posX{ "Row: " };
            posX.append(to_string(cell.row), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(), recSrc.x + (i * cell.rec.width), recSrc.y + (j * cell.rec.height) + (cell.rec.height / 2), std::clamp(GetFontDefault().baseSize, 10, 24), RED);
        }

    }
};

void Game::tick(Player player) {
    // need to check each cell if mouse is clicking it
    for (int i = 0; i < COLS; i++)
    {
        for (int j = ROWS; j > 0; j--) // Work backwards, starting from the end of the column checking each cell for blank = true.
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(GetMousePosition(), grid[i][j].rec) &&
                grid[i][j].blank)
            {
                DrawCircle(
                    recSrc.x + (recSrc.width / 2) + (i * recSrc.width / COLS),
                    grid[i][j].rec.y + grid[i][j].rec.height, ((grid[i][j].rec.width + grid[i][j].rec.height) / 2) * 0.33f, player.getPlayerColor());
                player.tick();
                grid[i][j].blank = false;
                goto stop;
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