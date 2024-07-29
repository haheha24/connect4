#include "Game.h"

Game::Game(TextureLoader& textureManager,
           float screenWidth,
           float screenHeight,
           std::vector<Player>& players) : textureManager(textureManager),
                                           screenWidth(screenWidth),
                                           screenHeight(screenHeight),
                                           turnPlayer(players[playerIndex]) {
    // set game colors
    int randPlayerIndex = GetRandomValue(0, 1);
    colors[randPlayerIndex] = {RED, textureManager.getTexture("redCoin")};
    colors[-randPlayerIndex + 1] = {YELLOW, textureManager.getTexture("yellowCoin")};
    setPlayerColor(players[randPlayerIndex], randPlayerIndex);
    setPlayerColor(players[-randPlayerIndex + 1], -randPlayerIndex + 1);

    // setup the grid
    for (int i = 0; i < COLS; ++i) {
        grid2d.push_back(std::vector<Cell>({}));
        for (int j = 0; j < ROWS; ++j) {
            grid2d[i].push_back((Cell){
                i,
                j,
                Rectangle{
                    static_cast<float>(recSrc.x + (i * (recSrc.width / COLS))),
                    static_cast<float>(recSrc.y + (j * (recSrc.height / ROWS))),
                    static_cast<float>(recSrc.width / COLS),
                    static_cast<float>(recSrc.height / ROWS)},
                recSrc,
                textureManager.getTexture("blankCoin")});
        }
    }
};

void Game::updateRes(float newScreenWidth, float newScreenHeight) {
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
    for (auto& col : grid2d) {
        for (auto&& row : col) {
            // Update gameRec pos for class instances to calculate from
            row.updateGameRec(recSrc);
            // Update cell position
            row.updateCellRec(Rectangle{
                static_cast<float>(row.getGameRec().x + ((row.getColumnPos()) * (row.getGameRec().width / COLS))),
                static_cast<float>(row.getGameRec().y + ((row.getRowPos()) * (row.getGameRec().height / ROWS))),
                static_cast<float>(row.getGameRec().width / COLS),
                static_cast<float>(row.getGameRec().height / ROWS)});
            // Update coin pos when blank and when not blank
            if (row.isBlank()) {
                row.updateCoinDest(Rectangle{
                    static_cast<float>(row.getGameRec().x + (row.getColumnPos() * (row.getGameRec().width / COLS))),
                    static_cast<float>(row.getGameRec().y - row.getCellRec().height),
                    row.getCellRec().width,
                    row.getCellRec().height});
            } else {
                row.updateCoinDest(Rectangle{
                    row.getCellRec().x,
                    row.getCellRec().y,
                    row.getCellRec().width,
                    row.getCellRec().height});
            }
        }
    }
};

void Game::draw() {
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    for (auto& col : grid2d) {
        for (auto&& row : col) {
            row.draw();
        }
    }
};

void Game::tick(Vector2 mousePos, std::vector<Player>& players) {
    for (auto& col : grid2d) {
        for (auto&& row = col.rbegin(); row != col.rend(); ++row) {
            Rectangle columnRec{
                col.begin()->getCellRec().x,
                col.begin()->getCellRec().y,
                col.begin()->getCellRec().width,
                col.begin()->getGameRec().height};
            // mouse hover effect for col indication
            if (CheckCollisionPointRec(mousePos, columnRec)) {
                DrawRectangle(
                    columnRec.x,
                    columnRec.y,
                    columnRec.width,
                    columnRec.height,
                    ColorAlpha(players[playerIndex].getPlayerColor(), 0.1f));
            }

            // player click action if their turn
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, columnRec)) {
                if (row->isBlank() && row->getOwner().getPlayerNumber() == 0) {
                    row->updateCell(players[playerIndex]);
                    row->setCoinIsDropping();
                    players[playerIndex].tick();
                    if (!winCon(players[playerIndex])) {
                        playerIndex = -playerIndex + 1;
                        setTurnPlayer(players[playerIndex]);
                    }
                    if (players[0].getNumOfCoinsLeft() == 0 && players[1].getNumOfCoinsLeft() == 0) {
                        gameover = true;
                    }
                    return;
                }
            }
        }
    }
};

