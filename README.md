# 16-2-Conway-s-Game-of-Life-Cycle-Finder
Finds both the cycle length and the number of generations (iterations) required to get to the cycle.

I did a silly thing in the beginning while first creating the game of life without the cycle finder: I made the board a 2D array of ints.
Then, to save on memory, I convert the 2D arrays of ints to a vector of booleans and store it in a vector of vectors of booleans.
Then, they are all compared against each other until a loop is found (e.g. one of the board states == one of the other board states)

If I were to do the project again, I'd simply have the input converted directly into a vector of booleans to save myself the conversion down the road.
I'd also make the board size modifiable.
