#include "player.hpp"
#include <vector>

#define MINIMUMHEURISTIC (-1*150*12)*65
#define MAXIMUMHEURISTIC 65*4*150*16*10
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

     this -> board = new Board();
     this -> playerside = side;
     if (side == WHITE)
     {
		 this -> otherside = BLACK;
	 }
	 else
	 {
		 this -> otherside = WHITE;
	 }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete this->board;
}

void Player::setBoard(Board *boardset) {
	delete board;
	board = boardset->copy();
}
 
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // executes the opponenets move on our board
    if (opponentsMove != nullptr)
    {
		board->doMove(opponentsMove, otherside);
	}
	// fills a vector with all valid moves our player can now make
	std::vector<Move *> validmoves;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 ; j++)
		{
			Move *m = new Move(i, j);
			if( board->checkMove(m, playerside))
			{
				validmoves.push_back(m);
			}
			else
				delete m;
		}
	}
	Move *nextmove = nullptr;
	int currentminimax = MINIMUMHEURISTIC;
	int temp;
	unsigned int index = 0;
	// if there is no valid move, the player doesn't move at all. 	
	if (validmoves.size() == 0)
	{
		return nullptr;
	}
	if (validmoves.size() == 1)
	{
		board -> doMove(validmoves[0], playerside);
		return validmoves[0];
	}
	// if there is a valid move, calls upon minimax function to find 
	// the greatest gauranteed heuristic value for our player
	else
	{
		for (unsigned int i = 0; i < validmoves.size(); i++)
		{
			temp = alphabeta(board, validmoves[i], 4, MINIMUMHEURISTIC, MAXIMUMHEURISTIC);
			if (temp >= currentminimax)
			{
				currentminimax = temp;
				nextmove = validmoves[i];
				index = i;
			}
		}
	}
		for (unsigned int i = 0; i < validmoves.size(); i++)
		{
			if (index != i)
			{
				delete validmoves[i];
			}
		}
	// player makes the move on its board and returns it
	board -> doMove(nextmove, playerside);
	return nextmove;
}

// Weights possible moves based on board position
// This function takes a move, a copy of the board, and a Side side,
// and makes the move on the board copy, leading to a specific position/
// configuration of the board and returns an integer representing the
// favorability of configuration for our player.
int Player::heuristic(Board *theboard, Move* move, Side side)
{
	Board *theboardcopy = theboard->copy();
	bool corner = false;
	int cornercount = 0;
	bool edge = false;
	int countedge = 0;
	bool adjacenttocorner = false;
	int adjacenttocornercount=0;
	
	if (move != nullptr)
	{
		theboardcopy->doMove(move, side);
	}
	int ours = theboardcopy->count(playerside);
	int theirs = theboardcopy->count(otherside);
	if (theboardcopy->isDone() && (ours >= theirs))
	{
		return MAXIMUMHEURISTIC;
	}
	if (theboardcopy->isDone() && (theirs > ours))
	{
		return MINIMUMHEURISTIC;
	}
	if (theboardcopy->get(playerside, 0, 0))
	{
		corner = true;
		cornercount++;
	}
	else if (!(theboardcopy->occupied(0, 0)))
	{
		if (theboardcopy->get(playerside, 0, 1))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 1, 0))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 1, 1))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
	}
	if (theboardcopy->get(playerside, 0, 7))
	{
		corner = true;
		cornercount++;
	}
	else if (!(theboardcopy->occupied(0, 7)))
	{
		if (theboardcopy->get(playerside, 7, 6))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 6, 7))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 6, 6))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
	}
	if (theboardcopy->get(playerside, 7, 0))
	{
		corner = true;
		cornercount++;
	}
	else if (!(theboardcopy->occupied(7, 0)))
	{
		if (theboardcopy->get(playerside, 6, 0))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}	
		if (theboardcopy->get(playerside, 7, 1))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 6, 1))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
	}
	if (theboardcopy->get(playerside, 7, 7))
	{
		corner = true;
		cornercount++;
	}
	else if (!(theboardcopy->occupied(7, 7)))
	{
		if (theboardcopy->get(playerside, 0, 6))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}	
		if (theboardcopy->get(playerside, 1, 7))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
		if (theboardcopy->get(playerside, 1, 6))
		{
			adjacenttocorner = true;
			adjacenttocornercount++;
		}
	}	
	if(theboardcopy->get(playerside, 0, 2))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 0, 3))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 0, 4))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 0, 5))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 7, 2))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 7, 3))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 7, 4))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 7, 5))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 2, 0))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 3, 0))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 4, 0))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 5, 0))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 2, 7))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 3, 7))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 4, 7))
	{
		edge = true;
		countedge++;
	}
	if(theboardcopy->get(playerside, 5, 7))
	{
		edge = true;
		countedge++;
	}
	delete theboardcopy;
	if (corner)
	{
		ours *= 150*cornercount;
	}
	if (adjacenttocorner)
	{
		theirs *= (150)*adjacenttocornercount;
	}
	if (edge)
	{
		ours *= (10)*countedge;
	}
	int temp = ours - theirs;
	return temp;
}	



