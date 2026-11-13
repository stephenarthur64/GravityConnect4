#include "Tree.h"
#include <algorithm>

Tree::Tree() : depth(0)
{
}

void Tree::BuildTree(int t_depth, Board t_start, Team t_current)
{
	depth = t_depth;
	startNode.SetBoard(t_start, t_current, 0);
	startNode.GenerateChildren();
}

void Tree::ResetTree()
{
	startNode.ClearChildren();
}

int Tree::GetMiniMaxMove()
{
	return 1;
}

int Tree::GetMonteCarloMove()
{
	int move = 0;

	int depth = 0;

	while (depth < 100)
	{
		startNode.SortChildrenByUCT();

		startNode.visit();
		startNode.GetFirstChild()->ProcessNodeMonteCarlo();

		depth++;
	}

	startNode.SortChildrenByUCT();
	move = startNode.GetFirstChild()->GetMove();
	std::cout << "Move picked: " << move << "\n";

	return move;
}
