/*
 * randUtils.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include "randUtils.hpp"
#include <cstdlib>

using namespace std;

int randInt(int N){
	return (int)((double)rand() / ((double)RAND_MAX + 1) * N);
}

void randPermutation(vector<int> &perm){
	int n = perm.size();
	for (int i = 0; i < n; ++i) {
	    int j = randInt(i+1);
	    perm[i] = perm[j];
	    perm[j] = i;
	  }
}

void randBinaryVector(vector<int> &binVector){
	int n = binVector.size();
	for (int i = 0; i < n; ++i) {
		binVector[i] = randInt(2);
	}
}

double unifRand()
{
    return rand() / double(RAND_MAX);
}

