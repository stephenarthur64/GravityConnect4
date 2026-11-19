#pragma once
#include <memory>
#include <vector>
#include "Board.h"

class Node
{
public:
	Node();
	void SetBoard(Board t_board, Team t_team, int t_turn);
	void GenerateChildren();
	void ClearChildren() { children.clear(); }

	bool HasChildren() const { return !children.empty(); }
	const std::vector<std::shared_ptr<Node>>& GetChildren() const { return children; }

	// MiniMax
	void CalcHeuristic(Team t_team);
	int GetHeuristic() const { return heuristic; }
	Team GetWinner() { return board.WholeBoardCheck(); }

	// Monte-Carlo
	void CalculateUTC();
	void CalculateAllUTC();
	void SortChildrenByUCT();
	void ProcessNodeMonteCarlo();
	int SimulationMonteCarlo(Team t_originalTeam);
	void visit() { visits++; }

	std::shared_ptr<Node> GetFirstChild() { return children.front(); }
	int GetMove() const { return moveUsed; }

private:
	int moveUsed = 0;
	int currentTurn = 0;
	std::vector<std::shared_ptr<Node>> children;
	Node* parent = nullptr;
	Board board;
	Team currentPlayer = Team::None;
	float heuristic = 0.0f;
	int wins = 0;
	int visits = 0;
	float UTC = INFINITY;
};

