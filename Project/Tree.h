#pragma once
#include "Node.h"
#include <memory>

class Tree
{
public:
	Tree();
	void BuildTree(int t_depth, Board t_start, Team t_current);
	void ResetTree();
	void IncrementGameState(int t_playerMove);

	// Minimax
	int GetMiniMaxMove(Team t_team);
	int MiniMax(std::shared_ptr<Node> t_node, int t_depth, bool t_max, Team t_team);

	int GetMonteCarloMove();

private:
	Node startNode;
	std::shared_ptr<Node> currentNode;
	int depth;
};

