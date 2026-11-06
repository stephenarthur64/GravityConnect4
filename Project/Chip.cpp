#include "Chip.h"

float Chip::radius = 0.0f;

Chip::Chip() : team(Team::None), downDirection({0.0f, 0.0f}), position({0.0f, 0.0f})
{
}

void Chip::Init(Vector2 t_down, Team t_t)
{
	downDirection = t_down;
	team = t_t;
}

void Chip::Update()
{
}

void Chip::Draw()
{
	if (team == Team::Red)
	{
		DrawCircleV(position, radius, RED);
	}
	else if (team == Team::Yellow)
	{
		DrawCircleV(position, radius, YELLOW);
	}
	else
	{
		DrawCircleV(position, radius, RAYWHITE);
	}
}
