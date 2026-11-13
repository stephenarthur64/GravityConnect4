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
    buttonRect.width = (float)GetScreenWidth() / 2.0f;
    buttonRect.height = GetScreenHeight() * 0.33f;
    buttonRect.x = 0.0f;
    buttonRect.y = 0.0f;
    if (GuiButton(buttonRect, "Easy"))
    {
        difficulty = Difficulties::Easy;
    }

    buttonRect.y += GetScreenHeight() * 0.33f;
    if (GuiButton(buttonRect, "Medium"))
    {
        difficulty = Difficulties::Medium;
    }

    buttonRect.y += GetScreenHeight() * 0.33f;
    if (GuiButton(buttonRect, "Hard"))
    {
        difficulty = Difficulties::Hard;
    }

    buttonRect.x += buttonRect.width;
    if (GuiButton(buttonRect, "Start"))
    {
        StartGame();
    }

    Rectangle dropdownRect;
    dropdownRect.width = GetScreenWidth() * 0.25f;
    dropdownRect.height = GetScreenHeight() * 0.1f;
    dropdownRect.x = (float)GetScreenWidth() / 2.0f;

    dropdownRect.y = 0;
    DrawText("Red Team", dropdownRect.x, dropdownRect.y, dropdownRect.height / 2.0f, RED);

    dropdownRect.y += GetScreenHeight() * 0.1f;
    if (GuiDropdownBox(dropdownRect, "Player;MiniMax;Monty-Carlo", &player1TypeChosenInt, dropdownEditMode1))
    {
        dropdownEditMode1 = !dropdownEditMode1;
    }

    dropdownRect.y = 0;
    dropdownRect.x += dropdownRect.width;
    DrawText("Yellow Team", dropdownRect.x, dropdownRect.y, dropdownRect.height / 2.0f, YELLOW);

    dropdownRect.y += GetScreenHeight() * 0.1f;
    if (GuiDropdownBox(dropdownRect, "Player;MiniMax;Monty-Carlo", &player2TypeChosenInt, dropdownEditMode2))
    {
        dropdownEditMode2 = !dropdownEditMode2;
    }
}

void Game::UpdatePreGame()
{
}

void Game::StartGame()
{
    player1TypeChosen = static_cast<PlayerType>(player1TypeChosenInt);
    player2TypeChosen = static_cast<PlayerType>(player2TypeChosenInt);

    teamToType[Team::Red] = player1TypeChosen;
    teamToType[Team::Yellow] = player2TypeChosen;


    currentState = GameStates::Game;
}

int Game::GetAIMove()
{
    int move = 1;

    tree.BuildTree(diffToDepth[difficulty], board, currentPlayer);

    if (teamToType[currentPlayer] == PlayerType::MiniMax)
    {
        move = tree.GetMiniMaxMove();
    }
    else if (teamToType[currentPlayer] == PlayerType::MonteCarlo)
    {
        move = tree.GetMonteCarloMove();
    }

    return move;
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

    // Placing past this point
    if (camRotating)
        return;

    if (teamToType[currentPlayer] == PlayerType::Player)
    {
        for (int i = buttonStart; i < 7; i++)
        {
            if (GuiButton({ 80.0f + (90.0f * i), 30.0f, 60.0f, 30.0f }, "Drop"))
            {
                placed = board.PlaceChip(i, currentPlayer);
            }
        }
    }
    else
    {
        int chosen = GetAIMove();
        placed = board.PlaceChip(chosen, currentPlayer);
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
