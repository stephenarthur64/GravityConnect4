#include "raylib.h"
#include "game.h"

void Game::Init()
{
    board.Init();
}

void Game::Draw()
{
    DrawFPS(0, 0);
    board.Draw();
}

void Game::Update()
{
    if (IsKeyReleased(KEY_ONE))
    {
        board.PlaceChip(0, currentPlayer);
    }
    if (IsKeyReleased(KEY_TWO))
    {
        board.PlaceChip(1, currentPlayer);
    }
    if (IsKeyReleased(KEY_THREE))
    {
        board.PlaceChip(2, currentPlayer);
    }
    if (IsKeyReleased(KEY_FOUR))
    {
        board.PlaceChip(3, currentPlayer);
    }
    if (IsKeyReleased(KEY_FIVE))
    {
        board.PlaceChip(4, currentPlayer);
    }
    if (IsKeyReleased(KEY_SIX))
    {
        board.PlaceChip(5, currentPlayer);
    }
    if (IsKeyReleased(KEY_SEVEN))
    {
        board.PlaceChip(6, currentPlayer);
    }

    if (IsKeyReleased(KEY_R))
    {
        currentPlayer = Team::Red;
    }
    else if (IsKeyReleased(KEY_Y))
    {
        currentPlayer = Team::Yellow;
    }

    if (IsKeyReleased(KEY_Q))
    {
        board.Rotate();
    }

    board.Update();
}
