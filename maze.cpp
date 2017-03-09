/* Your code here! */
#include "maze.h"
#include "png.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

// Empty parameter constructor.
SquareMaze::SquareMaze() {
	clear();

}

// Makes a new SquareMaze of the given height and width.
void SquareMaze::makeMaze(int width, int height) {
	clear();
	kuan = width; // Just pronounciation in Chinese...
	gao = height; // the same.
	grids.addelements(kuan*gao);
	vector<int> index = getRandom();
/*
	maze.resize(kuan);
	for (int i = 0; i < kuan; i++)
		maze[i].resize(gao);
*/

///*
	maze = new square*[kuan];
	for (int j = 0; j < kuan; j++) {
		maze[j] = new square[gao];
		for (int i = 0; i < gao; i++)
			maze[j][i] = square();
	}
	//}
//*/

	for (int i : index) {
		if (rand() % 2 == 1) {
			if ((i+1)%kuan != 0 && grids.find(i) != grids.find(i+1)) {
				maze[i%kuan][i/kuan].right = false;
				grids.setunion(i, i+1);
			}

			if (i < (gao-1)*kuan && grids.find(i) != grids.find(i+kuan)) {
				maze[i%kuan][i/kuan].down = false;
				grids.setunion(i, i+kuan);
			}
		}

		else {
			if (i < (gao-1)*kuan && grids.find(i) != grids.find(i+kuan)) {
				maze[i%kuan][i/kuan].down = false;
				grids.setunion(i, i+kuan);
			}

			if ((i+1)%kuan != 0 && grids.find(i) != grids.find(i+1)) {
				maze[i%kuan][i/kuan].right = false;
				grids.setunion(i, i+1);
			}
		}

	}
}

// This uses your representation of the maze to determine 
// whether it is possible to travel in the given direction
// from the square at coordinates (x,y).
bool SquareMaze::canTravel(int x, int y, int dir) const {
	if (dir == 3 && y == 0) return false;
	if (dir == 2 && x == 0) return false;

	if (dir==3) 		return !maze[x][y-1].down;
	else if (dir==1)	return !maze[x][y].down;
	else if (dir==2)	return !maze[x-1][y].right;
	else				return !maze[x][y].right;
}

// Sets whether or not the specified wall exists.
void SquareMaze::setWall(int x, int y, int dir, bool exist) const {
	//if (maze.empty()) return;
	if (maze == NULL) return;

	if (dir==3) 		maze[x][y-1] = square(exist, maze[x][y-1].down);
	else if (dir==1)	maze[x][y].down = exist;
	else if (dir==2)	maze[x-1][y].right = exist;
	else				maze[x][y].right = exist;
}

// Solves this SquareMaze.
vector<int> SquareMaze::solveMaze() {
	//cout  << " AA ";
	vector<int> solu;
	vector<vector<int>> solus;
	//cout  << " AA ";
	solus.resize(kuan);
	//cout  << " AA ";
	bool **visited = new bool*[kuan];
	for (int i = 0; i < kuan; i ++) {
		visited[i] = new bool[gao];
		for (int j = 0; j < gao; j++)
			visited[i][j] = false;
	}
	//cout  << " AA ";
	solveHelper(solu, visited, solus, 0, 0);

	size_t path = 0;
	vector<int> solution;
	for (int i = 0 ; i < kuan; i++) {
		if (solus[i].size() > path) {
			solution = solus[i];
			path = solus[i].size();
		}
	}

	return solution;
}

void SquareMaze::solveHelper(vector<int> & solu, bool **& visited, vector<vector<int>> & solus, int x, int y) {

	visited[x][y] = true;
	if (y == gao-1)  { // reach the bottom
			solus[x] = solu;
			//cout << " GET A SOLUTION ";
	}

	if (x < kuan-1 && !visited[x+1][y] && canTravel(x,y,0)) {
		solu.push_back(0);
		solveHelper(solu, visited, solus, x+1, y);
	}	
	if (y < gao-1 && !visited[x][y+1] && canTravel(x,y,1)) {
		solu.push_back(1);
		solveHelper(solu, visited, solus, x, y+1);
	}
	if (x > 0 && !visited[x-1][y] && canTravel(x,y,2)) {
		solu.push_back(2);
		solveHelper(solu, visited, solus, x-1, y);
	}
	if (y > 0 && !visited[x][y-1] && canTravel(x,y,3)) {
		solu.push_back(3);
		solveHelper(solu, visited, solus, x, y-1);
	}

	//cout << "END AT " << "(" << x << ", " << y << ")  ";
	if (!solu.empty()) solu.pop_back();

}

//
// Draws the maze without the solution.
PNG* SquareMaze::drawMaze() const {
	RGBAPixel black = RGBAPixel(0,0,0);

	PNG* pic = new PNG(kuan*10+1, gao*10+1);
	for (int i = 10; i < kuan*10+1; i++)
		*(*pic)(i, 0) = black;
	for (int i = 0; i < gao*10+1; i++)
		*(*pic)(0, i) = black;

	for (int x = 0; x < kuan; x++) {
		for (int y = 0; y < gao; y++) {
			//if (!canTravel(x,y,3)) {
			if (maze[x][y].right == true) {
				for (int k = 0; k <= 10; k++)
					*(*pic)((x+1)*10,y*10+k) = black;
			}

			//if (!canTravel(x,y,1)) {
			if (maze[x][y].down == true) {
				for (int k = 0; k <= 10; k++)
					*(*pic)(x*10+k, (y+1)*10) = black;
			}
		}
	}

	return pic;
}

// This function calls drawMaze, then solveMaze; it modifies
// the PNG from drawMaze to show the solution vector and the exit.
PNG* SquareMaze::drawMazeWithSolution() {
	PNG* pic = drawMaze();
	vector<int> solu = solveMaze();

	int x = 0;
	int y = 0;
	RGBAPixel aka(255, 0, 0);
	for(size_t i = 0; i < solu.size(); i++) {
		int d = solu[i];

		if (d == 0) {
			for (int j = 0; j < 11; j++) {
				*(*pic)(x*10+5+j, y*10+5) = aka;
			}
			x++;
		} else if (d == 1) {
			for (int j = 0; j < 11; j++) {
				*(*pic)(x*10+5, y*10+5+j) = aka;
			}
			y++;
		} else if (d == 2) {
			for (int j = 0; j < 11; j++) {
				*(*pic)(x*10+5-j, y*10+5) = aka;
			}
			x--;
		} else {
			for (int j = 0; j < 11; j++) {
				*(*pic)(x*10+5, y*10+5-j) = aka;
			}
			y--;
		}
	}

	for (int k = 1; k < 10; k++) {
		*(*pic)(x*10+k, (y+1)*10) = RGBAPixel();
	}
	return pic;
}

void SquareMaze::clear() {

	if (maze == NULL) return;

	for (int i = 0; i < kuan; i++) {
		//for (int j = 0; j < gao; j++)
			//delete maze[i][j];
		delete[] maze[i];
		maze[i] = NULL;
	}
	delete[] maze;
	maze = NULL;


	//maze.resize(0);
	kuan = 0;
	gao = 0;
	end = 0;
	//grids = DisjointSets();
	grids.elems.resize(0);
}

vector<int> SquareMaze::getRandom() {

	vector<int> temp;
	for (int i = 0; i < gao*kuan; i++)
		temp.push_back(i);

	random_shuffle(temp.begin(), temp.end());

	return temp;
}



