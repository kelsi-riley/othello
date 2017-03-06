#include "player.hpp"
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
    if (opponentsMove != nullptr)
    {
		board->doMove(opponentsMove, otherside);
	}
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
	Move *nextmove;
	int currentminimax = (-65)*3;
	int temp; 	
	if (validmoves.size() ==0)
	{
		return nullptr;
	}
	else
	{
		for (unsigned int i = 0; i < validmoves.size(); i++)
		{
			temp = minimax(validmoves[i]);
			if (temp > currentminimax)
			{
				currentminimax = temp;
				nextmove = validmoves[i];
			}
		}
	}
	board -> doMove(nextmove, playerside);
	return nextmove;
}

// I decided to make this helper function... It makes the code cleaner but
// I'm 100% sure this is not efficent. This probably isn't a problem for this
// week but we should keep it in mind for next week
int Player::heiuristic(Board *theboard, std::vector<Move*> moves, Side side)
{
	Board *theboardcopy = theboard->copy();
	bool corner = false;
	bool adjacenttocorner = false;
	for (unsigned int i = 0; i < moves.size(); i++)
	{
		if (i%2 == 0)
		{
			theboardcopy->doMove(moves[i], side);
			if (side == playerside)
			{
				if (moves[i]->getX() == 0)
				{
					if (moves[i]->getY()==0||moves[i]->getY()==7)
					{
						corner = true;
					}
					else if (moves[i]->getY()==1||moves[i]->getY()==6)
					{
						adjacenttocorner = true;
					}
				}
				else if (moves[i]->getX() == 7)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						corner = true;
					}
					else if (moves[i]->getY()==1 || moves[i]->getY()==6)
					{
						adjacenttocorner = true;
					}	
				}
				else if (moves[i]->getX() == 1)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						adjacenttocorner = true;
					}
				}	
				else if (moves[i]->getX() == 6)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						adjacenttocorner = true;
					}
				}
			}
		}
		else
		{
			if (side == playerside)
			{
				theboardcopy->doMove(moves[i], otherside);
			}
			else
			{
				theboardcopy->doMove(moves[i], playerside);
				if (moves[i]->getX() == 0)
				{
					if (moves[i]->getY()==0||moves[i]->getY()==7)
					{
						corner = true;
					}
					else if (moves[i]->getY()==1||moves[i]->getY()==6)
					{
						adjacenttocorner = true;
					}
				}
				else if (moves[i]->getX() == 7)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						corner = true;
					}
					else if (moves[i]->getY()==1 || moves[i]->getY()==6)
					{
						adjacenttocorner = true;
					}	
				}
				else if (moves[i]->getX() == 1)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						adjacenttocorner = true;
					}
				}	
				else if (moves[i]->getX() == 6)
				{
					if (moves[i]->getY()==0 || moves[i]->getY()==7)
					{
						adjacenttocorner = true;
					}
				}
			}
		}
	}
	int temp = theboardcopy->count(playerside) - theboardcopy->count(otherside);
	delete theboardcopy;
	if (corner)
	{
		temp *= 3;
	}
	if (adjacenttocorner)
	{
		temp *= (-3);
	}
	return temp;
}	

