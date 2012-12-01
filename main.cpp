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

#include "GirderSchedule.hpp"
#include "randUtils.hpp"
#include "Population.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 2)
		cout << "usage: " << argv[0] << " <filename>\n";
	else {
		srand(time(NULL));
		GirderSchedule *GS = new GirderSchedule(argv[1]);

		Environment *env = new Environment(GS, 6, 100, 0.1);
		env->run();

	}

	return 0;
}

