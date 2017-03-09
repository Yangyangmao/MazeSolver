/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "png.h"
#include "dsets.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

class SquareMaze {
private:
	class square {
	public:
		//int x, y;
		square() {
			down = true;
			right = true;
		}
		square(bool a, bool b) {
			down = a;
			right = b;
		}
		bool down = true;
		bool right = true;
	};

public:
	// Empty parameter constructor.
	SquareMaze(); 

	// Makes a new SquareMaze of the given height and width.
	void makeMaze(int width, int height);

	// This uses your representation of the maze to determine 
	// whether it is possible to travel in the given direction
	// from the square at coordinates (x,y).
	bool canTravel(int x, int y, int dir) const;

	// Sets whether or not the specified wall exists.
	void setWall(int x, int y, int dir, bool exist) const;

	// Solves this SquareMaze.
	std::vector<int> solveMaze();

	// Draws the maze without the solution.
	PNG* drawMaze() const;

	// This function calls drawMaze, then solveMaze; it modifies
	// the PNG from drawMaze to show the solution vector and the exit.
	PNG* drawMazeWithSolution();

		

private:
	int kuan;
	int gao;
	int end;
	//vector<vector<square>> maze;
	square ** maze = NULL;
	DisjointSets grids;

	void clear();
	vector<int> getRandom();
	void solveHelper(vector<int> & solu, bool **&visited, vector<vector<int>> & solus, int x, int y);
	//void solver()
};


#endif // MAZE_H