bool Game::winCon(Player& previousPlayer) {
    /********************************************** WIN CONDITIONS ****************************************************/
    /** VERTICAL **/
    for (auto& col : grid2d) {
        for (auto&& row = col.rbegin(); row != col.rend(); ++row) {
            if (row + 1 != col.rend()) {
                if (previousPlayer.getPlayerNumber() == (row + 1)->getOwner().getPlayerNumber() &&
                    previousPlayer.getPlayerNumber() == row->getOwner().getPlayerNumber()) {
                    previousPlayer.incrementVerticalCounter();
                    if (previousPlayer.getCoinCounter().vertical == 4) {
                        gameover = true;
                        winner = previousPlayer;
                        return true;
                    }
                } else {
                    previousPlayer.resetVerticalCounter();
                }
            }
        }
    }

    /** HORIZONTAL **/
    for (int r = 5; r > 0; --r) {
        for (std::size_t c = 0; c < grid2d.size(); ++c) {
            if (c + 1 < grid2d.size() &&
                previousPlayer.getPlayerNumber() == grid2d.at(c).at(r).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(c + 1).at(r).getOwner().getPlayerNumber()) {
                previousPlayer.incrementHorizontalCounter();
                if (previousPlayer.getCoinCounter().horizontal == 4) {
                    gameover = true;
                    winner = previousPlayer;
                    return true;
                }
            } else
                previousPlayer.resetHorizontalCounter();
        }
    }
    /** DIAGONOL UPWARDS **/
    int cDU = 3, rDU = 5;
    // Do not compare unsigned types with negative numbers. Negative numbers are unrepresentable by unsigned types.
    // An unsigned type compared with a signed integer type <= will be converted to unsigned.
    // std::ssize() makes a copy of an unsigned type as signed and satisfies the compiler warning
    while (cDU > -1 && rDU > 2) {
        for (int i = cDU, j = rDU; i < std::ssize(grid2d) && j >= 0; ++i, --j) {
            if (i + 1 < std::ssize(grid2d) &&
                j - 1 >= 0 &&
                previousPlayer.getPlayerNumber() == grid2d.at(i).at(j).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(i + 1).at(j - 1).getOwner().getPlayerNumber()) {
                previousPlayer.incrementDiagonolUpwardsCounter();
                if (previousPlayer.getCoinCounter().diagonolUpwards == 4) {
                    gameover = true;
                    winner = previousPlayer;
                    return true;
                }
            } else {
                previousPlayer.resetDiagUpwardsCounter();
            }
        }
        if (cDU == 0) --rDU;
        if (cDU > 0) --cDU;
    }
    /** DIAGONOL DOWNWARDS **/
    int cDD = 3, rDD = 0;
    while (cDD > -1 && rDD < 3) {
        for (int i = cDD, j = rDD; i < std::ssize(grid2d) && j < std::ssize(grid2d.front()); ++i, ++j) {
            if (i + 1 < std::ssize(grid2d) &&
                j + 1 < std::ssize(grid2d.front()) &&
                previousPlayer.getPlayerNumber() == grid2d.at(i).at(j).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(i + 1).at(j + 1).getOwner().getPlayerNumber()) {
                previousPlayer.incrementDiagonolDownwardsCounter();
                if (previousPlayer.getCoinCounter().diagonolDownwards == 4) {
                    gameover = true;
                    winner = previousPlayer;
                    return true;
                }
            } else {
                previousPlayer.resetDiagDownwardsCounter();
            }
        }
        if (cDD == 0) ++rDD;
        if (cDD > 0) --cDD;
    }
    /********************************************** END WIN CONDITIONS ************************************************/
    return false;
};

void Game::setPlayerColor(Player& player, int n) {
    // Not sure how to use raylibs macros as an enum list so took a long way about it with a switch case.
    Color color;
    switch (n) {
        case 0:
            color = RED;
            break;
        case 1:
            color = YELLOW;
            break;
        default:
            color = WHITE;
            break;
    }
    // Must match each value as part of raylibs Color class
    for (int i = 0; i < sizeOfPlayerColors; ++i) {
        if (color.r == colors[i].color.r &&
            color.g == colors[i].color.g &&
            color.b == colors[i].color.b &&
            color.a == colors[i].color.a) {
            player.setPlayerColor(colors[i].color);
            player.setPlayerTexture(colors[i].coin);
        }
    }
}

Game::GameState Game::getGameState() {
    GameState state{
        gameover,
        paused,
        winner};
    return state;
};

void Game::reset(std::vector<Player>& players) {
    gameover = false;
    paused = false;
    // randomly swap or assign new colors for each player
    int randPlayerColor = GetRandomValue(0, 1);
    Game::setPlayerColor(players[0], randPlayerColor);
    Game::setPlayerColor(players[1], -randPlayerColor + 1);
    for (auto& player : players) {
        player.resetNumOfCoinsLeft();
        player.resetVerticalCounter();
        player.resetHorizontalCounter();
        player.resetDiagDownwardsCounter();
        player.resetDiagUpwardsCounter();
    }
    for (auto& column : grid2d) {
        for (auto&& row : column) {
            row.reset();
        }
    }
};