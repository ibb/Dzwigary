/*
 * GirderSchedule.cpp
 *
 *  Created on: 30-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "GirderSchedule.hpp"

Girder::Girder()
{
}

Girder::Girder(double z, double t, double r, double p, double e, double d,
		double v, double w) {
	this->z = z; // czas załadunku
	this->t = t; // czas transportu na czas budowy
	this->r = r; // czas rozładunku na placu budowy
	this->p = p; // czas powrotu
	this->e = e; // żądany najwcześniejszy termin przywozu
	this->d = d; // żądany najpóźniejszy termin przywozu
	this->v = v; // wsp. f. kary za zbyt wczesne przybycie
	this->w = w; // wsp. f. kary za zbyt późne przybycie
}

double Girder::countCost(double s) {
	double E = max(0.0, e - s);
	double T = max(0.0, s - d);
	return v * E + w * T;
}

bool Girder::cmpD(pair<Girder,int > a, pair<Girder,int > b){
return a.first.d < b.first.d;
}

bool Girder::cmpE(pair<Girder,int > a, pair<Girder,int > b){
return a.first.e < b.first.e;
}

bool Girder::cmpED(pair<Girder,int > a, pair<Girder,int > b){
double meanA = a.first.d - a.first.e;
double meanB = b.first.d - b.first.e;
return meanA < meanB;
}

void Girder::print() {
	cout << "z: " << z << "\tt: " << t << "\tr: " << r << "\tp: " << p
			<< "\te: " << e << "\td: " << d << " \tv: " << v << "\tw: " << w
			<< endl;
}

GirderSchedule::GirderSchedule(const char* fileName) {
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
	int num = number;
	double cost = 0;
	for (int i = 0; i < num; i++) {
		if(S[i]!=-1)
		{
			cost += this->Girders[i].countCost(S[i]);
		}
	}
	return cost;
}

int GirderSchedule::getNumber() {
	return this->number;
}

vector<double> GirderSchedule::findDeliverTime(vector<int> &order)
{
	Girder G;
	double bestDeliverCost, currentDeliverCost;
	vector<double> lastIterationBestDeliverTime, bestDeliverTime, currentDeliverTime;

	lastIterationBestDeliverTime.resize(Girders.size());
	bestDeliverTime.resize(Girders.size());
	currentDeliverTime.resize(Girders.size());
	
	// Rozważamy sytuację, w której mamy tylko jeden dźwigar do rozpatrzenia
	for (int i = 0; i < lastIterationBestDeliverTime.size(); i++)
		lastIterationBestDeliverTime[i] = -1;
	if (order.size() == 0) return lastIterationBestDeliverTime;
	// Ustawiamy go tak, aby wypadł na początku okienka lub od czasu zerowego.
	G = Girders[order[0]];
	lastIterationBestDeliverTime[order[0]] = max(G.z + G.t + G.r, G.e);
	
	// Ustawiamy i+1 pierwszych dźwigarów (od 0 do i)
	for(int i = 1; i < order.size(); i++)
	{
		// Jeśli da się ustawić i-te zadanie bez przeszkód to ustawiamy i kończymy
		G = Girders[order[i]];
		if (lastIterationBestDeliverTime[order[i-1]] + Girders[order[i-1]].p + G.z + G.t + G.r <= G.d)
		{
			lastIterationBestDeliverTime[order[i]] = max(G.e, lastIterationBestDeliverTime[order[i-1]] + Girders[order[i-1]].p + G.z + G.t + G.r);
//printf("Ustawiam je sobie, bo mogę.\n");
		}
		else
		{
			// Po pierwsze spróbujemy je ustawić od 0 po kolei
			for (int j = 0; j < bestDeliverTime.size(); j++)
				bestDeliverTime[j] = -1;
			float c = 0;
			for (int j = 0; j <= i; j++)
			{
				G = Girders[order[j]];
				bestDeliverTime[order[j]] = c + G.z + G.t + G.r;
				c += G.z + G.t + G.r + G.p;
			}
			bestDeliverCost = countCost(bestDeliverTime);
//printf("Pocz: ");
//for (int m = 0; m < bestDeliverTime.size(); m++) printf("%lf ", bestDeliverTime[m]); printf("\n");
			for (int j = 0; j <= i; j++)
			{
				// Próbujemy tak ustawić czasy, aby zadanie j-te zostało wykonane w czasie.
				
				// Skopiuj wynik z poprzedniej iteracji:
				for (int k = 0; k < Girders.size(); k++)
					currentDeliverTime[k] = lastIterationBestDeliverTime[k];
				
				// Ustaw j-te zadanie na czas d oraz e
				float possibilities[] = {Girders[order[j]].e, Girders[order[j]].d};
				
				for (int z = 0; z < 2; z++)
				{
					currentDeliverTime[order[j]] = possibilities[z];
					
					// Zadania po nim - w ogonku
					c = currentDeliverTime[order[j]] + Girders[order[j]].p;
					for (int k = j+1; k <= i; k++)
					{
						G = Girders[order[k]];
						currentDeliverTime[order[k]] = c + G.z + G.t + G.r;
						c += G.z + G.t + G.r + G.p;
					}
					
					// Zadania przed nim spychamy w lewo.
					int k = j-1;
					G = Girders[order[k+1]];
					while (k >= 0 && currentDeliverTime[order[k]] + Girders[order[k]].p > currentDeliverTime[order[k+1]] - G.z - G.t - G.r)
					{
						currentDeliverTime[order[k]] = currentDeliverTime[order[k+1]] - G.z - G.t - G.r - Girders[order[k]].p;
						G = Girders[order[k]];
						k--;
					}
					
					// Sprawdzamy czy to rozwiązanie jest lepsze niż wcześniej znalezione
					currentDeliverCost = countCost(currentDeliverTime);
					G = Girders[order[0]];
					if (currentDeliverTime[order[0]] - G.z -G.t - G.r  >= 0 && currentDeliverCost < bestDeliverCost)
					{
						bestDeliverCost = currentDeliverCost;
						for (int k = 0; k <= i; k++)
							bestDeliverTime[k] = currentDeliverTime[k];
					}
//printf("Current: ");
//for (int m = 0; m < bestDeliverTime.size(); m++) printf("%lf ", currentDeliverTime[m]); printf("\n");
				}
			}
			// Kopiujemy najlepszy znaleziony jako najlepszy z danej iteracji
			for (int j = 0; j < Girders.size(); j++)
				lastIterationBestDeliverTime[j] = bestDeliverTime[j];
		}
//printf("Best: ");
//for (int j = 0; j < bestDeliverTime.size(); j++) printf("%lf ", lastIterationBestDeliverTime[j]); printf("\n");
	}
	return lastIterationBestDeliverTime;
}

vector<int> GirderSchedule::sortGirders(bool (*cmpfun)(pair<Girder,int>, pair<Girder,int>)){
	vector<pair<Girder,int> > tmp;
	vector<int> sorted;
	for(int i=0; i<this->number; i++){
		tmp.push_back(make_pair(this->Girders[i],i));
	}
	sort(tmp.begin(),tmp.end(),cmpfun);
	for(int i=0; i<this->number; i++){
			sorted.push_back(tmp[i].second);
		}
	return sorted;

}

vector<int> GirderSchedule::minDTime(){
	return this->sortGirders(Girder::cmpD);
}

vector<int> GirderSchedule::minETime(){
	return this->sortGirders(Girder::cmpE);
}

vector<int> GirderSchedule::minEDTime(){
	return this->sortGirders(Girder::cmpED);
}

void GirderSchedule::print() {
	for (int i = 0; i < this->number; i++) {
		this->Girders[i].print();
	}
}

