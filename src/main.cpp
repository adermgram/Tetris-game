#include "tetris.h"
#include <new>
#include <cstdlib>

int main(int argc, char* argv[])
{
    srandom(time(nullptr));
    Tetris* game = new(std::nothrow) Tetris(argc, argv);
    if (game)
    {
        game->run();
    }
    return EXIT_FAILURE;
}
