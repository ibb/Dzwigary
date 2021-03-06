/*
 * evolution.cpp
 *
 *  Created on: 29-11-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cstring>

#include "GirderSchedule.hpp"
#include "randUtils.hpp"
#include "Population.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 2)
		cout << "usage: " << argv[0] << " <filename>\n";
	else
	{
		if (!strcmp("debugmode", argv[1]))
		{
			vector<int> O;
			GirderSchedule GS("In/1.in");
			
			for (int i = 0; i < 4; i++)
				O.push_back(i);
			
			GS.findDeliverTime(O);
		}
		else
		{
			srand(time(NULL));
			GirderSchedule *GS = new GirderSchedule(argv[1]);

			Environment *env = new Environment(GS, 100, 10000, 0.1, SPECIALIND, 0.1, 100);
			//env->random(100000);
			env->run();
		}
	}

	return 0;
}

