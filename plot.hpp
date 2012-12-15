/*
 * plot.h
 *
 *  Created on: 15-12-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */

#ifndef PLOT_HPP_
#define PLOT_HPP_


struct Statistic{
  int n;
  int max;

  int populationSize;
  int maxIteration;
  double mutateRate;
  char *initialisation;

  float best[10000];
  float worst[10000];
  float average[10000];
};

void makePlot(Statistic d, const char* filename);


#endif /* PLOT_HPP_ */
