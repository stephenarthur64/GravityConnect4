#pragma once
#include <raylib.h>
#include <raymath.h>

enum class Team {
	None = -1,
	Red,
	Yellow
};

class Chip
{
public:
	Chip();
	void Init(Vector2 t_down, Team t_t = Team::None);
	void Update();
	void Draw();
	void SetDownDirection(Vector2 t_down) { downDirection = t_down; }

	void SetPos(Vector2 t_pos) { position = t_pos; }
	static void SetRadius(float t_r) { radius = t_r; }
	static float GetRadius() { return radius; }

	Team GetTeam() const { return team; }
	void SetTeam(Team t_t) { team = t_t; }

private:
	Texture2D texture;

	Vector2 position;
	Vector2 downDirection;
	static float radius;
	Team team;
};

