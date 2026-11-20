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
	if (t_turn == 0)
	{
		rootTeam = t_team;
	}
	currentTurn = t_turn;
}

void Node::GenerateChildren()
{
	for (int i = 0; i < 7; i++)
	{
		AddChild(i);
	}
}

bool Node::AddChild(int t_move)
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
		return false;
	}

	std::shared_ptr<Node> child = std::make_shared<Node>();

	child->SetBoard(board, nextTeam, currentTurn + 1);
	child->SetRotation(rotating);
	if (child->board.PlaceChip(t_move, nextTeam))
	{
		if (child->currentTurn % 4 == 0 && rotating)
		{
			child->board.Rotate();
		}
		child->parent = this;
		child->moveUsed = t_move;
		child->rootTeam = rootTeam;
		children.push_back(child);
		return true;
	}
	return false;
}

std::shared_ptr<Node> Node::FindChildByMove(int t_move)
{
	if (children.size() == 0)
	{
		return nullptr;
	}

	for (std::shared_ptr<Node> n : children)
	{
		if (n->moveUsed == t_move)
		{
			return n;
		}
	}

	return nullptr;
}

void Node::CalcHeuristic(Team t_team)
{
	heuristic = board.Evaluate(t_team);
}

void Node::CalculateUTC()
{
	float exploitation = 0.0f;
	float exploration = 0.0f;

	if (visits > 0 && parent->visits > 0)
	{
		exploitation = (double)wins / visits;
		exploration = sqrt((log((double)parent->visits) / visits));
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
	if (children.size() == 0) { return; }
	std::sort(children.begin(), children.end(),
		[](std::shared_ptr<Node> const Node1, std::shared_ptr<Node> const Node2)
		{
			return Node1->UTC > Node2->UTC;
		});
}

void Node::ProcessNodeMonteCarlo()
{
	int simulationResult = SimulationMonteCarlo(rootTeam); // 0 for loss / draw, 1 for win
	visits++;
	wins += simulationResult;
}

int Node::SimulationMonteCarlo(Team t_originalTeam)
{
	int result = 0;
	int nextMove = 0;
	bool childMade = false;
	int allMoves = 0;

	visits++;

	//board.PlaceChip(moveUsed, currentPlayer);

	Team winState = board.WholeBoardCheck();

	if (winState == Team::None) // Not terminal node
	{
		FindAllPossibleMoves();

		for (int i = 0; i < 7; i++) // Check if there are any possible moves
		{
			if (possibleMoves[i] == 1)
			{
				allMoves++;
			}
		}

		if (allMoves == 0)
		{
			return 0; // Draw
		}

		while (!childMade)
		{
			nextMove = rand() % 7;
			std::shared_ptr<Node> nextChild = FindChildByMove(nextMove);
			
			if (nextChild != nullptr) // if child node already exists
			{
				result = nextChild->SimulationMonteCarlo(t_originalTeam);
				childMade = true;
			}
			else if (possibleMoves[nextMove] == 1)
			{
				childMade = AddChild(nextMove);
				result = children.back()->SimulationMonteCarlo(t_originalTeam);
			}
		}
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
	}

	//CalculateUTC();
	return result;

}

void Node::FindAllPossibleMoves()
{
	Board dummy = board;

	for (int i = 0; i < 7; i++)
	{
		if (dummy.PlaceChip(i, currentPlayer))
		{
			possibleMoves[i] = 1;
		}
		else
		{
			possibleMoves[i] = 0;
		}
		dummy = board;
	}
}

