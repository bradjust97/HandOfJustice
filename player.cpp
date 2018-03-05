#include "player.hpp"

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



Move* Player::doMove(Move *opponentsMove, int msLeft) {

    this->myBoard->doMove(opponentsMove, getOppSide(mySide));

    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    return nullptr;
}
