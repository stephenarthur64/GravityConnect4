#include "Node.h"
#include <algorithm>

static float explorationConstant = 1.41f;

Node::Node()
{
}

void Node::SetBoard(Board t_board, Team t_team, int t_turn)
{
	board = t_board;
	currentPlayer = t_team;
	currentTurn = t_turn;

	if (currentTurn > 0 && currentTurn % 4 == 0)
	{
		board.Rotate();
	}
}

void Node::GenerateChildren()
{
	Team nextTeam = Team::None;

	if (currentPlayer == Team::Red)
	{
		nextTeam = Team::Yellow;
	}
	else if (currentPlayer == Team::Yellow)
	{
		nextTeam = Team::Red;
	}
	else
	{
		std::cout << "ERROR - No team assigned\n";
		return;
	}

	for (int i = 0; i < 7; i++)
	{
		std::shared_ptr<Node> child = std::make_shared<Node>();

		child->SetBoard(board, nextTeam, currentTurn + 1);
		if (child->board.PlaceChip(i, nextTeam))
		{
			child->parent = this;
			child->moveUsed = i;
			children.push_back(child);
		}
	}
}

void Node::CalculateUTC()
{
	float exploitation = 0.0f;
	float exploration = 0.0f;

	if (visits > 0 && parent->visits > 0)
	{
		exploitation = wins / visits;
		exploration = sqrt((log(parent->visits) / visits));
	}

	UTC = exploitation + (explorationConstant * exploration);
}

void Node::CalculateAllUTC()
{
	CalculateUTC();

	for (std::shared_ptr<Node> n : children)
	{
		n->CalculateUTC();
	}
}

void Node::SortChildrenByUCT()
{
	std::sort(children.begin(), children.end(),
		[](std::shared_ptr<Node> const Node1, std::shared_ptr<Node> const Node2)
		{
			return Node1->UTC > Node2->UTC;
		});
}

void Node::ProcessNodeMonteCarlo()
{
	if (children.size() == 0)
	{
		GenerateChildren();
	}

	SortChildrenByUCT();

	visits++;
	int simulationResult = children.front()->SimulationMonteCarlo(parent->currentPlayer); // 0 for loss / draw, 1 for win
	wins += simulationResult;
	CalculateUTC();
}

int Node::SimulationMonteCarlo(Team t_originalTeam)
{
	int result = 0;

	visits++;

	board.PlaceChip(moveUsed, currentPlayer);

	Team winState = board.WholeBoardCheck();

	if (winState == Team::None) // Not terminal node
	{
		if (children.size() == 0)
		{
			GenerateChildren();
		}

		int nextMove = rand() % children.size();
		result = children.at(nextMove)->SimulationMonteCarlo(t_originalTeam);
	}
	else if (winState == t_originalTeam) // Win
	{
		result = 1;
	}
	else // Lose
	{
		result = 0;
	}

	// Increments for terminal node and back propagation
	if (result == 1)
	{
		wins++;
		CalculateUTC();
	}

	return result;

}

