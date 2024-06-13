#include "player.h"


Player::Player() {};

void Player::turn() {
    numOfCoinsLeft > 0 ? numOfCoinsLeft -= 1 : !hasTurns;
};