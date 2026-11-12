#include "Chip.h"

float Chip::radius = 0.0f;

Chip::Chip() : team(Team::None), downDirection({0.0f, 0.0f}), position({0.0f, 0.0f})
{
}

void Chip::Init(Vector2 t_down, Team t_t)
{
	texture = LoadTexture("Resources/Chip.png");

	downDirection = t_down;
	team = t_t;
}

void Chip::Update()
{
}

void Chip::Draw()
{
	Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle dest = { position.x, position.y, radius * 2.0f, radius * 2.0f };
	Vector2 origin = { radius, radius };
	if (team == Team::Red)
	{
		//DrawCircleV(position, radius, RED);
		DrawTexturePro(texture, source, dest, origin, 0.0f, RED);
	}
	else if (team == Team::Yellow)
	{
		//DrawCircleV(position, radius, YELLOW);
		DrawTexturePro(texture, source, dest, origin, 0.0f, YELLOW);
	}
}
