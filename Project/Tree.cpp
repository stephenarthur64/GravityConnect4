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
	currentNode = std::make_shared<Node>(startNode);
}

void Tree::ResetTree()
{
	startNode.ClearChildren();
}

int Tree::GetMiniMaxMove()
{
	return 1;
}

int Tree::GetMonteCarloMove(int t_lastPlayerMove)
{
	int move = 0;

	int currentDepth = 0;
	std::shared_ptr<Node> nextMove = currentNode->FindChildByMove(t_lastPlayerMove);
	if (nextMove != nullptr)
	{
		currentNode = nextMove;
	}
	else
	{
		currentNode->AddChild(t_lastPlayerMove);
		currentNode = currentNode->FindChildByMove(t_lastPlayerMove);
	}

	while (currentDepth < 1000)
	{
		currentNode->SortChildrenByUCT();

		currentNode->visit();
		currentNode->GetFirstChild()->ProcessNodeMonteCarlo();

		currentDepth++;
	}

	currentNode->SortChildrenByUCT();
	move = currentNode->GetFirstChild()->GetMove();
	currentNode = currentNode->GetFirstChild();
	std::cout << "Move picked: " << move << "\n";

	return move;
}
