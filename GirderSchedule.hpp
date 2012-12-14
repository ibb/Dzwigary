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
	Girder();
	Girder(double z, double t, double r, double p, double e, double d,
			double v, double w);

	double countCost(double s);
	bool static cmpD(pair<Girder,int > a, pair<Girder,int > b);
	bool static cmpE(pair<Girder,int > a, pair<Girder,int > b);
	bool static cmpED(pair<Girder,int > a, pair<Girder,int > b);

	void print();
	
	friend class GirderSchedule;
};


class GirderSchedule {
private:
	int number;
	vector<Girder> Girders;
public:
	GirderSchedule(const char* fileName);

	double countCost(vector<double> &S);
	int getNumber();
	vector<double> findDeliverTime(vector<int> &order);
	vector<int> minDTime();
	vector<int> minETime();
	vector<int> minEDTime();
	vector<int> sortGirders(bool (*cmpfun)(pair<Girder,int>, pair<Girder,int>));
	void print();

};


#endif /* GIRDERSCHEDULE_HPP_ */
