#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <string>

#include "raylib.h"

class Button {
   public:
    enum MENU_OPTIONS {
        MAIN_MENU = 0,
        NEW_GAME,
        EXIT,
        BACK,
        EXIT_2,
        BACK_2,
        NEW_GAME_2
    };
    Button(Rectangle dest, Texture2D tex, Texture2D texHover, MENU_OPTIONS);
    virtual void draw(Vector2 origin, float rotation, Color tint);
    Rectangle getRec();
    Texture2D getTextureState() { return textureState; }
    int getOption() { return option; }
    void updateDestRec(Rectangle newRec);

   private:
    Rectangle srcRec{};
    Rectangle destRec{};
    Texture2D texture;
    Texture2D textureHover;
    Texture2D textureState = texture;
    int option{};
};

#endif  // !BUTTON_H