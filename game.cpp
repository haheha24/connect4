#include "game.h"

Game::Game(float screenWidth,
           float screenHeight) : screenWidth(screenWidth),
                                 screenHeight(screenHeight),
                                 turnPlayer(players[0])

{
    // set game colors
    colors[0] = {true, RED};
    colors[1] = {true, YELLOW};
    colors[2] = {true, GREEN};
    colors[3] = {true, ORANGE};

    Game::setPlayerColor(players[0], 1);
    Game::setPlayerColor(players[1], 2);

    for (int i = 0; i < ROWS; ++i)
    {
        // setup the grid
        grid2d.push_back(std::vector<Cell>({}));
        for (int j = 0; j < COLS; ++j)
        {
            grid2d[i].push_back((Cell){i,
                                       j,
                                       Rectangle{
                                           static_cast<float>(recSrc.x + (i * (recSrc.width / ROWS))),
                                           static_cast<float>(recSrc.y + (j * (recSrc.height / COLS))),
                                           static_cast<float>(recSrc.width / ROWS),
                                           static_cast<float>(recSrc.height / COLS)},
                                       recSrc});
        }
    }
};

void Game::updateRes(float newScreenWidth, float newScreenHeight)
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
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            grid2d[i][j].updateGameRec(recSrc);
            grid2d[i][j].updateCellRec(Rectangle{
                static_cast<float>(grid2d[i][j].getGameRec().x + ((grid2d[i][j].getRowPos()) * (grid2d[i][j].getGameRec().width / ROWS))),
                static_cast<float>(grid2d[i][j].getGameRec().y + ((grid2d[i][j].getColumnPos()) * (grid2d[i][j].getGameRec().height / COLS))),
                static_cast<float>(grid2d[i][j].getGameRec().width / ROWS),
                static_cast<float>(grid2d[i][j].getGameRec().height / COLS)});
        }
    }
};

void Game::draw()
{
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    /* for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            grid2d[i][j].drawCoin();
            // delete when finished
            std::string posY{"Col: "};
            posY.append(std::to_string(grid2d[i][j].getColumnPos()), 0, 10);
            std::string posX{"Row: "};
            posX.append(std::to_string((grid2d[i][j].getRowPos())), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(),
                     recSrc.x + (i * grid2d[i][j].getCellRec().width),
                     recSrc.y + (j * grid2d[i][j].getCellRec().height),
                     14,
                     RED);
        }
    } */
    for (auto row : grid2d)
    {
        for (auto col = row.begin(); col != row.end(); ++col)
        {
            col->drawCoin();
            // delete when finished
            std::string posY{"Col: "};
            posY.append(std::to_string(col->getColumnPos()), 0, 10);
            std::string posX{"Row: "};
            posX.append(std::to_string((col->getRowPos())), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(),
                     recSrc.x + (col->getRowPos() * col->getCellRec().width),
                     recSrc.y + (col->getColumnPos() * col->getCellRec().height),
                     14,
                     RED);
        }
    }
};

void Game::tick(Vector2 mousePos)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            /* int index = (i * COLS) + j;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, grid[index].getCellRec()))
            {
                if (grid[index].isBlank())
                {
                    grid[index].updateCell(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = -playerIndex + 1;
                    Game::setTurnPlayer(players[playerIndex]);
                    std::cout << "Position: " << "(" << grid[index].getRowPos() - 1 << "," << grid[index].getColumnPos() - 1 << ")" << std::endl;
                    std::cout << "Owned by? " << grid[index].getOwner().getName() << std::endl;
                    std::cout << "blank? " << grid[index].isBlank() << std::endl;
                    std::cout << "Color: " << std::to_string(grid[index].getOwner().getPlayerColor().r).c_str() << ", " << std::to_string(grid[index].getOwner().getPlayerColor().b).c_str() << ", " << std::to_string(grid[index].getOwner().getPlayerColor().g).c_str() << ", " << std::to_string(grid[index].getOwner().getPlayerColor().a).c_str() << std::endl;
                    std::cout << "Number of turns left: " << grid[index].getOwner().getNumOfCoinsLeft() << "\n"
                              << std::endl;
                }
            } */
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, grid2d[i][j].getCellRec()))
            {
                if (grid2d[i][j].isBlank())
                {
                    grid2d[i][j].updateCell(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = -playerIndex + 1;
                    Game::setTurnPlayer(players[playerIndex]);
                    std::cout << "Position: " << "(" << grid2d[i][j].getRowPos() << "," << grid2d[i][j].getColumnPos() << ")" << std::endl;
                    std::cout << "Owned by? " << grid2d[i][j].getOwner().getName() << std::endl;
                    std::cout << "blank? " << grid2d[i][j].isBlank() << std::endl;
                    std::cout << "Color: " << std::to_string(grid2d[i][j].getOwner().getPlayerColor().r).c_str() << ", " << std::to_string(grid2d[i][j].getOwner().getPlayerColor().b).c_str() << ", " << std::to_string(grid2d[i][j].getOwner().getPlayerColor().g).c_str() << ", " << std::to_string(grid2d[i][j].getOwner().getPlayerColor().a).c_str() << std::endl;
                    std::cout << "Number of turns left: " << grid2d[i][j].getOwner().getNumOfCoinsLeft() << "\n"
                              << std::endl;
                }
            }
        }
    }
    /* for (auto row : grid)
    {
        for (auto cell = row.rbegin(); cell != row.rend(); ++cell)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, cell->getCellRec()))
            {
                if (cell->isBlank())
                {
                    cell->updateCell(players[playerIndex]);
                    Game::setPrevPlayer(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = static_cast<int>((playerIndex + 1) % numOfPlayers);
                    Game::setTurnPlayer(players[playerIndex]);
                    std::cout << "Position: " << "(" << cell->getRowPos() - 1 << "," << cell->getColumnPos() - 1 << ")" << std::endl;
                    std::cout << "Owned by? " << cell->getOwner().getName() << std::endl;
                    std::cout << "blank? " << cell->isBlank() << std::endl;
                    std::cout << "Color: " << std::to_string(cell->getOwner().getPlayerColor().r).c_str() << ", " << std::to_string(cell->getOwner().getPlayerColor().b).c_str() << ", " << std::to_string(cell->getOwner().getPlayerColor().g).c_str() << ", " << std::to_string(cell->getOwner().getPlayerColor().a).c_str() << std::endl;
                }
            }
        }
    } */
};

void Game::setPlayerColor(Player player, int n)
{
    Color color;
    switch (n)
    {
    case 1:
        color = RED;
        break;
    case 2:
        color = YELLOW;
        break;
    case 3:
        color = GREEN;
        break;
    case 4:
        color = ORANGE;
        break;
    default:
        color = BLACK;
        break;
    }
    for (int i = 0; i < sizeOfPlayerColors; ++i)
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