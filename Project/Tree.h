#pragma once
#include "Node.h"
#include <memory>

class Tree
{
public:
	Tree();
	void BuildTree(Board t_start, Team t_current, bool t_rotate);
	void ResetTree();
	void IncrementGameState(int t_playerMove);

	// Minimax
	int GetMiniMaxMove(int t_depth, Team t_team);
	int MiniMax(std::shared_ptr<Node> t_node, int t_depth, bool t_max, Team t_team);

	int GetMonteCarloMove(int t_depth);

private:
	Node startNode;
	std::shared_ptr<Node> currentNode;
	int depth;
};

