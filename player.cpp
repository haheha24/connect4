#include "player.h"


Player::Player(int playerNumber) : playerNumber(playerNumber) {};

void Player::tick() {
    numOfCoinsLeft > 0 ? numOfCoinsLeft -= 1 : !hasTurns;
};