#include "raylib.h"
#include "game.h"
#include <reasings.h>

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
    switch (currentState)
    {
    case GameStates::PreGame:
        DrawPreGame();
        break;
    case GameStates::Game:
        DrawGame();
        break;
    case GameStates::PostGame:
        DrawPostGame();
        break;
    }
}

void Game::Update()
{
    switch (currentState)
    {
    case GameStates::PreGame:
        UpdatePreGame();
        break;
    case GameStates::Game:
        UpdateGame();
        break;
    case GameStates::PostGame:
        UpdatePostGame();
        break;
    }
}

void Game::DrawPreGame()
{
    Rectangle buttonRect;
    buttonRect.width = (float)GetScreenWidth();
    buttonRect.height = GetScreenHeight() * 0.33f;
    buttonRect.x = 0.0f;
    buttonRect.y = 0.0f;
    if (GuiButton(buttonRect, "Easy"))
    {
        difficulty = Difficulties::Easy;
        currentState = GameStates::Game;
    }

    buttonRect.y += GetScreenHeight() * 0.33f;
    if (GuiButton(buttonRect, "Medium"))
    {
        difficulty = Difficulties::Medium;
        currentState = GameStates::Game;
    }

    buttonRect.y += GetScreenHeight() * 0.33f;
    if (GuiButton(buttonRect, "Hard"))
    {
        difficulty = Difficulties::Hard;
        currentState = GameStates::Game;
    }
}

void Game::UpdatePreGame()
{
}

void Game::DrawGame()
{
    board.DrawUi();

    BeginMode2D(camera);

    board.Draw();

    EndMode2D();

    int buttonStart = 0;
    if (board.GetDirection() == Directions::Left || board.GetDirection() == Directions::Right)
        buttonStart = 1;

    for (int i = buttonStart; i < 7; i++)
    {
        if (GuiButton({ 80.0f + (90.0f * i), 30.0f, 60.0f, 30.0f }, "Drop") && !camRotating)
        {
            placed = board.PlaceChip(i, currentPlayer);
        }
    }
}

void Game::UpdateGame()
{
    if (turn % 4 == 0 && turn > 0)
    {
        if (rotating)
        {
            StartCameraRotation();
        }
        turn++;
    }

    if (RotateCamera())
    {
        board.Rotate();
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

void Game::StartCameraRotation()
{
    cameraStartRot = camera.rotation;
    cameraTimer = 0.0f;
    camRotating = true;
}

bool Game::RotateCamera()
{
    if (!camRotating)
    {
        return false;
    }

    cameraTimer += GetFrameTime();
    if (cameraTimer >= CAMERA_ROTATION_DUR)
    {
        cameraTimer = CAMERA_ROTATION_DUR;
        camRotating = false;
        return true;
    }

    camera.rotation = EaseSineInOut(cameraTimer, cameraStartRot, 90.0f, CAMERA_ROTATION_DUR);

    return false;
}

void Game::DrawPostGame()
{
}

void Game::UpdatePostGame()
{
}
