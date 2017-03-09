# MazeSolver
The final MP of my data structure course. I wrote all the code except RGBAPixel and PNG library.
This program can create a maze without a loop and with a unique solution, i.e., a spanning tree, and provide the solution.
The shape of the maze can be modified by changing parameters in testsquremaze.cpp file.

# Method used
I used disjoint set method to prevent creating loop, and DFS to search for a solution of the maze.
