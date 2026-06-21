#include "portal.h"
#include "gui.h"

int main(){

    Portal portal;
    GUI gui(portal);
    gui.run();

    return 0;
}
