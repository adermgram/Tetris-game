#include "tetris.h"
#include <cstdlib>
#include <ctime>
int main(int argc, char* argv[])
{
    srand(time(nullptr));
    Tetris game(argc, argv);
    game.run();
    return EXIT_FAILURE;
}
