/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets {

 public:
 	// Creates n unconnected root nodes at the end of the vector.
 	void addelements(int num);

 	// This function should compress paths and works as described in lecture.
 	int find(int elem);

 	// This function should be implemented as union-by-size.
 	void setunion(int a, int b);

 //private:
 	std::vector<int> elems;
};


#endif // DSETS_H