#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Player(int playerNumber = 0);
    void tick();
    int getPlayerNumber() { return playerNumber; }
    Color getPlayerColor() { return playerColor; }
    Color setPlayerColor(Color newColor) { return playerColor = newColor; }
    int getCoins() { return numOfCoinsLeft; }
    bool getPlayerTurn() { return playerTurn; }
    void setPlayerTurn(bool turn) { playerTurn = turn; }
private:
    Color playerColor;
    int playerNumber{};
    bool playerTurn{ false };
    int numOfCoinsLeft{ 21 };
    bool hasTurns{ true };
};

#endif