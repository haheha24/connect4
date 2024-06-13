#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Player();
    void turn();
    Color getPlayerColor() { return playerColor; }
    Color setPlayerColor(Color newColor) { playerColor = newColor; }
    int getCoins() { return numOfCoinsLeft; };
private:
    Color playerColor;
    int numOfCoinsLeft{ 21 };
    bool hasTurns{ true };
};

#endif