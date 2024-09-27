#pragma once

class Ball
{
public:
    Ball() = default;
    void Update();
    void Draw();

private:
    unsigned int x = 100;
    unsigned int y = 100;
    int speedX = 5;
    int speedY = 5;
    unsigned int radius = 15;
};
