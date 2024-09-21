#pragma once
#include "colors.h"
#include "game.h"
#include <string>

class Tetris {
  public:
    Tetris(int argc, char* argv[]);
    ~Tetris();
    void run();

  private:
    bool EventTriggered(double interval);

  private:
    std::string build_path;
    Font font;
    Game game;
    double lastUpdateTime = 0;
};
