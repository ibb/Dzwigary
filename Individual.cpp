/*
 * Individual.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include <vector>
#include <iostream>
#include <algorithm>

#include "Individual.hpp"
#include "randUtils.hpp"
#include "GirderSchedule.hpp"

using namespace std;

Individual::Individual(Environment* env) {
	this->value = -1; // I assume that all weights are not negative
	this->length = env->individualLength();
	this->env = env;
	chromosome.resize(this->length);
	randPermutation(chromosome);

}

Individual::Individual(Environment* env, vector<int> &chromosom) {
	this->value = -1; // I assume that all weights are not negative
	this->length = chromosom.size();
	this->chromosome = chromosom;
	this->env = env;

}


bool Individual::operator<(const Individual &a) const{
	return this->value < a.value;

}

void Individual::addGene(int girderNum){
	return this->chromosome.push_back(girderNum);
	this->value = -1;
	this->length++;
}

void Individual::swapGenes(int p1, int p2){
	swap(this->chromosome[p1],this->chromosome[p2]);
	this->value = -1;
}


vector<vector<int> > Individual::uniformCrossover(Individual *in2) {
	vector<int> binVector(this->length, 0);
	vector<int> child1(this->length, -1);
	vector<int> child2(this->length, -1);
	vector<vector<int> > res;


	randBinaryVector(binVector);

	for (int i = 0; i < this->length; i++) {

		//first copy values accordingly to binVector
		if (binVector[i] == 0) {
			child1[i] = this->chromosome[i];
		} else {
			child2[i] = in2->chromosome[i];
		}
	}
	fillPermutation(child1, in2->chromosome);
	fillPermutation(child2, this->chromosome);

	res.push_back(child1);
	res.push_back(child2);


	binVector.clear();
	return res;

}
void Individual::mutate(){
	int p1 = randInt(this->length);
	int p2 = randInt(this->length);
	swap(this->chromosome[p1], this->chromosome[p2]);
	this->value = -1;
}

void Individual::fillPermutation(vector<int> &child, vector<int> &parent) {
	int j = 0;
	for (int i = 0; i < this->length; i++) {

		if (child[i] == -1) {
			while (j < this->length && find(child.begin(), child.end(),
					parent[j]) != child.end()) {
				j++;
			}
			child[i] = parent[j];
		}
	}

}

void Individual::evaluate(){

	if(this->value == -1){
		GirderSchedule *GS = this->env->getGirderSchedule();
		vector<double> deliverTime = GS->findDeliverTime(this->chromosome);
		this->value = GS->countCost(deliverTime);
	}



}

void Individual::localSeach()
{
	vector<int> order;
	Individual *in = new Individual(this->env,order);
	in->addGene(this->chromosome[0]);

	double min;
	vector<int> minChromosom;
	minChromosom.resize(this->length);
	for(int i=1; i<this->length; i++)
	{
		in->addGene(this->chromosome[i]);
		in->evaluate();
		min = in->value;
		copy(in->chromosome.begin(),in->chromosome.end(), minChromosom.begin());
		for(int j=i-1; j>= 0; j--){
			in->swapGenes(j,j+1);
			in->evaluate();
			if(in->value < min)
			{
				min = in->value;
				copy(in->chromosome.begin(),in->chromosome.end(), minChromosom.begin());
			}
		}

	}
	this->chromosome.clear();
	this->chromosome = minChromosom;
	this->value = min;

}

void Individual::print() {
	vector<int>::iterator it;
	for (it = chromosome.begin(); it != chromosome.end(); it++)
		cout << *it << " ";
	cout << endl;
	cout << "value: " << value << endl;
}

Individual::~Individual(){
	chromosome.clear();
}

