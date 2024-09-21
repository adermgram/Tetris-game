#include "tetris.h"
int main(int argc, char* argv[])
{
    auto game = Tetris(argc, argv);
    game.run();
}