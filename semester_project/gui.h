#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include "portal.h"

class GUI{
    private:
        Portal& portal;

        void mainMenu();
        void memberMenu();
        void courseMenu();
        void fileMenu();
        void mailMenu();

        string userInput(int y, int x, const char* prompt);

    public:
        GUI(Portal& p);
        void run();

};





#endif