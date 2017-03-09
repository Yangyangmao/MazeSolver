/* Your code here! */
#include "dsets.h"
#include <vector>
#include <iostream>
using namespace std;

void DisjointSets::addelements(int num) {
	for (int i = 0; i < num; i++)
		elems.push_back(-1);
}

int DisjointSets::find(int elem) {
	//cout << elem << "  " << elems[elem] << endl;
	if (elems[elem] < 0) return elem;
	else return elems[elem] = find(elems[elem]);
}

void DisjointSets::setunion(int a, int b) {
	int rootA = find(a);
	int rootB = find(b);
	if (rootA == rootB) return;

	int nsizeA = elems[rootA];
	//cout << nsizeA << endl;
	int nsizeB = elems[rootB];
	//cout << nsizeB <<endl;

	if (nsizeA < nsizeB) {		// sizeA <= sizeB
		elems[rootB] += nsizeA;
		elems[rootA] = rootB;
	} else {
		elems[rootA] += nsizeB;
		elems[rootB] = rootA;
	}
	//cout << "HHH    " << endl;
	//cout << elems[rootA] << endl;
	//cout << elems[rootB] << endl;

}