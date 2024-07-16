#ifndef CELL_H
#define CELL_H

#include "player.h"
#include "raylib.h"

class Player;

class Cell {
   public:
    Cell(int col, int row, Rectangle cellRec, Rectangle gameRec, Texture2D texture);
    int getRowPos() { return row; }
    int getColumnPos() { return column; }
    bool isBlank() { return blank; }
    void setBlank(bool b) { blank = b; }
    Rectangle getCellRec() { return cellRec; }
    void updateCellRec(Rectangle newRec) { cellRec = newRec; }
    Player getOwner() { return owner; }
    void updateCell(Player& player);
    Rectangle getGameRec() { return gameRec; }
    void updateGameRec(Rectangle& newGameRec) { gameRec = newGameRec; }
    void updateTexture(Texture2D coin) { tex = coin; }
    void drawCoin();

   protected:
    void drawCoinDrop();

   private:
    int column{};
    int row{};
    Rectangle cellRec{};
    Rectangle gameRec{};
    bool blank{true};
    Player owner{0};
    Texture2D tex{};
    bool drop{false};
    float runningTime{};
    float updateTime{};
    float deltaTime{};
};
#endif
