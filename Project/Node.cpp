#include "Node.h"

Node::Node()
{
}

void Node::SetBoard(Board t_board, Team t_team)
{
	board = t_board;
	currentPlayer = t_team;
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

		child->SetBoard(board, nextTeam);
		if (child->board.PlaceChip(i, nextTeam))
		{
			children.push_back(child);
		}
	}
}

