#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Side getOppSide(Side side);
    Move* minimaxMove(int steps, Side side, Board* board);
    int getMinimaxScore(int steps, Side side, Board* board);
    Move *doMove(Move *opponentsMove, int msLeft);
    Move* doRandomMove();
    int getScore(Board* theBoard);
    Move* doGreedyMove();

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    bool greedy;
    bool rand; 
    Board* myBoard;
    Side mySide;
};

#endif
