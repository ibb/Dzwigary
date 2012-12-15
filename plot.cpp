/*
 * plot.cpp
 *
 *  Created on: 15-12-2012
 *      Author: Izabela Biczysko, Krzysztof Piecuch
 */


#include <stdlib.h>
#include <string.h>
#include <karola.h>
#include "plot.hpp"

using namespace karola;

latexdoc& operator<<(latexdoc &ld, Statistic &d)
{
  ld << "\\begin{center}\n\\begin{tabular}{c}\n";
  ld << "\\begin{tikzpicture}[domain=0:1, scale=0.4]\n";

  ld << "\\foreach \\x/\\xtext in {2.5/" << double(d.n) / 4 << ", 5/" << double(d.n) / 2 << ", 7.5/" << 3 * double(d.n) / 4 << ", 10/" << double(d.n) << "}\n";
  ld << "\\draw[shift={(\\x,0)}] (0pt,2pt) -- (0pt,-2pt) node[below] {$\\xtext$};\n";

  ld << "\\foreach \\y/\\ytext in {2.5/" << double(d.max) / 4 << ", 5/" << double(d.max) / 2 << ", 7.5/" << 3 * double(d.max) / 4 << ", 10/" << double(d.max) << "}\n";
  ld << "\\draw[shift={(0,\\y)}] (2pt,0pt) -- (-2pt,0pt) node[left] {$\\ytext$};\n";

  ld << "\\draw[very thin,color=gray] (-0.1,-0.1) grid (10.9,10.9);\n";
  ld << "\\draw[->] (-0.2,0) -- (11.2,0) node[right] {$czas$};\n";
  ld << "\\draw[->] (0,-0.2) -- (0,11.2) node[above] {$wynik$};\n";

  ld << "\\draw[color = black!30!green, thick]\n";
  ld << "plot coordinates { ";
  for (int i = 0; i < d.n; i++)
    ld << "(" << float(i)*10/d.n << "," << float(d.best[i])/d.max*10 << ") ";
  ld << " };\n";

  ld << "\\draw[color = black!30!yellow, thick]\n";
  ld << "plot coordinates { ";
  for (int i = 0; i < d.n; i++)
    ld << "(" << float(i)*10/d.n << "," << float(d.average[i])/d.max*10 << ") ";
  ld << " };\n";

  ld << "\\draw[color = black!30!red, thick]\n";
  ld << "plot coordinates { ";
  for (int i = 0; i < d.n; i++)
    ld << "(" << float(i)*10/d.n << "," << float(d.worst[i])/d.max*10 << ") ";
  ld << " };\n";

  ld << "\\end{tikzpicture}\n";
  ld << "\n\\\\\n\n";
  ld << "population size = $" << d.populationSize << "$ \n\n\\\\\n\n";
  ld << "max iteration = $" << d.maxIteration << "$ \n\n\\\\\n\n";
  ld << "mutate rate = $" << d.mutateRate << "$ \n\n\\\\\n\n";
  ld << "initialisation = $" << d.initialisation << "$ \n\n\\\\\n\n";

  ld << "\\end{tabular}\n";
  ld << "\\end{center}\n";

  return ld;
}

void makePlot(Statistic d, const char* filename)
{
  latexdoc ld;
  ld.open(filename);

  ld << sf << d << ef;

  ld.close();
}
