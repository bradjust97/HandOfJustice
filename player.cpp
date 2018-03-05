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
    vector<Move*> possMoves = board->getallMoves(side);
    Move* bestMove;
    if(possMoves.size() > 0) {
        bestMove = possMoves[0];
        for(int i = 1; i < possMoves.size(); i++) {
            if(this->getWorstScore(steps, side, board, possMoves[i]) > this->getWorstScore(steps, side, board, bestMove)) {
                bestMove = possMoves[i];
            }
        }
        return bestMove;
    }
    else {
        return nullptr;
    }
    
}

//for some move on a board with a certain number of steps, determine the worst score possible.
//this function only makes sense if last step is the other player's move
int Player::getWorstScore(int steps, Side side, Board* board, Move* move) {

    //return value. The worst score of this particular move from this board. 
    int worst; 

    //get board after this player has moved. 
    Board* afterMoveBoard = board->copy();
    afterMoveBoard->doMove(move, side);

    //get vector of all possible moves of the other player.
    vector<Move*> possMoves = afterMoveBoard->getAllMoves(getOppSide(side));

    //if there are possible moves, do stuff. 
    if(possMoves.size() != 0) {
        //base case
        //heuristic is the heuristic func, whatever it is.
        if(steps == 1) {
            //create vector of boards after all possible last step moves.
            vector<Board*> afterMoveBoards;
            for(int i = 0; i < possMoves.size(); i++) {
                Board* boardCopy = afterMoveBoard->copy();
                boardCopy->doMove(possMoves[i], side);
                afterMoveBoards.push_back(boardCopy);
            }
            //get worst possible score from the available last states. 
            worst = heuristic(afterMoveBoards[0]);
            int thisWorst;
            for(int i = 1; i < possMoves.size(); i++) {
                thisWorst = heuristic(possMoves[i]);
                if(thisWorst < worst) {
                    worst = thisWorst;
                }
            }
            return worst;
        }
        else {
            //recursive step
            worst = getWorstScore(steps-1, side, board, possMoves[0]);
            int thisWorst;
            for(int i = 1; i < possMoves.size(); i++) {
                thisWorst = getWorstScore(steps-1, side, board, possMoves[i]);
                if(thisWorst < worst) {
                    worst = thisWorst;
                }
            }
            return worst;
        }
    }
    else {
        //kinda stop gap. If there are no possible moves from this board state, 
        //then that means you lost. Give super low score so that you know not to do it. 
        return -100;
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
