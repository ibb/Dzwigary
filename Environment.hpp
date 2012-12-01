/*
 * Environment.hpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include "GirderSchedule.hpp"

#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

class Environment{
private:
	GirderSchedule *GS;
	int populationSize;
	int maxIteration;
	int iterationNumber;
	double mutateRate;
	double minValue;
public:
	Environment(GirderSchedule *GS, int populationSize, int maxIteration, double mutateRate);
	int individualLength();

	void run();

	bool terminationCondition();
	GirderSchedule * getGirderSchedule();
};

#endif /* ENVIRONMENT_HPP_ */
