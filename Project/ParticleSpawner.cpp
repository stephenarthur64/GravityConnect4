#include "ParticleSpawner.h"

void ParticleSpawner::SetValues(Vector2 t_pos, int t_angleLeeway, float t_dirAngle)
{
    position = t_pos;
    angleLeeway = t_angleLeeway;
    dirAngle = t_dirAngle;
}

void ParticleSpawner::AddColor(Color t_color)
{
    colors.push_back(t_color);
}

void ParticleSpawner::Spawn()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        float randDir = RandomizeDir();
        int randSpeed = (rand() % 5) + 5;
        int randSize = (rand() % 7) + 7;
        Color randColor = RandomizeColor();

        particles.push_back(Particle(position, randSize, randSpeed, randDir, randColor));
    }

    active = true;
}

void ParticleSpawner::Spawn(int t_amount)
{
    for (int iteration = 0; iteration < t_amount; iteration++)
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            float randDir = RandomizeDir();
            int randSpeed = (rand() % 5) + 5;
            int randSize = (rand() % 7) + 7;
            Color randColor = RandomizeColor();

            particles.push_back(Particle(position, randSize, randSpeed, randDir, randColor));
        }
    }
    active = true;
}

void ParticleSpawner::CircularSpawn(int t_amount, float t_radius)
{
    for (int iteration = 0; iteration < t_amount; iteration++)
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            float randDir = RandomizeDir();
            Vector2 randPos = PosOnCircle(randDir, t_radius);
            int randSpeed = (rand() % 5) + 5;
            int randSize = (rand() % 7) + 7;
            Color randColor = RandomizeColor();

            particles.push_back(Particle(randPos, randSize, randSpeed, randDir, randColor));
        }
    }

    active = true;
}

bool ParticleSpawner::CheckIfParticalsActive()
{
    for (Particle& p : particles)
    {
        if (p.IsActive())
        {
            return false; // At least one particle  is active
        }
    }

    // No particles are active
    return true;
}

void ParticleSpawner::Update()
{
    if (CheckIfParticalsActive())
    {
        particles.clear();
        active = false;
    }

    if (active && !paused)
    {
        for (Particle& p : particles)
        {
            if (p.IsActive())
            {
                p.Move();
            }
        }
    }
    else if (paused)
    {
        printf("Particles are paused");
    }
}

void ParticleSpawner::Draw()
{
    for (Particle& p : particles)
    {
        if (p.IsActive())
        {
            p.Draw();
        }
    }
}

Vector2 ParticleSpawner::PosOnCircle(float t_angle, float t_radius)
{
    Vector2 randPos = { 0.0f, 0.0f };
    float randAngle = rand() % 360;
    t_angle = t_angle * DEG2RAD;

    randPos.x = position.x + t_radius * cos(t_angle);
    randPos.y = position.y + t_radius * sin(t_angle);


    return randPos;
}

float ParticleSpawner::RandomizeDir()
{
    // Randomize direction
    float result = 0.0f;
    float randLeewat = rand() % angleLeeway;
    if (rand() % 2 == 0)
    {
        result = dirAngle + randLeewat;
    }
    else
    {
        result = dirAngle - randLeewat;
    }

    return result;
}

Color ParticleSpawner::RandomizeColor()
{
    return colors[rand() % colors.size()];;
}