#include "tetris.h"
#include <cstdlib>
int main(int argc, char* argv[])
{
    Tetris game(argc, argv);
    game.run();
    return EXIT_FAILURE;
}
