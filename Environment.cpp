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

	this->stats.maxIteration = this->maxIteration;
	this->stats.populationSize = this->populationSize;
	this->stats.mutateRate = this->mutateRate;
	if(m == RANDOM){
		this->stats.initialisation = "RANDOM";
	}
	else{
		this->stats.initialisation = "SPECIALIND";
	}



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
		population->evaluate();
		population->localSearch();

		this->stats.average[this->iterationNumber-1] = population->getMean();
		this->stats.best[this->iterationNumber-1] = population->getMin();
		this->stats.worst[this->iterationNumber-1] = population->getMax();
//		cout << "stats" << endl;
//		cout << this->stats.average[this->iterationNumber] << endl;
//		cout << this->stats.best[this->iterationNumber] << endl;
//		cout << this->stats.worst[this->iterationNumber] << endl;

		population->replace();
		this->iterationNumber++;
		double minVal = population->getMin();
		cout << minVal << endl;
		if (minVal < this->minValue) {
			this->minValue = minVal;
		}

	}
	cout << this->minValue << endl;
	cout << this->iterationNumber << endl;
	makePlot(this->stats, "plik.tex");
}

void Environment::random(int iter) {
	Population *population = new Population(this, iter,RANDOM);
	population->evaluate();
	cout << population->getMin() << endl;
}

bool Environment::terminationCondition() {
	if(this->iterationNumber % this->endIteration == 0)
	{
		if((this->minEndIterationsValue - this->minValue) < this->endDifference){
			return false;
		}
		this->minEndIterationsValue = this->minValue;


	}
	else if(this->iterationNumber > maxIteration)
		return false;
	return true;
}

GirderSchedule * Environment::getGirderSchedule() {
	return this->GS;
}

//Environment::~Environment(){
//}
