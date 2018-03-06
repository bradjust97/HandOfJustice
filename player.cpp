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

//looks at the board state, checks how many steps ahead. 
//uses worstScore function to return worst score for each of the next moves. picks move with best worstScore. 
Move* Player::minimaxMove(int steps, Side side, Board* board) {
    vector<Move*> possMoves = board->getAllMoves(side);
    Move* bestMove;
    if(possMoves.size() > 0) {
        bestMove = possMoves[0];
        for(int i = 1; i < possMoves.size(); i++) {
            if(this->getMinimaxScore(steps, side, board->copy()->doMove(possMoves[i], side)) > 
                this->getMinimaxScore(steps, side, board->copy()->doMove(bestMove, side))) {
                bestMove = possMoves[i];
            }
        }
        return bestMove;
    }
    else {
        return nullptr;
    }
    
}

//get the minimax score from this particular board state. 
int Player::getMinimaxScore(int steps, Side side, Board* board) {
    //return value. The max or min score of this particular move on the board. 
    int score; 
    //make a bool for if you are trying to max or minimize the final score. 
    bool isMaxing;
    if(side == mySide) {
        isMaxing = true
    }
    else {
        isMaxing = false;
    }

    //get vector of all possible moves that you can make. 
    vector<Move*> possMoves = board->getAllMoves(side);

    //if there are possible moves, do stuff. 
    if(possMoves.size() != 0) {
        //base case
        //heuristic is the heuristic func, whatever it is.
        if(steps == 1) {
            //return the score of this particular board
            return getScore(board);
        }
        else {
            //recursive step
            score = getMinimaxScore(steps-1, this->getOppSide(side), board->copy()->doMove(possMoves[0], side));
            int thisScore;
            if(isMaxing) {
                for(int i = 1; i < possMoves.size(); i++) {
                    thisScore = getMinimaxScore(steps-1, this->getOppSide(side), board->copy()->doMove(possMoves[i], side));
                    if(thisScore > score) {
                        score = thisScore;
                    }
                }
            }
            else {
                for(int i = 1; i < possMoves.size(); i++) {
                    thisScore = getMinimaxScore(steps-1, side, board->copy()->doMove(possMoves[i], side));
                    if(thisScore < score) {
                        score = thisScore;
                    }
                }
            }
            return score;
        }
    }
    else {
        //kinda stop gap. If there are no possible moves from this board state and you are trying to max, that means
        //maxxer lost. If you are minimizer and you lose, that's beneficial. 
        if(isMaxing) {
            return -100;
        }
        else {
            return 100;
        }
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
>>>>>>> master
