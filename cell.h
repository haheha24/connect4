#ifndef CELL_H
#define CELL_H

#include "raylib.h"
#include "player.h"

class Player;

class Cell
{
public:
    Cell(int row, int col, Rectangle cellRec, Rectangle gameRec);
    int getRowPos() { return row; }
    int getColumnPos() { return column; }
    bool isBlank() { return blank; }
    void setBlank(bool b) { blank = b; }
    Rectangle getCellRec() { return cellRec; }
    void updateCellRec(Rectangle newRec) { cellRec = newRec; }
    Player getOwner() { return owner; }
    void updateCell(Player player);
    Rectangle getGameRec() { return gameRec; }
    void updateGameRec(Rectangle &newGameRec) { gameRec = newGameRec; }

    void drawCoin();

protected:
    void drawCoinDrop();

private:
    int row{};
    int column{};
    bool blank{true};
    Rectangle cellRec{};
    Player owner{0};
    Rectangle gameRec{};
};
#endif
