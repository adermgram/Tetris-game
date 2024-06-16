#include "tetris.h"
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

Tetris::Tetris()
{
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("fonts/BebasNeue-Regular.ttf", 64, 0, 0);

    Game game = Game();
    while (WindowShouldClose() == false) 
    {
        UpdateMusicStream(game.music);
        game.handleInput();
        if (EventTriggered(0.2))
        {
            game.moveBlockDown();
        }
        BeginDrawing();
        ClearBackground(black);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {345, 450}, 40, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, darkGrey);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, darkGrey);
        game.draw();
        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
}
