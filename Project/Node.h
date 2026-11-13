#pragma once
#include <memory>
#include <vector>
#include "Board.h"

class Node
{
public:
	Node();
	void SetBoard(Board t_board, Team t_team);
	void GenerateChildren();
	void SetHeuristic(float t_h) { heuristic = t_h; }
	void ClearChildren() { children.clear(); }

private:
	std::vector<std::shared_ptr<Node>> children;

	Board board;
	Team currentPlayer = Team::None;
	float heuristic = 0.0f;
};

