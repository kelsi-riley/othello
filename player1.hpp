#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {
private:
	Side playerside;
	Side otherside;
	Board *board;
public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    int minimax(Move *move);
    int heuristic(Board *theboard, std::vector<Move *> moves, Side side);
    void setBoard(Board *boardset);
	int alphabeta(Board *aboard, Move *move, int depth, int min, int max);
};

#endif
