#pragma once
#include "Node.h"

class Tree
{
public:
	Tree();
	void BuildTree(int t_depth, Board t_start, Team t_current);
	void ResetTree();
	int GetMiniMaxMove();
	int GetMonteCarloMove(int t_lastPlayerMove);

private:
	Node startNode;
	std::shared_ptr<Node> currentNode;
	int depth;
};

