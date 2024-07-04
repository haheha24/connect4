#include "game.h"

Game::Game(TextureLoader& textureManager,
    float screenWidth,
    float screenHeight,
    std::vector<Player>& players) :
    textureManager(textureManager),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    turnPlayer(players[0])
{
    // set game colors
    colors[0] = { true, RED, textureManager.getTexture("redCoin") };
    colors[1] = { true, YELLOW, textureManager.getTexture("yellowCoin") };

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
                        textureManager.getTexture("blankCoin")
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
            std::string posY{ "Row: " };
            posY.append(std::to_string(row->getRowPos()), 0, 10);
            std::string posX{ "Col: " };
            posX.append(std::to_string((row->getColumnPos())), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(),
                recSrc.x + (row->getColumnPos() * row->getCellRec().width),
                recSrc.y + (row->getRowPos() * row->getCellRec().height),
                11,
                BLACK);
        }
    }
};

void Game::tick(Vector2 mousePos, std::vector<Player>& players)
{
    // win conditions
    if (!gameover)
    {
        checkConnect4(players[playerIndex]);
    }
    else if (players[0].getCoins() == 0 && players[1].getCoins() == 0)
    {
        gameover = true;
        winner = 0;
    }
    // player actions
    for (auto& col : grid2d)
    {
        Rectangle columnRec{
                col.begin()->getCellRec().x,
                col.begin()->getCellRec().y,
                col.begin()->getCellRec().width,
                col.begin()->getGameRec().height
        };
        for (auto row = col.rbegin(); row != col.rend(); ++row)
        {
            if (CheckCollisionPointRec(mousePos, columnRec))
            {
                DrawText("highlighted", row->getGameRec().x + row->getColumnPos() * row->getCellRec().width, row->getGameRec().y + row->getRowPos() * row->getCellRec().height, 11, RED); // replace with highlighted texture around cell
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, columnRec))
            {
                if (row->isBlank() && row->getOwner().getPlayerNumber() == 0)
                {
                    row->updateCell(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = -playerIndex + 1;
                    Game::setTurnPlayer(players[playerIndex]);
                    return;
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

void Game::checkConnect4(Player& player)
{
    for (int col = 0; col < grid2d.size() - 1; ++col)
    {
        for (int row = grid2d[col].size() - 1; row >= 0; --row)
        {
            if (!grid2d[col][row].isBlank())
            {
                //vertical
                if (row > 0 && grid2d[col][row].getOwner().getPlayerNumber() == grid2d[col][row - 1].getOwner().getPlayerNumber())
                {
                    ++player.coinCounter.vertical;
                    if (player.coinCounter.vertical == 4) { gameover = true; winner = grid2d[col][row].getOwner().getPlayerNumber(); }
                }
                else
                {
                    player.coinCounter.vertical = 1;
                }
                //check horizontal
                //check next column but guard against out of bounds
                if (col < grid2d.size() - 1 &&
                    grid2d[col][row].getOwner().getPlayerNumber() == grid2d[col + 1][row].getOwner().getPlayerNumber())
                {
                    ++player.coinCounter.horizontal;
                    if (player.coinCounter.horizontal == 4) { gameover = true; winner = grid2d[col][row].getOwner().getPlayerNumber(); }
                }
                else
                {
                    player.coinCounter.horizontal = 1;
                }
                /*//check diagonol upwards
                if (col + 1 > grid2d.size() - 1 &&
                    row - 1 > 0 &&
                    grid2d[col + 1][row - 1].getOwner().getPlayerNumber() == player.getPlayerNumber())
                {
                    ++diagonolUpwardsCounter;
                    if (diagonolUpwardsCounter == 4) { gameover = true; winner = player.getPlayerNumber(); }
                }
                else
                {
                    diagonolUpwardsCounter = 1;
                }
                //check diagonol downwards
                if (col + 1 > grid2d.size() - 1 &&
                    row + 1 < grid2d[col].size() - 1 &&
                    grid2d[col + 1][row + 1].getOwner().getPlayerNumber() == player.getPlayerNumber())
                {
                    ++diagonolDownwardsCounter;
                    if (diagonolDownwardsCounter == 4) { gameover = true; winner = player.getPlayerNumber(); }
                }
                else
                {
                    diagonolDownwardsCounter = 1;
                } */
            }
            else
            {
                break;
            }
        }

    };
}

Game::GameState Game::getGameState() {
    GameState state{
        gameover,
        winner
    };
    return state;
};