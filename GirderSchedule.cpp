/*
 * GirderSchedule.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "GirderSchedule.hpp"

Girder::Girder(double z, double t, double r, double p, double e, double d,
		double v, double w) {
	this->z = z;
	this->t = t;
	this->r = r;
	this->p = p;
	this->e = e;
	this->d = d;
	this->v = v;
	this->w = w;
}

double Girder::countCost(double s) {
	double E = max(0.0, e - s);
	double T = max(0.0, s - d);
	return v * E + w * T;
}

void Girder::print() {
	cout << "z: " << z << "\tt: " << t << "\tr: " << r << "\tp: " << p
			<< "\te: " << e << "\td: " << d << " \tv: " << v << "\tw: " << w
			<< endl;
}

GirderSchedule::GirderSchedule(char* fileName) {
	double z, t, r, p, e, d, v, w;
	ifstream infile(fileName);
	infile >> (this->number);
	for (int i = 0; i < this->number; i++) {
		infile >> z >> t >> r >> p >> e >> d >> v >> w;
		Girders.push_back(Girder(z, t, r, p, e, d, v, w));
	}
}

double GirderSchedule::countCost(vector<double> &S) {
	// S = (s_1,s_2,  ,s_k) is a vector where si is a term for ith girder
	// k can be < than n
	int num = S.size();
	double cost = 0;
	for (int i = 0; i < num; i++) {
		cost += this->Girders[i].countCost(S[i]);
	}
	return cost;
}

int GirderSchedule::getNumber() {
	return this->number;
}

vector<double> GirderSchedule::findDeliverTime(vector<int> &order) {
	//Krzysiu, uzupełnij prosze tę funkcję
	//Na razie zwraca ona fikcyje wartości w celu testowania całego programu
	// Weź pod uwagę, że długości order może być mniejsza od ilości dzwigarów,
	//potrzebne jest to do naszej wersji przeszukiwania lokalnego
	vector<double> deliverTime;
	deliverTime.resize(order.size());
	for(int i=0; i< order.size(); i++){
		deliverTime[i] = order[i];
	}
	return deliverTime;

}

void GirderSchedule::print() {
	for (int i = 0; i < this->number; i++) {
		this->Girders[i].print();
	}
}

