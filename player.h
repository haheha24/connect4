#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "raylib.h"

class Player
{
private:
    typedef struct {
        int vertical{ 1 };
        int horizontal{ 1 };
        int diagonolUpwards{ 1 };
        int diagonolDownwards{ 1 };
    }counters;
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
    counters coinCounter{};
private:
    Color playerColor{};
    Texture2D playerCoinTexture{};
    int playerNumber{};
    int numOfCoinsLeft{ 21 };
    std::string name{ "Player " };
};

#endif