#include "Tree.h"
#include <algorithm>

Tree::Tree() : depth(0)
{
}

void Tree::BuildTree(int t_depth, Board t_start, Team t_current, int t_currentTurn)
{
	ResetTree();
	depth = t_depth;

	Team previousPlayer = Team::None;
	if (t_current == Team::Red)
		previousPlayer = Team::Yellow;
	else if (t_current == Team::Yellow)
		previousPlayer = Team::Red;

	startNode.SetBoard(t_start, previousPlayer, t_currentTurn);
	startNode.GenerateChildren();
	currentNode = std::make_shared<Node>(startNode);
}

void Tree::ResetTree()
{
	startNode.ClearChildren();
}

int Tree::GetMiniMaxMove(Team t_team)
{
	int currentDepth = 5;
	int bestMove = -1;
	int bestScore = -9999999;

	std::cout << "Started search for best move" << std::endl;

	for (const std::shared_ptr<Node>& child : startNode.GetChildren())
	{
		int score = MiniMax(child, currentDepth - 1, false, t_team);

		if (score > bestScore)
		{
			bestScore = score;
			bestMove = child->GetMove();
		}
	}

	std::cout << "Best Move is: " << bestMove << std::endl;

	return bestMove;
}

int Tree::MiniMax(std::shared_ptr<Node> t_node, int t_depth, bool t_max, Team t_team)
{
	t_node->CalcHeuristic(t_team);
	int heuristic = t_node->GetHeuristic();

	// Stop when win found
	if (t_node->GetWinner() != Team::None)
		return heuristic;

	// Reached max depth
	if (t_depth == 0)
		return heuristic;

	// Create children if not made
	if (!t_node->HasChildren())
	{
		t_node->GenerateChildren();
	}

	const std::vector<std::shared_ptr<Node>>& children = t_node->GetChildren();

	// No valid moves
	if (children.empty())
		return 0;

	if (t_max)
	{
		int bestScore = -9999999;

		for (const std::shared_ptr<Node>& child : children)
		{
			int score = MiniMax(child, t_depth - 1, false, t_team);
			bestScore = std::max(bestScore, score);
		}

		return bestScore;
	}
	else
	{
		int worstScore = 9999999;

		for (const std::shared_ptr<Node>& child : children)
		{
			int score = MiniMax(child, t_depth - 1, true, t_team);
			worstScore = std::min(worstScore, score);
		}

		return worstScore;
	}
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
