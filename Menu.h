#ifndef MENU_H
#define MENU_H

#include "raylib.h"

class Menu {
   public:
    Menu(float x,
         float y,
         int width,
         int height);
    void active() { !activeMenu; }

   private:
    bool activeMenu{true};
    Rectangle srcRec{};
};

#endif  // !MENU_H