#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow* The_Last_Guardian = new GameWindow();

    The_Last_Guardian->game_play();

    delete The_Last_Guardian;

    return 0;
}
