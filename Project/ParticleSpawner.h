#pragma once

#include "Particle.h"

class ParticleSpawner
{
public:
    void SetValues(Vector2 t_pos, int t_angleLeeway, float t_dirAngle);

    void ClearColors() { colors.clear(); }
    void AddColor(Color t_color);

    void Spawn();
    void Spawn(int t_amount);
    void CircularSpawn(int t_amount, float t_radius);

    void Update();
    void Draw();

    bool CheckIfParticalsActive();
private:
    // Randomizing functions
    float RandomizeDir();
    Color RandomizeColor();
    Vector2 PosOnCircle(float t_angle, float t_radius);

    Vector2 position;

    const int MAX_PARTICLES = 10;
    std::vector<Particle> particles;

    int angleLeeway;
    float dirAngle;

    std::vector<Color> colors;

    bool paused = false;
    bool active = false;
};
