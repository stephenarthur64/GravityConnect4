#pragma once
#include <raygui.h>
#include "Board.h"

enum class GameStates
{
    PreGame,
    Game,
    PostGame
};
enum class Difficulties
{
    Easy,
    Medium,
    Hard
};

class Game
{
public:
    void Init();
    void Draw();
    void Update();

private:
    Difficulties difficulty = Difficulties::Easy;

    void DrawPreGame();
    void UpdatePreGame();

    void DrawGame();
    void UpdateGame();

    void DrawPostGame();
    void UpdatePostGame();
    GameStates currentState = GameStates::PreGame;

    Board board;
    Team currentPlayer = Team::Red;
    int turn = 0;
    bool rotating = true;
    bool placed;

    Camera2D camera;
};