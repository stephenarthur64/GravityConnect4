#pragma once
#include <raygui.h>
#include "Board.h"

class Game
{
public:
    void Init();
    void Draw();
    void Update();

private:
    Board board;
    Team currentPlayer = Team::Red;
    int turn = 0;
    bool rotating = true;
    bool placed;
    Camera2D camera;
};