#include "Tree.h"
#include <algorithm>

Tree::Tree() : depth(0)
{
}

void Tree::BuildTree(Board t_start, Team t_current, bool t_rotate)
{
	ResetTree();

	Team previousPlayer = Team::None;
	if (t_current == Team::Red)
		previousPlayer = Team::Yellow;
	else if (t_current == Team::Yellow)
		previousPlayer = Team::Red;

	startNode.SetBoard(t_start, previousPlayer, 0);
	startNode.SetRotation(t_rotate);
	startNode.GenerateChildren();
	currentNode = std::make_shared<Node>(startNode);
}

void Tree::ResetTree()
{
	startNode.ClearChildren();
}

void Tree::IncrementGameState(int t_playerMove)
{
	std::shared_ptr<Node> nextMove = currentNode->FindChildByMove(t_playerMove);
	if (nextMove != nullptr)
	{
		currentNode = nextMove;
	}
	else
	{
		if (currentNode->AddChild(t_playerMove))
		{
			currentNode = currentNode->FindChildByMove(t_playerMove);
		}
		else
		{
			std::cout << "add child failed";
			return;
		}

	}
}

int Tree::GetMiniMaxMove(int t_depth, Team t_team)
{
	int currentDepth = t_depth;
	int bestMove = -1;
	int bestScore = -9999999;

	if (!currentNode->HasChildren())
	{
		currentNode->GenerateChildren();
	}

	std::cout << "Started search for best move" << std::endl;

	for (const std::shared_ptr<Node>& child : currentNode->GetChildren())
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

int Tree::GetMonteCarloMove(int t_depth)
{
	int move = 0;

	int currentDepth = 0;

	while (currentDepth < t_depth)
	{
		currentNode->CalculateAllUTC();
		currentNode->SortChildrenByUCT();

		currentNode->visit();
		currentNode->GetFirstChild()->ProcessNodeMonteCarlo();

		currentDepth++;
	}

	currentNode->CalculateAllUTC();
	currentNode->SortChildrenByUCT();
	move = currentNode->GetFirstChild()->GetMove();
	std::cout << "Move picked: " << move << "\n";

	return move;
}
