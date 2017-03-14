Both of us worked on writing our implmentation of player and debugging it.
For the most part we worked together, disucssing and editing our code 
together. Occassionally, one of us would work on implementing/debugging
individually, but this was fairly uncommon. Because we were working
together,there are probably relatively few commits/the commits might not
indicate an even even distribution of work, but this is because we were 
mostly working together on a single computer.

Our Improvements:
-We implemented alpha-beta pruning for this week.
-We updated our heuristic function because our last one was buggy (i.e.
if we had a very favorable set of moves, but had a single unfavorable
board position, then our heuristic would be very negative). Also our old
heuristic function did not consider the entire board configuration following
our moves, so we updated it to do so
-We addressed memory leak problems

-Our heuristic improvements should lead our player (JoeORourkeTheScienceDork)
to choose moves that lead to configurations in which we have the corners
and if we don't have the corners, we don't play in positions adjacent to them
if possible to avoid our opponent obtaining corner positions. Our heuristic will 
always be the maximum value when the board configuration  is a completed 
game and we have won and the minimum value when the board is a completed
game and we have lost.
This updated heuristic should lead us to choose favorable moves pretty consistently
andthe alpha-beta pruning will make our player mmore efficient.
