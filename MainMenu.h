#ifndef MAINMENU_H
#define MAINMENU_H

#include <array>

#include "Menu.h"

class MainMenu : Menu {
   public:
    MainMenu();

   private:
    bool initGame{false};
    typedef enum MENU_OPTIONS { NEW_GAME = 0,
                                OPTIONS,
                                CLOSE_MENU,
                                EXIT };
};

#endif  // !MAINMENU_H