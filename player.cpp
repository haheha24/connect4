#include "player.h"

Player::Player(int playerNumber) : playerNumber(playerNumber)
{
    name.append(std::to_string(playerNumber));
};

Color Player::setPlayerColor(Color newColor) { return playerColor = newColor; }

void Player::tick()
{
    numOfCoinsLeft > 0 ? numOfCoinsLeft -= 1 : hasTurns = false;
};