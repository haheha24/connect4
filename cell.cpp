#include "Cell.h"

Cell::Cell(int col, int row, Rectangle cellRec, Rectangle gameRec, Texture2D texture) : column(col), row(row), cellRec(cellRec), gameRec(gameRec), tex(texture){};

void Cell::drawCoinDrop() {
    Rectangle gridColumn{static_cast<float>(gameRec.x + (column * (gameRec.width / 7))),
                         static_cast<float>(gameRec.y + (row * (gameRec.height / 6))),
                         cellRec.width,
                         gameRec.height};

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        /* frame++; */
        runningTime = 0.f;
        /* if (frame > maxFrame) frame = 0; */
    }
    DrawTexturePro(tex, Rectangle{0.f, 0.f, static_cast<float>(tex.width), static_cast<float>(tex.height)}, cellRec, {}, 0.f, WHITE);
};
void Cell::drawCoin() {
    if (drop) DrawTexturePro(tex, Rectangle{0.f, 0.f, static_cast<float>(tex.width), static_cast<float>(tex.height)}, cellRec, {}, 0.f, WHITE);
};

void Cell::updateCell(Player& player) {
    blank = false;
    owner = player;
    updateTexture(owner.getPlayerCoinTexture());
};
