/*
 * Individual.hpp
 *
 *  Created on: 30-11-2012
 *      Author: ibb
 */

#include <vector>
#include "Environment.hpp"
using namespace std;

#ifndef INDIVIDUAL_HPP_
#define INDIVIDUAL_HPP_


class Individual{
private:
	vector<int> chromosome;
	double value; //before evaluation value is -1
	double length;
	Environment * env;

	void fillPermutation(vector<int> &child, vector<int> &parent);

public:
	Individual(Environment* env);
	Individual(Environment* env, vector<int> &chromosom);
	~Individual();
	bool operator<(const Individual &a) const;
	void addGene(int girderNum);
	void swapGenes(int p1, int p2);
	vector <vector<int> >  uniformCrossover(Individual *in2);
	void evaluate();
	void mutate();
	void localSeach();
	void print();
	double getValue(){return this->value;}


};


#endif /* INDIVIDUAL_HPP_ */
