#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>

#include "Button.h"
#include "raylib.h"
#include "textureLoader.h"

class Button;

class MainMenu {
   public:
    MainMenu(TextureLoader& texManager);
    Rectangle getMenuRec() { return menuRec; }
    Button getMenu() { return list[0]; }
    std::vector<Button> getMenuList() { return list; }
    void toggle() { activeMenu = !activeMenu; }
    void on() { activeMenu = true; }
    void off() { activeMenu = false; }
    bool isActive() { return activeMenu; }
    void updateRes();
    bool exitWindowRequest{false};
    bool exitWindow{false};

   private:
    bool activeMenu{false};

    std::vector<Button> list;
    Rectangle menuRec{GetScreenWidth() * 0.9f,
                      0,
                      GetScreenWidth() * 0.1f,
                      GetScreenHeight() * 0.1f};  // the position for the cogwheel menu button
    TextureLoader textureManager;
};

#endif  // !MAINMENU_H