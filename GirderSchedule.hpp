/*
 * GirderSchedule.hpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#ifndef GIRDERSCHEDULE_HPP_
#define GIRDERSCHEDULE_HPP_

#include <vector>
using namespace std;

class Girder {
private:
	double z;
	double t;
	double r;
	double p;

	double e;
	double d;

	double v;
	double w;

public:
	Girder(double z, double t, double r, double p, double e, double d,
			double v, double w);

	double countCost(double s);

	void print();
};


class GirderSchedule {
private:
	int number;
	vector<Girder> Girders;
public:
	GirderSchedule(char* fileName);

	double countCost(vector<double> &S);
	int getNumber();
	vector<double> findDeliverTime(vector<int> &order);
	void print();

};


#endif /* GIRDERSCHEDULE_HPP_ */
