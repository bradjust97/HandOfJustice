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
    myBoard = new Board();
    mySide = side;
    rand = true;
    greedy = false;
    testingMinimax = false;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


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
    if(possMoves.size() > 0) {
        int movei = std::rand() % (possMoves.size());
        Move* answer = possMoves[movei];
        return answer;
    }
    else {
        return nullptr;
    }
}

int Player::getScore(Board* theBoard){
    if(mySide == BLACK)
    {
        return theBoard->countBlack() - theBoard->countWhite();
    }
    else
    {
        return theBoard->countWhite() - theBoard->countBlack();
    }
}


Move* Player::doGreedyMove() {
    vector<Move*> allPossMoves = myBoard->getAllMoves(mySide);
    
    if(allPossMoves.size() > 0) {
        Move* bestMove = allPossMoves[0];
        Board* bestBoard = myBoard->copy();
        bestBoard->doMove(bestMove, mySide);
        int bestScore = this->getScore(bestBoard);
        for (unsigned int i = 1; i < allPossMoves.size(); i++)
        {
            Move* testMove = allPossMoves[i];
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
    else {
        return nullptr;
    }
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
Move* Player::doMove(Move *opponentsMove, int msLeft) {
    myBoard->doMove(opponentsMove, getOppSide(mySide));
    Move* answer;
    if(this->rand == true)
    {
        answer = this->doRandomMove();
    }
    else if (this->greedy == true) 
    {
        answer = this->doGreedyMove();
    }
    else
    {
        //this->doMinMaxMove();
    }
    myBoard->doMove(answer, mySide);
    return answer;
}