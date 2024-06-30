#include "game.h"

Game::Game(float screenWidth,
    float screenHeight,
    std::vector<Player>& players,
    std::vector<Texture2D>& coins) : screenWidth(screenWidth),
    screenHeight(screenHeight),
    turnPlayer(players[0]),
    coins(coins)

{
    // set game colors
    colors[0] = { true, RED, coins[1] };
    colors[1] = { true, YELLOW, coins[2] };
    /* colors[2] = { true, GREEN, coins[3] };
    colors[3] = { true, ORANGE, coins[4] }; */

    Game::setPlayerColor(players[0], 1);
    Game::setPlayerColor(players[1], 2);

    for (int i = 0; i < COLS; ++i)
    {
        // setup the grid
        grid2d.push_back(std::vector<Cell>({}));
        for (int j = 0; j < ROWS; ++j)
        {
            grid2d[i].push_back((Cell) {
                i,
                    j,
                    Rectangle{
                        static_cast<float>(recSrc.x + (i * (recSrc.width / COLS))),
                        static_cast<float>(recSrc.y + (j * (recSrc.height / ROWS))),
                        static_cast<float>(recSrc.width / COLS),
                        static_cast<float>(recSrc.height / ROWS) },
                        recSrc,
                        coins[0]
            });
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
    screenPos = Vector2{ (screenWidth - width) / 2.f, (screenHeight - height) / 2.f };
    recSrc = Rectangle{
        screenPos.x,
        screenPos.y,
        width,
        height };

    // UPDATE 2D GRID ARRAY
    for (auto& col : grid2d)
    {
        for (auto row = col.begin(); row != col.end(); ++row)
        {
            row->updateGameRec(recSrc);
            row->updateCellRec(Rectangle{
                static_cast<float>(row->getGameRec().x + ((row->getColumnPos()) * (row->getGameRec().width / COLS))),
                static_cast<float>(row->getGameRec().y + ((row->getRowPos()) * (row->getGameRec().height / ROWS))),
                static_cast<float>(row->getGameRec().width / COLS),
                static_cast<float>(row->getGameRec().height / ROWS) });
        }
    }
};

void Game::draw()
{
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    for (auto& col : grid2d)
    {
        for (auto row = col.begin(); row != col.end(); ++row)
        {
            row->drawCoin();
            // delete when finished
            /* std::string blank{ "Blank: " };
            blank.append(std::to_string(row->isBlank()), 0, 10);
            std::string owner{ row->getOwner().getName() };
            owner.append("\n" + blank);
            std::string posY{ "Row: " };
            posY.append(std::to_string(row->getRowPos()), 0, 10).append("\n" + owner);
            std::string posX{ "Col: " };
            posX.append(std::to_string((row->getColumnPos())), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(),
                recSrc.x + (row->getColumnPos() * row->getCellRec().width),
                recSrc.y + (row->getRowPos() * row->getCellRec().height),
                11,
                BLACK); */
        }
    }
};

void Game::tick(Vector2 mousePos, std::vector<Player>& players)
{
    for (auto& col : grid2d)
    {
        for (auto row = col.begin(); row != col.end(); ++row)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, row->getCellRec()))
            {
                if (row->isBlank() && row->getOwner().getPlayerNumber() == 0)
                {
                    row->updateCell(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = -playerIndex + 1;
                    Game::setTurnPlayer(players[playerIndex]);
                    std::cout << "Position: " << "(" << row->getRowPos() << "," << row->getColumnPos() << ")" << std::endl;
                    std::cout << "Owned by? " << row->getOwner().getName() << std::endl;
                    std::cout << "blank? " << row->isBlank() << std::endl;
                    std::cout << "Color: " << std::to_string(row->getOwner().getPlayerColor().r).c_str() << ", " << std::to_string(row->getOwner().getPlayerColor().b).c_str() << ", " << std::to_string(row->getOwner().getPlayerColor().g).c_str() << ", " << std::to_string(row->getOwner().getPlayerColor().a).c_str() << std::endl;
                    std::cout << "Number of turns left: " << row->getOwner().getNumOfCoinsLeft() << "\n"
                        << std::endl;
                }
            }
        }
    }
};

void Game::setPlayerColor(Player& player, int n)
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
            player.setPlayerColor(colors[i].color);
            player.setPlayerTexture(colors[i].coin);
            colors[i].available = false;
        }
        else
        {
            colors[i].available = true;
        }
    }
}