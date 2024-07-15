#include "game.h"

Game::Game(TextureLoader& textureManager,
           float screenWidth,
           float screenHeight,
           std::vector<Player>& players) : textureManager(textureManager),
                                           screenWidth(screenWidth),
                                           screenHeight(screenHeight),
                                           turnPlayer(players[0]) {
    // set game colors
    colors[0] = {true, RED, textureManager.getTexture("redCoin")};
    colors[1] = {true, YELLOW, textureManager.getTexture("yellowCoin")};

    Game::setPlayerColor(players[0], 1);
    Game::setPlayerColor(players[1], 2);

    for (int i = 0; i < COLS; ++i) {
        // setup the grid
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
            row.updateGameRec(recSrc);
            row.updateCellRec(Rectangle{
                static_cast<float>(row.getGameRec().x + ((row.getColumnPos()) * (row.getGameRec().width / COLS))),
                static_cast<float>(row.getGameRec().y + ((row.getRowPos()) * (row.getGameRec().height / ROWS))),
                static_cast<float>(row.getGameRec().width / COLS),
                static_cast<float>(row.getGameRec().height / ROWS)});
        }
    }
};

void Game::draw() {
    DrawRectangle(recSrc.x, recSrc.y, recSrc.width, recSrc.height, BLUE);
    for (auto& col : grid2d) {
        for (auto row = col.begin(); row != col.end(); ++row) {
            row->drawCoin();
            // delete when finished
            std::string posY{"Row: "};
            posY.append(std::to_string(row->getRowPos()), 0, 10);
            std::string posX{"Col: "};
            posX.append(std::to_string((row->getColumnPos())), 0, 10).append("\n" + posY);
            DrawText(posX.c_str(),
                     recSrc.x + (row->getColumnPos() * row->getCellRec().width),
                     recSrc.y + (row->getRowPos() * row->getCellRec().height),
                     11,
                     BLACK);
        }
    }
};

void Game::tick(Vector2 mousePos, std::vector<Player>& players) {
    Player previousPlayer = players[-playerIndex + 1];
    /********************************************** WIN CONDITIONS ****************************************************/
    /** HORIZONTAL **/
    for (int r = 5; r > 0; --r) {
        for (int c = 0; c < grid2d.size() - 1; ++c) {
            if (c + 1 < grid2d.size() - 1 &&
                previousPlayer.getPlayerNumber() == grid2d.at(c).at(r).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(c + 1).at(r).getOwner().getPlayerNumber()) {
                previousPlayer.incrementHorizontalCounter();
                if (previousPlayer.getCoinCounter().horizontal == 4) {
                    gameover = true;
                    winner = previousPlayer.getPlayerNumber();
                }
            } else
                previousPlayer.resetHorizontalCounter();
        }
    }
    /** DIAGONOL UPWARDS **/
    int cDU = 3, rDU = 5;
    while (cDU > -1 && rDU > 2) {
        for (int i = cDU, j = rDU; i < grid2d.size() && j >= 0; ++i, --j) {
            if (i + 1 < grid2d.size() &&
                j - 1 >= 0 &&
                previousPlayer.getPlayerNumber() == grid2d.at(i).at(j).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(i + 1).at(j - 1).getOwner().getPlayerNumber()) {
                previousPlayer.incrementDiagonolUpwardsCounter();
                if (previousPlayer.getCoinCounter().diagonolUpwards == 4) {
                    gameover = true;
                    winner = previousPlayer.getPlayerNumber();
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
        for (int i = cDD, j = rDD; i < grid2d.size() && j < grid2d.front().size(); ++i, ++j) {
            if (i + 1 < grid2d.size() &&
                j + 1 < grid2d.front().size() &&
                previousPlayer.getPlayerNumber() == grid2d.at(i).at(j).getOwner().getPlayerNumber() &&
                previousPlayer.getPlayerNumber() == grid2d.at(i + 1).at(j + 1).getOwner().getPlayerNumber()) {
                previousPlayer.incrementDiagonolDownwardsCounter();
                if (previousPlayer.getCoinCounter().diagonolDownwards == 4) {
                    gameover = true;
                    winner = previousPlayer.getPlayerNumber();
                }
            } else {
                previousPlayer.resetDiagDownwardsCounter();
            }
        }
        if (cDD == 0) ++rDD;
        if (cDD > 0) --cDD;
    }
    /********************************************** END WIN CONDITIONS ************************************************/

    for (auto& col : grid2d) {
        for (auto&& row = col.rbegin(); row != col.rend(); ++row) {
            /********************************************** WIN CONDITIONS ****************************************************/
            /** VERTICAL **/
            if (row + 1 != col.rend()) {
                // check if both cells belong to same player
                if (previousPlayer.getPlayerNumber() == (row + 1)->getOwner().getPlayerNumber() &&
                    previousPlayer.getPlayerNumber() == row->getOwner().getPlayerNumber()) {
                    previousPlayer.incrementVerticalCounter();
                    if (previousPlayer.getCoinCounter().vertical == 4) {
                        gameover = true;
                        winner = previousPlayer.getPlayerNumber();
                    }
                } else {
                    previousPlayer.resetVerticalCounter();
                }
            }
            /********************************************** END WIN CONDITIONS ************************************************/

            Rectangle columnRec{
                col.begin()->getCellRec().x,
                col.begin()->getCellRec().y,
                col.begin()->getCellRec().width,
                col.begin()->getGameRec().height};
            // mouse hover effect for col indication
            if (CheckCollisionPointRec(mousePos, columnRec)) {
                DrawText("highlighted", row->getGameRec().x + row->getColumnPos() * row->getCellRec().width, row->getGameRec().y + row->getRowPos() * row->getCellRec().height, 11, RED);  // replace with highlighted texture around cell
            }

            // player click action if their turn
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(mousePos, columnRec)) {
                if (row->isBlank() && row->getOwner().getPlayerNumber() == 0) {
                    row->updateCell(players[playerIndex]);
                    players[playerIndex].tick();
                    playerIndex = -playerIndex + 1;
                    Game::setTurnPlayer(players[playerIndex]);
                    return;
                }
            }
        }
    }

    if (players[0].getNumOfCoinsLeft() == 0 && players[1].getNumOfCoinsLeft() == 0) {
        gameover = true;
        winner = 0;
    }
};

void Game::setPlayerColor(Player& player, int n) {
    Color color;
    switch (n) {
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
    for (int i = 0; i < sizeOfPlayerColors; ++i) {
        if (color.r == colors[i].color.r &&
            color.g == colors[i].color.g &&
            color.b == colors[i].color.b &&
            color.a == colors[i].color.a &&
            colors[i].available) {
            player.setPlayerColor(colors[i].color);
            player.setPlayerTexture(colors[i].coin);
            colors[i].available = false;
        } else {
            colors[i].available = true;
        }
    }
}

// Input starting coordinate from grid using row and column.
// True for upwards and false for downwards.
void Game::checkDiagonol(int row, int column, bool direction) {
    if (direction) {  // upwards

    } else {  // downwards
    }
};

Game::GameState Game::getGameState() {
    GameState state{
        gameover,
        winner};
    return state;
};