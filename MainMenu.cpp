#include "MainMenu.h"

MainMenu::MainMenu(TextureLoader& texManager) : textureManager(texManager) {
    const Texture2D& menuSpriteRed{textureManager.getTexture("menuSprite_red")};
    const Texture2D& menuSpriteWhite{textureManager.getTexture("menuSprite_white")};
    // Main menu button
    list.push_back((Button){
        menuRec,
        menuSpriteWhite,
        menuSpriteRed,
        Button::MAIN_MENU});
    // New game button
    list.push_back((Button){
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - menuSpriteWhite.height / 5.f) / 2.f,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::NEW_GAME});
    // Exit game button
    list.push_back((Button){
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - menuSpriteWhite.height / 5.f) / 2.f + 100,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::EXIT});
    // Back button
    list.push_back((Button){
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - menuSpriteWhite.height / 5.f) / 2.f + 200,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::BACK});
    // Exit button #2
    list.push_back((Button){
        Rectangle{(GetScreenWidth() - 200) / 3.f,
                  (GetScreenHeight() - list[2].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::EXIT_2});
    // Back button #2
    list.push_back((Button){
        Rectangle{((GetScreenWidth() - 200) / 3.f) * 2,
                  (GetScreenHeight() - list[3].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::BACK_2});
    // New Game button #2
    list.push_back((Button){
        Rectangle{(GetScreenWidth() - 200) / 3.f,
                  (GetScreenHeight() - list[2].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100},
        menuSpriteWhite,
        menuSpriteRed,
        Button::NEW_GAME_2});
}

void MainMenu::updateRes() {
    // Main Menu rectangle and button
    menuRec = {GetScreenWidth() * 0.9f,
               0,
               GetScreenWidth() * 0.1f,
               GetScreenHeight() * 0.1f};

    list[0].updateDestRec(
        Rectangle{GetScreenWidth() * 0.9f,
                  0,
                  GetScreenWidth() * 0.1f,
                  GetScreenHeight() * 0.1f});
    // New game button
    list[1].updateDestRec(
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - list[1].getTextureState().height / 5.f) / 2.f,
                  200,
                  100});
    // Exit button
    list[2].updateDestRec(
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - list[2].getTextureState().height / 5.f) / 2.f + 100,
                  200,
                  100});
    // Back button
    list[3].updateDestRec(
        Rectangle{(GetScreenWidth() - 200) / 2.f,
                  (GetScreenHeight() - list[3].getTextureState().height / 5.f) / 2.f + 200,
                  200,
                  100});
    // Exit button #2
    list[4].updateDestRec(
        Rectangle{(GetScreenWidth() - 200) / 3.f,
                  (GetScreenHeight() - list[2].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100});
    // Back button #2
    list[5].updateDestRec(
        Rectangle{((GetScreenWidth() - 200) / 3.f) * 2,
                  (GetScreenHeight() - list[3].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100});
    // New Game button #2
    list[6].updateDestRec(
        Rectangle{(GetScreenWidth() - 200) / 3.f,
                  (GetScreenHeight() - list[2].getTextureState().height / 5.f) / 2.f + 50,
                  200,
                  100});
};