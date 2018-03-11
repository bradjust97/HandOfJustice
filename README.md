USE OF THIS GAMEPLAYER

Run as normal. To alter what type of player is running, go into player.cpp. 
Go to the constructor. There are three booleans, named rand, greedy, and minimax.
Set one to true and the other two to false to use that player type. 

Greedy corresponds to a greedy algorithm that picks the best next move by the difference 
between the number of its own stones and the number of the enemy's stones.

Minimax performs the minimax algorithm. At the moment, it is a 2-plie player. This can be set to different in 
player.cpp doMove() function. 

rand corresponds to a player that plays entirely random valid moves. 
