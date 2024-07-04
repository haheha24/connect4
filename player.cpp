#include "player.h"

Player::Player(int playerNumber) : playerNumber(playerNumber)
{
    name.append(std::to_string(playerNumber));
};

void Player::setPlayerColor(Color& newColor) {
    playerColor = newColor;
}

void Player::setPlayerTexture(Texture2D coin) {
    playerCoinTexture = coin;
}

void Player::tick()
{
    if (numOfCoinsLeft > 0) numOfCoinsLeft -= 1;
};