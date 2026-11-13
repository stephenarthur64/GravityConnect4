#include "Tree.h"

Tree::Tree() : depth(0)
{
}

void Tree::BuildTree(int t_depth, Board t_start, Team t_current)
{
	depth = t_depth;
	startNode.SetBoard(t_start, t_current);
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
	return 6;
}
