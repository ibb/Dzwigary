/*
 * Population.hpp
 *
 *  Created on: 30-11-2012
 *      Author: ibb
 */
using namespace std;
#include <vector>
#include "Individual.hpp"



#ifndef POPULATION_HPP_
#define POPULATION_HPP_

class Population{
private:
	vector<Individual> individuals;
	int size;
	Environment *env;
public:
	Population(Environment *env, int size);
	void crossover();
	void evaluate();
	void mutate(double mutationtRate);
	void replace();
	void localSearch();
	double getMin();
	void print();


};


#endif /* POPULATION_HPP_ */
