#include "cell.h"

Cell::Cell(int col, int row, Rectangle cellRec, Rectangle gameRec, Texture2D texture) : column(col), row(row), cellRec(cellRec), gameRec(gameRec), tex(texture){};

void Cell::drawCoinDrop() {
    /*
        centerX = cellRec.x + cellRec.width / 2
        centerY = gameRec.y
        loop : increase centerY until it is the center of the cell then call drawCoin();
     */
    int centerX = static_cast<int>(cellRec.x + cellRec.width / 2);
    int centerY = gameRec.y;
};
void Cell::drawCoin() {
    DrawTexturePro(tex, Rectangle{0.f, 0.f, static_cast<float>(tex.width), static_cast<float>(tex.height)}, cellRec, {}, 0.f, WHITE);
};

void Cell::updateCell(Player& player) {
    blank = false;
    owner = player;
    updateTexture(owner.getPlayerCoinTexture());
};
