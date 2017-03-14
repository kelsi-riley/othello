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
		std::cerr<< "w: " << opponentsMove -> getX() << "," << opponentsMove->getY() << std::endl;
	}
	else 
		std::cerr<<"W did not move"<< std::endl;
	// fills a vector with all valid moves our player can now make
	std::vector<Move *> validmoves;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 ; j++)
		{
			Move *m = new Move(i, j);
			if( board->checkMove(m, playerside))
			{
				std::cerr << "valid: "<< m->getX() << "," << m->getY() << std::endl;
				validmoves.push_back(m);
			}
			else
				delete m;
		}
	}
	Move *nextmove = nullptr;
	int currentminimax = (-50*12)*65;
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
		std::cerr<<"size = "<<validmoves.size()<<std::endl;
		for (unsigned int i = 0; i < validmoves.size(); i++)
		{
			std::cerr<<"i = " << i << std::endl;
			temp = alphabeta(board, validmoves[i], 2, (-50*12)*65, 65*400);
			//std::cerr << temp << std::endl;
			if (temp >= currentminimax)
			{
				currentminimax = temp;
				nextmove = validmoves[i];
				index = i;
			}
		}
	}
	std::cerr<<"i = " << index << " deleting"<<std::endl;
		for (unsigned int i = 0; i < validmoves.size(); i++)
		{
			std::cerr<<validmoves.size()<<" " << i << std::endl;
			if (index != i)
			{
				std::cerr<<"rip"<<std::endl;
				delete validmoves[i];
			}
		}
	// player makes the move on its board and returns it
	std::cerr<< "b: " << nextmove -> getX() << "," << nextmove->getY() << std::endl;
	board -> doMove(nextmove, playerside);
	return nextmove;
}

// Weights possible moves based on board position
// This function takes a vector of steps leading to a specific position/
// configuration of the board and returns an integer representing the
// favorability of configuration for our player.
int Player::heuristic(Board *theboard, Move* move, Side side)
{
	Board *theboardcopy = theboard->copy();
	bool corner = false;
	int cornercount = 0;
	bool edge = false;
	bool adjacenttocorner = false;
	int adjacenttocornercount=0;
	
	// this works because moves will only contain one move-> we should change
	// this stylistically but for now it fine.
	if (move != nullptr)
	{
		theboardcopy->doMove(move, side);
	}
	if (theboardcopy->get(playerside, 0, 0))
	{
		corner = true;
		cornercount++;
	}
	else
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
	else
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
	else
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
	else
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
				
			//if (side == playerside)
			//{
				//if (move->getX() == 0)
				//{
					//if (move->getY()==0||move->getY()==7)
					//{
						//corner = true;
					//}
					//else if (move->getY()==1||move->getY()==6)
					//{
						//adjacenttocorner = true;
					//}
					//else
					//{
						//edge = true;
					//}
				//}
				//else if (move->getX() == 7)
				//{
					//if (move->getY()==0 || move->getY()==7)
					//{
						//corner = true;
					//}
					//else if (move->getY()==1 || move->getY()==6)
					//{
						//adjacenttocorner = true;
					//}	
					//else
					//{
						//edge = true;
					//}
				//}
				//else if (move->getX() == 1)
				//{
					//if (move->getY()==0 || move->getY()==7)
					//{
						//adjacenttocorner = true;
					//}
				//}	
				//else if (move->getX() == 6)
				//{
					//if (move->getY()==0 || move->getY()==7)
					//{
						//adjacenttocorner = true;
					//}
				//}
				//else if (move->getY() == 0)
				//{
					//edge = true;
				//}
				//else if (move->getY() == 7)
				//{
					//edge = true;
				//}
			//}
		//}
	int temp = 64 + theboardcopy->count(playerside) - theboardcopy->count(otherside);
	delete theboardcopy;
	if (corner)
	{
		temp *= 100*cornercount;
	}
	else if (adjacenttocorner)
	{
		temp *= (-50)*adjacenttocornercount;
	}
	else if (edge)
	{
		temp *= (5);
	}
	//std::cerr<<temp<<std::endl;
	return temp;
}	


//I started writing the skeleton code of this function, it doesn't work yet
int Player::alphabeta(Board *aboard, Move *move, int depth, int min, int max)
{
	Board *theboard = aboard->copy();
	if (depth == 0)
	{
		//if (move != nullptr)
		//{
			//theboard -> doMove(move, playerside);
		//}
		//int score = theboard -> count(playerside) - theboard -> count(otherside);
		//std::cerr<<"score: " <<score<<std::endl;
		//theboard->doMove(move, playerside);
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
			std::cerr<<"testing w "<< validnextmoves[i] -> getX()<< "," << validnextmoves[i] -> getY() << std::endl;
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
			std::cerr << move->getX() << move->getY() << ": ";
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8 ; j++)
			{
				std::cerr << i << j;
				Move *m = new Move(i, j);
				if(theboard->checkMove(m, playerside))
				{
					validnextmoves.push_back(m);
					std::cerr << "X ";
				}
				else
					delete m;
					std::cerr << "  ";
			}
			std::cerr << "| ";
		}
		std::cerr << std::endl;
		int v = min;
		if (validnextmoves.size() == 0)
		{
			
			int temp = alphabeta(theboard, nullptr,  depth-1, v, max);
			if (temp > v)
				v = temp;
			if (v > max)
			{
				delete theboard;
				std::cerr<<"b: " << max << endl;
				return max;
			}
		}
		for (unsigned int i = 0; i < validnextmoves.size(); i++)
		{
			std::cerr<<"       testing b "<< validnextmoves[i] -> getX()<< "," << validnextmoves[i] -> getY() << std::endl;
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
				std::cerr<<"b: " << max << endl;
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



//// Much of the commented code is for multiple layers of minimax, unimplemented
//// This function takes a move that our player is considering and considers
//// the favorability of the board after some depth of future moves.
//int Player::minimax(Move *move)
//{
	//Board *boardclone = board -> copy();
	//boardclone -> doMove(move, playerside);
	//// builds a vector of all valid moves our opponent can make after
	//// we make our move "move"
	//std::vector<Move *> validopponentmoves;
	//std::vector<Move *> ourmoves;
	//ourmoves.push_back(move);
	//int i;
	//int iterations = 0;
	
	//int worst = 3*65;
	//for (i = 0; i < 8; i++)
	//{
		//for (int j = 0; j < 8 ; j++)
		//{
			//Move *m = new Move(i, j);
			//if(boardclone->checkMove(m, otherside))
			//{
				//validopponentmoves.push_back(m);
			//}
			//else
			//delete m;
		//}
	//} 	
	//delete boardclone;
	//// if our opponent has any valid moves, then we find the most unfavorable
	//// possible outcome
	//if (validopponentmoves.size() != 0)
	//{
		//for (unsigned int i = 0; i < validopponentmoves.size(); i++)
		//{
			//ourmoves[1] = validopponentmoves[i];
			//int temp = heuristic(board, ourmoves, playerside);
			//if (temp < worst)
			//{
				//worst = temp;
			//}
		//}
	//}
	//else
	//{
		//std::vector<Move*> ourmove;
		//ourmove.push_back(move);
		//int temp = heuristic(board, ourmove, playerside);
		//return temp;
	//}
////	delete boardclone;
	//return worst;	
//}
