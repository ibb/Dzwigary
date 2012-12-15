/*
 * Environment.hpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include "GirderSchedule.hpp"
#include "plot.hpp"

#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

typedef enum {
	RANDOM, SPECIALIND
} Initialisation;

class Environment {
private:
	GirderSchedule *GS;
	int populationSize;
	int maxIteration;
	int iterationNumber;
	double mutateRate;
	double minValue;
	Initialisation initialisation;
	double endDifference;
	int endIteration;
	double minEndIterationsValue;
	Statistic stats;
public:
	Environment(GirderSchedule *GS, int populationSize, int maxIteration,
			double mutateRate, Initialisation m, double endDifference,
			int endIteration);
	int individualLength();

	void run();

	bool terminationCondition();
	GirderSchedule * getGirderSchedule();
};

#endif /* ENVIRONMENT_HPP_ */
