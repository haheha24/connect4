#include "cell.h"

Cell::Cell(int row, int col, Rectangle cellRec, Rectangle gameRec) : row(row), column(col), cellRec(cellRec), gameRec(gameRec){};

void Cell::drawCoinDrop()
{
    /*
        centerX = cellRec.x + cellRec.width / 2
        centerY = gameRec.y
        loop : increase centerY until it is the center of the cell then call drawCoin();
     */
    int centerX = static_cast<int>(cellRec.x + cellRec.width / 2);
    int centerY = gameRec.y;
};
void Cell::drawCoin()
{
    if (owner.getPlayerNumber() == 0)
    {
        DrawCircle(gameRec.x + (row * cellRec.width) + (cellRec.width / 2),
                   gameRec.y + (column * cellRec.height) + (cellRec.height / 2),
                   ((cellRec.width + cellRec.height) / 2) * 0.33f,
                   WHITE);
        return;
    }
    DrawCircle(gameRec.x + (row * cellRec.width) + (cellRec.width / 2),
               gameRec.y + (column * cellRec.height) + (cellRec.height / 2),
               ((cellRec.width + cellRec.height) / 2) * 0.33f,
               owner.getPlayerColor());
    return;
};

void Cell::updateCell(Player player)
{
    blank = false;
    owner = player;
};
