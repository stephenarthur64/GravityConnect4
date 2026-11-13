#pragma once
#include <raygui.h>
#include "Tree.h"
#include <map>

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

enum class PlayerType
{
    Player,
    MiniMax,
    MonteCarlo
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
    bool dropdownEditMode1 = false;
    bool dropdownEditMode2 = false;
    int player1TypeChosenInt = 0;
    int player2TypeChosenInt = 0;
    PlayerType player1TypeChosen = PlayerType::Player;
    PlayerType player2TypeChosen = PlayerType::Player;

    void StartGame();

    int GetAIMove();

    void DrawGame();
    void UpdateGame();

    void StartCameraRotation();
    bool RotateCamera();
    float cameraTimer = 0.0f;
    float cameraStartRot = 0.0f;
    const float CAMERA_ROTATION_DUR = 0.5f;
    bool camRotating;

    void DrawPostGame();
    void UpdatePostGame();
    GameStates currentState = GameStates::PreGame;

    Board board;
    Team currentPlayer = Team::Red;
    int turn = 0;
    bool rotating = true;
    bool placed;

    Camera2D camera;

    std::map<Team, PlayerType> teamToType;
    std::map<Difficulties, int> diffToDepth = {
        {Difficulties::Easy, 2},
        {Difficulties::Medium, 5},
        {Difficulties::Hard, 8}
    };

    Tree tree;
};