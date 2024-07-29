#include "Button.h"

Button::Button(Rectangle dest, Texture2D tex, Texture2D texHover, MENU_OPTIONS OPTION) : destRec{dest},
                                                                                         texture(tex),
                                                                                         textureHover(texHover),
                                                                                         option(OPTION) {
    switch (OPTION) {
        case MAIN_MENU:
            srcRec = {1870,
                      835,
                      200,
                      200};
            break;
        case NEW_GAME:
            srcRec = {0,
                      tex.height / 5.f * 3,
                      tex.width / 3.8f,
                      tex.height / 5.f};
            break;
        case EXIT:
            srcRec = {
                tex.width / 3.75f * 2,
                tex.height / 5.f * 3,
                tex.width / 3.8f,
                tex.height / 5.f};
            break;
        case BACK:
            srcRec = {
                0,
                tex.height / 5.f * 4,
                tex.width / 3.8f,
                tex.height / 5.f};
            break;
        case EXIT_2:
            srcRec = {
                tex.width / 3.75f * 2,
                tex.height / 5.f * 3,
                tex.width / 3.8f,
                tex.height / 5.f};
            break;
        case BACK_2:
            srcRec = {
                0,
                tex.height / 5.f * 4,
                tex.width / 3.8f,
                tex.height / 5.f};
            break;
        case NEW_GAME_2:
            srcRec = {0,
                      tex.height / 5.f * 3,
                      tex.width / 3.8f,
                      tex.height / 5.f};
            break;
        default:
            srcRec = {};
            break;
    }
}

void Button::draw(Vector2 origin = {}, float rotation = 0.f, Color tint = WHITE) {
    if (CheckCollisionPointRec(GetMousePosition(), destRec)) {
        textureState = textureHover;
    } else {
        textureState = texture;
    }
    DrawTexturePro(textureState, srcRec, destRec, origin, rotation, tint);
};

Rectangle Button::getRec() { return destRec; }
void Button::updateDestRec(Rectangle newRec) {
    destRec = newRec;
}