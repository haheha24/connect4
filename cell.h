#ifndef CELL_H
#define CELL_H

#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "textureLoader.h"

class Player;
class TextureLoader;

class Cell {
   public:
    Cell(int col, int row, Rectangle cellRec, Rectangle gameRec, Texture2D texBlank);
    int getRowPos() { return row; }
    int getColumnPos() { return column; }
    bool isBlank() { return blank; }
    Rectangle getCellRec() { return cellRec; }
    void updateCellRec(Rectangle newRec) { cellRec = newRec; }
    void updateCoinDest(Rectangle newDest) { coinDest = newDest; }
    Rectangle getGameRec() { return gameRec; }
    void updateGameRec(Rectangle& newGameRec) { gameRec = newGameRec; }
    Player getOwner() { return owner; }
    void updateCell(Player& player);
    void draw();
    void setCoinIsDropping() { isCoinDropping = true; }
    void reset();

   private:
    int column{};
    int row{};

    Rectangle cellRec{};
    Rectangle gameRec{};
    Rectangle coinDest{
        static_cast<float>(gameRec.x + (column * (gameRec.width / 7))),
        gameRec.y - cellRec.height,
        cellRec.width,
        cellRec.height};

    bool blank{true};
    Player owner{0};

    Texture2D texBlank{};
    Texture2D texCoin{};

    bool isCoinDropping{false};
    int gravity{1000};  // gravity
    float velocity{};
};
#endif