int Player::alphabeta(Board *aboard, Move *move, int depth, int min, int max)
{
	Board *theboard = aboard->copy();
	if (depth == 0)
	{
		int temp = heuristic(theboard, move, playerside);
		delete theboard;
		return temp;
	}
	 
	std::vector<Move *> validnextmoves;
	// minimizing node:
	if (depth% 2 == 0)
	{	
		if (move != nullptr)
		{
			theboard-> doMove(move, playerside);
		}
		int v = max;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8 ; j++)
			{
				Move *m = new Move(i, j);
				if(theboard->checkMove(m, otherside))
				{
					validnextmoves.push_back(m);
				}
				else
				{
					delete m;
				}
			}
		}
		if (validnextmoves.size() == 0)
		{
			int temp = alphabeta(theboard, nullptr, depth-1, min, v);
			if (temp < v)
			{
				v = temp;
			}
			if (v < min)
			{
				delete theboard;
				return min;
			}
		}
		for (unsigned int i = 0; i<validnextmoves.size(); i++)
		{
			int temp = alphabeta(theboard, validnextmoves[i], depth-1, min, v);
			if (temp < v)
			{
				v = temp;
			}
			if (v < min)
			{
				delete theboard;
				for (unsigned int k = 0; k<validnextmoves.size(); k++)
				{
					delete validnextmoves[k];
				}
				return min;
			}
		}
		delete theboard;
		for (unsigned int i = 0; i<validnextmoves.size(); i++)
		{
			delete validnextmoves[i];
		}
		return v;
	}
	
	
	//maximizing node
	else
	{
		if (move != nullptr)
		{
			theboard->doMove(move, otherside);
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8 ; j++)
			{
				Move *m = new Move(i, j);
				if(theboard->checkMove(m, playerside))
				{
					validnextmoves.push_back(m);
				}
				else
					delete m;
			}
		}
		int v = min;
		if (validnextmoves.size() == 0)
		{
			
			int temp = alphabeta(theboard, nullptr,  depth-1, v, max);
			if (temp > v)
				v = temp;
			if (v > max)
			{
				delete theboard;
				return max;
			}
		}
		for (unsigned int i = 0; i < validnextmoves.size(); i++)
		{
			int temp = alphabeta(theboard, validnextmoves[i],  depth-1, v, max);
			if (temp > v)
				v = temp;
			if (v > max)
			{
				delete theboard;
				for (unsigned int k = 0; k<validnextmoves.size(); k++)
				{
					delete validnextmoves[k];
				}
				return max;
			}
		}
		delete theboard;
		for (unsigned int i = 0; i<validnextmoves.size(); i++)
		{
			delete validnextmoves[i];
		}
		
		return v;
	}

}

