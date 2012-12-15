/*
 * Population.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Population.hpp"
#include "randUtils.hpp"

using namespace std;

Population::Population(Environment *env, int size, Initialisation m) {
	this->size = size;
	this->env = env;

	int sind = 0;
	if( m == SPECIALIND){
		vector<int> order;
		GirderSchedule *GS = env->getGirderSchedule();
		order = GS->minDTime();
		individuals.push_back(Individual(env,order));
		order = GS->minETime();
		individuals.push_back(Individual(env,order));
		order = GS->minEDTime();
		individuals.push_back(Individual(env,order));
		sind = 3;
	}
	for (int i = 0; i < this->size-sind; i++) {
		individuals.push_back(Individual(env));
	}
}

void Population::crossover() {
	//pairwise crossover of all individuals, individuals are match in pairs random
	vector<int> perm(this->size, 1);
	vector<vector<int> > res;

	randPermutation(perm);
	for (int i = 0; i < this->size; i += 2) {
		res = this->individuals[perm[i]].uniformCrossover(&individuals[perm[i + 1]]);

		Individual *in1 = new Individual(this->env, res[0]);
		Individual *in2 = new Individual(this->env, res[1]);
		individuals.push_back(*in1);
		individuals.push_back(*in2);
	}
	this->size *= 2;
	perm.clear();
}

void Population::mutate(double mutationtRate){
	vector<Individual>::iterator it;
	for(it = individuals.begin(); it!=individuals.end(); it++){
		if(unifRand() <mutationtRate ){
			it->mutate();
		}

	}

}

void Population::replace(){
	sort(individuals.begin(), individuals.end());
	this->size /= 2;
	individuals.resize(this->size, Individual(this->env));
}

void Population::evaluate(){
	vector<Individual>::iterator it;
	for(it = individuals.begin(); it!=individuals.end(); it++){
		it->evaluate();
	}
}

void Population::localSearch(){

	vector<Individual>::iterator  best;
	best = min_element(individuals.begin(), individuals.end());
	best->localSeach();

}

double Population::getMin(){
	return min_element(individuals.begin(), individuals.end())->getValue();
}

double Population::getMax(){
	return max_element(individuals.begin(), individuals.end())->getValue();
}

double Population::getMean(){
	vector<Individual>::iterator it;
	int sum = 0;
	for(it= individuals.begin(); it!= individuals.end(); it++){
		sum += it-> getValue();
	}
	return (double)sum/this->size;
}

void Population::print() {
	vector<Individual>::iterator it;
	int i = 0;
	for (it = individuals.begin(); it != individuals.end(); it++) {
		cout << "Individual " << i++ << endl;
		it->print();
		cout <<endl;
	}

}

