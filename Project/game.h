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
    Difficulties difficultyMiniMax = Difficulties::Easy;
    Difficulties difficultyMonteCarlo = Difficulties::Easy;

    void DrawPreGame();
    void UpdatePreGame();
    bool dropdownEditMode1 = false;
    bool dropdownEditMode2 = false;
    int player1TypeChosenInt = 0;
    int player2TypeChosenInt = 0;
    PlayerType player1TypeChosen = PlayerType::Player;
    PlayerType player2TypeChosen = PlayerType::Player;

    void StartGame();
    void ResetGame();

    int GetAIMove();

    void DrawGame();
    void UpdateGame();

    void StartCameraRotation();
    bool RotateCamera();
    float cameraTimer = 0.0f;
    float cameraStartRot = 0.0f;
    const float CAMERA_ROTATION_DUR = 0.5f;
    bool canRotate = false;
    bool camRotating;

    void DrawPostGame();
    void UpdatePostGame();
    GameStates currentState = GameStates::PreGame;

    Board board;
    Team currentPlayer = Team::Red;
    int turn = 0;
    bool rotationOn = true;
    bool placed;

    Camera2D camera;

    std::map<Team, PlayerType> teamToType;
    std::map<Difficulties, int> diffToDepthMiniMax = {
        {Difficulties::Easy, 2},
        {Difficulties::Medium, 4},
        {Difficulties::Hard, 6}
    };
    std::map<Difficulties, int> diffToDepthMonteCarlo = {
        {Difficulties::Easy, 100},
        {Difficulties::Medium, 1000},
        {Difficulties::Hard, 10000}
    };

    Tree tree;
    int lastPlayerMove = 0;
};