// sorry for all of the commented out code in this one... I'm the worst
// that would be for if we wanted to implement another layer of minimax
// but then I realized that can wait... I didnt want to just delete it
// all though so here we are.. D: 
int Player::minimax(Move *move)
{
	Board *boardclone = board -> copy();
	boardclone -> doMove(move, playerside);
	// builds a vector of all valid moves our opponent can make after
	// we make our move "move"
	std::vector<Move *> validopponentmoves;
	std::vector<Move *> ourmoves;
	ourmoves.push_back(move);
	ourmoves.push_back(move);
	int i;
	int worst = 3*65;
	for (i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 ; j++)
		{
			Move *m = new Move(i, j);
			if(boardclone->checkMove(m, otherside))
			{
				validopponentmoves.push_back(m);
			}
			else
			delete m;
		}
	} 	
	delete boardclone;
	// if our opponent has any valid moves, then we find the most unfavorable
	// possible outcome
	if (validopponentmoves.size() != 0)
	{
		for (unsigned int i = 0; i < validopponentmoves.size(); i++)
		{
			ourmoves[1] = validopponentmoves[i];
			int temp = heiuristic(board, ourmoves, playerside);
			if (temp < worst)
			{
				worst = temp;
			}
		}
			//Board *boardcopy = boardclone->copy();
			//boardcopy->doMove(validopponentmoves[i], otherside);
			//int ours = boardcopy->count(playerside);
			//int theirs = boardcopy->count(otherside);
			//int temp = ours-theirs;
			//if (temp < worst)
			//{
				//worst = temp;
			//}
			//std::vector<Move *> validmoves;
			//for (int k = 0; k < 8; k++)
			//{
				//for (int j = 0; j < 8 ; j++)
				//{
					//Move *m = new Move(k, j);
					//if(boardcopy->checkMove(m, playerside))
					//{
						//validmoves.push_back(m);
					//}
					//else
					//delete m;
				//}
			//}
			//for (unsigned int k = 0; k <validmoves.size(); k++)
			//{
				//Board *boardcopytwo = boardcopy->copy();
				//boardcopytwo->doMove(validmoves[k], playerside);
				//int ours = boardcopytwo->count(playerside);
				//int theirs = boardcopytwo->count(otherside);
				//int temp = ours-theirs;
				//if (validmoves[k]->getX() == 0)
				//{
					//if (validmoves[k]->getY()==0||validmoves[k]->getY()==7)
					//{
						//temp *= 3;
					//}
					//else if (validmoves[k]->getY()==1||validmoves[k]->getY()==6)
					//{
						//temp *= (-3);
					//}
				//}
				//else if (validmoves[k]->getX() == 7)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= 3;
					//}
					//else if (validmoves[k]->getY()==1 || validmoves[k]->getY()==6)
					//{
						//temp *= (-3);
					//}
				//}
				//else if (validmoves[k]->getX() == 1)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= (-3);
					//}	
				//}
				//else if (validmoves[k]->getX() == 6)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= (-3);
					//}
				//}
				//if (temp < worst)
				//{
					//worst = temp;	
				//}
				//delete boardcopytwo;
			//}
	}
	else
	{
		std::vector<Move*> ourmove;
		ourmove.push_back(move);
		int temp = heiuristic(board, ourmove, playerside);
		return temp;
		//int ours = boardclone->count(playerside);
		//int theirs = boardclone->count(otherside);
		//worst = ours-theirs;
				//int temp = ours-theirs;
			//std::vector<Move *> validmoves;
			//for (int k = 0; k < 8; k++)
			//{
				//for (int j = 0; j < 8 ; j++)
				//{
					//Move *m = new Move(k, j);
					//if(boardclone->checkMove(m, playerside))
					//{
						//validmoves.push_back(m);
					//}
					//else
					//delete m;
				//}
			//}
			//for (unsigned int k = 0; k <validmoves.size(); k++)
			//{
				//Board *boardcopy = board->copy();
				//boardcopy->doMove(validmoves[k], playerside);
				//int ours = boardcopy->count(playerside);
				//int theirs = boardcopy->count(otherside);
				//int temp = ours-theirs;
				//if (validmoves[k]->getX() == 0)
				//{
					//if (validmoves[k]->getY()==0||validmoves[k]->getY()==7)
					//{
						//temp *= 3;
					//}
					//else if (validmoves[k]->getY()==1||validmoves[k]->getY()==6)
					//{
						//temp *= (-3);
					//}
				//}
				//else if (validmoves[k]->getX() == 7)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= 3;
					//}
					//else if (validmoves[k]->getY()==1 || validmoves[k]->getY()==6)
					//{
						//temp *= (-3);
					//}
				//}
				//else if (validmoves[k]->getX() == 1)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= (-3);
					//}	
				//}
				//else if (validmoves[k]->getX() == 6)
				//{
					//if (validmoves[k]->getY()==0 || validmoves[k]->getY()==7)
					//{
						//temp *= (-3);
					//}
				//}
				//if (temp < worst)
				//{
					//worst = temp;	
				//}
				//delete boardcopy;
			//}
	}
//	delete boardclone;
	return worst;	
}
