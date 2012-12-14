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
		int maxIteration, double mutateRate, Initialisation m,
		double endDifference, int endIteration) {
	this->GS = GS;
	this->populationSize = populationSize;
	this->maxIteration = maxIteration;
	this->iterationNumber = 1;
	this->mutateRate = mutateRate;
	this->minValue = -1;
	this->initialisation = m;
	this->endDifference = endDifference;
	this->endIteration = endIteration;
	this->minEndIterationsValue = -1;


	assert(populationSize % 2 == 0);
}
int Environment::individualLength() {
	return GS->getNumber();
}

void Environment::run() {
	Population *population = new Population(this, populationSize,this->initialisation);
	population->evaluate();
	this->minEndIterationsValue = population->getMin();
	this->minValue = population->getMin();
	while (terminationCondition()) {
		population->crossover();
		population->mutate(this->mutateRate);
		population->localSearch();
		population->evaluate();
		population->replace();
		this->iterationNumber++;
		double minVal = population->getMin();
		if (minVal < this->minValue) {
			this->minValue = minVal;
		}

	}
	cout << this->minValue << endl;
}

bool Environment::terminationCondition() {
	if(this->iterationNumber % this->endIteration == 0)
	{
		if((this->minEndIterationsValue - this->minValue) < this->endDifference){
			return false;
		}
		this->minEndIterationsValue = this->minValue;
		return true;

	}
}

GirderSchedule * Environment::getGirderSchedule() {
	return this->GS;
}

//Environment::~Environment(){
//}
