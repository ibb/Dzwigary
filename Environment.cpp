/*
 * Environment.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */
#include <cassert>
#include <iostream>
#include "Environment.hpp"
#include "Population.hpp"

Environment::Environment(GirderSchedule *GS, int populationSize,
		int maxIteration, double mutateRate) {
	this->GS = GS;
	this->populationSize = populationSize;
	this->maxIteration = maxIteration;
	this->iterationNumber = 0;
	this->mutateRate = mutateRate;
	this->minValue = -1;

	assert(populationSize % 2 == 0);
}
int Environment::individualLength() {
	return GS->getNumber();
}

void Environment::run() {
	Population *population = new Population(this, populationSize);
	while (terminationCondition()) {
		population->crossover();
		population->mutate(this->mutateRate);
		population->localSearch();
		population->evaluate();
		population->replace();
		this->iterationNumber++;
		double minVal = population->getMin();
		if (this->minValue == -1 || minVal < this->minValue) {
			this->minValue = minVal;
		}

	}
	cout << this->minValue << endl;
}

bool Environment::terminationCondition() {
	return iterationNumber < maxIteration;
}

GirderSchedule * Environment::getGirderSchedule() {
	return this->GS;
}

//Environment::~Environment(){
//}
