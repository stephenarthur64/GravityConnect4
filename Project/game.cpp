#include "raylib.h"
#include "game.h"

void Game::Init()
{
    camera.rotation = 0.0f;
    camera.target = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.zoom = 1.0f;
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    board.Init();
    turn = 0;
}

void Game::Draw()
{
    DrawFPS(0, 0);

    BeginMode2D(camera);

    board.Draw();

    EndMode2D();

    int buttonStart = 0;
    if (board.GetDirection() == Directions::Left || board.GetDirection() == Directions::Right)
        buttonStart = 1;

    for (int i = buttonStart; i < 7; i++)
    {
        if (GuiButton({ 80.0f + (90.0f * i), 30.0f, 60.0f, 30.0f }, "Drop"))
        {
            placed = board.PlaceChip(i, currentPlayer);
        }
    }
}

void Game::Update()
{
    if (turn % 4 == 0 && turn > 0)
    {
        if (rotating)
        {
             board.Rotate();
             camera.rotation += 90.0f;
        }
        turn++;
    }

    if (placed)
    {
        turn++;
        if (currentPlayer == Team::Red)
        {
            currentPlayer = Team::Yellow;
        }
        else if (currentPlayer == Team::Yellow)
        {
            currentPlayer = Team::Red;
        }
        placed = false;
    }

    if (IsKeyReleased(KEY_Q))
    {
        rotating = !rotating;
    }

    board.Update();

    switch (currentPlayer)
    {
    case Team::Red:
        DrawText("Turn Red", GetScreenWidth() - 140.0f, 20, 20, RED);
        break;
    case Team::Yellow:
        DrawText("Turn Yellow", GetScreenWidth() - 140.0f, 20, 20, YELLOW);
        break;
    default:
        break;
    }

}
