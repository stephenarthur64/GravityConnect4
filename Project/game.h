#pragma once
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
};