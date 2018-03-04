#include "player.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <stdlib.h>
//Eric Han's smallio change
//Brad Justice smallerio change 

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
    myBoard = new Board();
    mySide = side;

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

//returns the side of the other player.
Side Player::getOppSide(Side side) {
    if(side == WHITE) {
        return BLACK;
    }
    else {
        return WHITE;
    }
}

Move* Player::doRandomMove(){

    vector<Move*> possMoves = myBoard->getAllMoves(mySide);
    int movei = std::rand() % (possMoves.size() - 1);
    Move* answer = possMoves.at(movei);
    return answer;
}

int Player::getScore(Board* theBoard){
    if(mySide == BLACK)
    {
        return theBoard->countBlack();
    }
    else
    {
        return theBoard->countWhite();
    }
}


Move* Player::doGreedyMove(){
    vector<Move*> allPossMoves = myBoard->getAllMoves(mySide);
    Move* bestMove;
    int bestScore;
    for (unsigned int i = 0; i < allPossMoves.size(); i++)
    {
        Move* testMove = allPossMoves.at(i);
        Board* newBoard = myBoard->copy();
        newBoard->doMove(testMove, mySide);
        int newScore = this->getScore(newBoard);
        if(newScore > bestScore)
        {
            bestScore = newScore;
            bestMove = testMove;
        }

    }
    return bestMove;
}


Move* Player::doMove(Move *opponentsMove, int msLeft) {

    Move* answer = nullptr;
    myBoard->doMove(opponentsMove, getOppSide(mySide));
    if(this->rand == true)
    {
        answer = this->doRandomMove();
    }/*
    else if (this->greedy == true) 
    {
        this->doGreedyMove();
    }
    else
    {
        this->doMinMaxMove();
    }
    *
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    return answer;
}