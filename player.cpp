#include "Player.h"

Player::Player(int playerNumber) : playerNumber(playerNumber) {
    name.append(std::to_string(playerNumber));
};

void Player::setPlayerColor(Color& newColor) {
    playerColor = newColor;
}

void Player::setPlayerTexture(Texture2D coin) {
    playerCoinTexture = coin;
}

void Player::tick() {
    if (numOfCoinsLeft > 0) numOfCoinsLeft -= 1;
};

void Player::incrementVerticalCounter() { ++coinCounter.vertical; }
void Player::resetVerticalCounter() { coinCounter.vertical = 1; }
void Player::incrementHorizontalCounter() { ++coinCounter.horizontal; }
void Player::resetHorizontalCounter() { coinCounter.horizontal = 1; }
void Player::incrementDiagonolDownwardsCounter() { ++coinCounter.diagonolDownwards; }
void Player::resetDiagDownwardsCounter() { coinCounter.diagonolDownwards = 1; }
void Player::incrementDiagonolUpwardsCounter() { ++coinCounter.diagonolUpwards; }
void Player::resetDiagUpwardsCounter() { coinCounter.diagonolUpwards = 1; }