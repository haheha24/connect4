#include "Cell.h"

Cell::Cell(int col, int row, Rectangle cellRec, Rectangle gameRec, Texture2D texBlank) : column(col), row(row), cellRec(cellRec), gameRec(gameRec), texBlank(texBlank) {};

void Cell::draw() {
    // Coin pos per frame
    if (isCoinDropping && blank) {
        float deltaTime = GetFrameTime();
        velocity = gravity * deltaTime;
        coinDest.y += velocity;
        if (coinDest.y > cellRec.y) {
            coinDest.y = cellRec.y;
            blank = false;
        }
    }
    // Player coin
    if (isCoinDropping) {
        DrawTexturePro(texCoin, Rectangle{0.f, 0.f, static_cast<float>(texCoin.width), static_cast<float>(texCoin.height)}, coinDest, {}, 0.f, WHITE);
    }
    // Blank
    if (blank) {
        DrawTexturePro(texBlank, Rectangle{0.f, 0.f, static_cast<float>(texBlank.width), static_cast<float>(texBlank.height)}, cellRec, {}, 0.f, WHITE);
    }
}

void Cell::updateCell(Player& player) {
    owner = player;
    texCoin = owner.getPlayerCoinTexture();
};

void Cell::reset() {
    blank = true;
    owner = Player();
    texCoin = {};
    isCoinDropping = false;
    velocity = 0;
    coinDest = {
        static_cast<float>(gameRec.x + (column * (gameRec.width / 7))),
        gameRec.y - cellRec.height,
        cellRec.width,
        cellRec.height};
};
