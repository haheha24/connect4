#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "raylib.h"

class Player
{
public:
    Player(int playerNumber = 0);
    void tick();
    int getPlayerNumber() { return playerNumber; }
    Color getPlayerColor() { return playerColor; }
    void setPlayerColor(Color& newColor);
    Texture2D getPlayerCoinTexture() { return playerCoinTexture; }
    void setPlayerTexture(Texture2D coin);
    int getCoins() { return numOfCoinsLeft; }
    std::string getName() { return name; }
    int getNumOfCoinsLeft() { return numOfCoinsLeft; }

private:
    Color playerColor{};
    Texture2D playerCoinTexture{};
    int playerNumber{};
    int numOfCoinsLeft{ 21 };
    bool hasTurns{ true };
    std::string name{ "Player " };
};

#endif