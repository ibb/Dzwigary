/*
 * randUtils.hpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#ifndef RANDUTILS_HPP_
#define RANDUTILS_HPP_

#include <vector>
using namespace std;

int randInt(int N);
void randPermutation(vector<int> &perm);
void randBinaryVector(vector<int> &binVector);
double unifRand();



#endif /* RANDUTILS_HPP_ */
