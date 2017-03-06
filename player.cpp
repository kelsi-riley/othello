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
     Board *board = new Board();
     Side playerside = side;
     if (side == WHITE)
     {
		 Side otherside = BLACK;
	 }
	 else
	 {
		 Side otherside = WHITE;
	 }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
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
		}
	}
	Move *nextmove;
	int currentminimax;
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
	return nextmove;
}

int Player::minimax(Move *move)
{
	std::vector<Move *> validopponentmoves;
	int i;
	int worst = 65;
	for (i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8 ; j++)
		{
			Move *m = new Move(i, j);
			if( board->checkMove(m, otherside))
			{
				validopponentmoves.push_back(m);
			}
		}
	} 	
	if (validopponentmoves.size() != 0)
	{
		for (unsigned int i = 0; i < validopponentmoves.size(); i++)
		{
			Board *boardcopy = board->copy();
			boardcopy->doMove(move, playerside);
			boardcopy->doMove(validopponentmoves[i], otherside);
			int ours = boardcopy->count(playerside);
			int theirs = boardcopy->count(otherside);
			if (ours-theirs < worst)
			{
			   worst = ours-theirs;	
			}
		}
	}
	else
	{
		Board *boardcopy = board->copy();
		boardcopy->doMove(move, playerside);	
		int ours = boardcopy->count(playerside);
		int theirs = boardcopy->count(otherside);
		if (ours-theirs < worst)
		{
		   worst = ours-theirs;	
		}
	}
	return worst;	
}
