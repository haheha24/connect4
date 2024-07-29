#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "raylib.h"

class Player {
   private:
    typedef struct {
        int vertical{1};
        int horizontal{1};
        int diagonolUpwards{1};
        int diagonolDownwards{1};
    } Counters;
    Counters coinCounter{};

   public:
    Player(int playerNumber = 0);
    void tick();
    int getPlayerNumber() { return playerNumber; }
    Color getPlayerColor() { return playerColor; }
    void setPlayerColor(Color& newColor);
    Texture2D getPlayerCoinTexture() { return playerCoinTexture; }
    void setPlayerTexture(Texture2D coin);
    int getNumOfCoinsLeft() { return numOfCoinsLeft; }
    void resetNumOfCoinsLeft() { numOfCoinsLeft = 21; }
    std::string getName() { return name; }
    Counters getCoinCounter() { return coinCounter; }
    void incrementVerticalCounter();
    void resetVerticalCounter();
    void incrementHorizontalCounter();
    void resetHorizontalCounter();
    void incrementDiagonolDownwardsCounter();
    void resetDiagDownwardsCounter();
    void incrementDiagonolUpwardsCounter();
    void resetDiagUpwardsCounter();

   private:
    Color playerColor{};
    Texture2D playerCoinTexture{};
    int playerNumber{};
    int numOfCoinsLeft{21};
    std::string name{"Player "};
};

#endif