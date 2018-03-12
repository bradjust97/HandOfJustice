USE OF THIS GAMEPLAYER

Run as normal. To alter what type of player is running, go into player.cpp. 
Go to the constructor. There are three booleans, named rand, greedy, and minimax.
Set one to true and the other two to false to use that player type. 

Greedy corresponds to a greedy algorithm that picks the best next move by the difference 
between the number of its own stones and the number of the enemy's stones.

Minimax performs the minimax algorithm. At the moment, it is a 2-plie player. This can be set to different in 
player.cpp doMove() function. 

rand corresponds to a player that plays entirely random valid moves. 

================================

Eric Han's contributions
 - Wrote minimax algorithm
 - Wrote getAllMoves() function

Bradley Justice's contributions
 - Wrote player's constructor
 - Wrote greedy algorithm 
 - Wrote random algorithm
 - Wrote and improved heuristic
 
 ================================
 Our update for assignment 10: 
 We updated the heuristic. We believe that will make the AI prioritize more critical areas, such as the sides and corners, and deprioritize squares that are less useful in the long term. 
