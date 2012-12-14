#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct dzwigar
{
  double z; // czas załadunku
  double t; // czas transportu na czas budowy
  double r; // czas rozładunku na placu budowy
  double p; // czas powrotu
  double e; // żądany najwcześniejszy termin przywozu
  double d; // żądany najpóźniejszy termin przywozu
  double v; // wsp. f. kary za zbyt wczesne przybycie
  double w; // wsp. f. kary za zbyt późne przybycie
} tab[1000]; // Ustaliłem na 1000 bo przy 1000 już mój algorytm n^3 nie ścierpi...

inline void zero(int N)
{
  // Ustawiaj losowo z, t, r oraz p
  for (int i = 0; i < N; i++)
  {
    tab[i].z = (10.0 * rand()) / RAND_MAX;
    tab[i].t = (10.0 * rand()) / RAND_MAX;
    tab[i].r = (10.0 * rand()) / RAND_MAX;
    tab[i].p = (10.0 * rand()) / RAND_MAX;
  }
  
  double time = 0.0;
  
  // Ustawiamy tak czas, aby porządek 1, 2, 3... był dobrym porządkiem
  for (int i = 0; i < N; i++)
  {
    time += tab[i].z + tab[i].t + tab[i].r;
    
    // Od
    if (rand() % 3 == 0)
      // dokładny czas
      tab[i].e = time;
    else if (rand() % 2 == 0)
      // mniej więcej czas
      tab[i].e = max(time - (1.0 * rand()) / RAND_MAX, 0.0);
    else
      // w ogóle nie ten czas
      tab[i].e = max(time - (10.0 * rand()) / RAND_MAX, 0.0);
    
    // Do
    if (rand() % 3 == 0)
      // dokładny czas
      tab[i].d = time;
    else if (rand() % 2 == 0)
      // mniej więcej czas
      tab[i].d = time + (1.0 * rand()) / RAND_MAX;
    else
      // w ogóle nie ten czas
      tab[i].d = time + (100.0 * rand()) / RAND_MAX;
    
    time += tab[i].p;
  }
  
  // Kary
  for (int i = 0; i < N; i++)
  {
    tab[i].v = (10.0 * rand()) / RAND_MAX;
    tab[i].w = (10.0 * rand()) / RAND_MAX;
  }
}

inline void fullrandom(int N)
{
  double time;
  // Ustawiaj losowo z, t, r oraz p
  for (int i = 0; i < N; i++)
  {
    tab[i].z = (10.0 * rand()) / RAND_MAX;
    tab[i].t = (10.0 * rand()) / RAND_MAX;
    tab[i].r = (10.0 * rand()) / RAND_MAX;
    tab[i].p = (10.0 * rand()) / RAND_MAX;
    
    time = (40.0 * rand()) / RAND_MAX + 30.0;
    
    tab[i].e = max(time - (40.0 * rand()) / RAND_MAX, 0.0);
    tab[i].d = time + (40.0 * rand()) / RAND_MAX;
    
    tab[i].v = (10.0 * rand()) / RAND_MAX;
    tab[i].w = (10.0 * rand()) / RAND_MAX;
  }
}

inline void counterexample(int N)
{
  for (int i = 0; i < N; i++)
  {
    tab[i].z = 1;
    tab[i].t = 1;
    tab[i].r = 1;
    tab[i].p = 1;
    
    tab[i].e = 0.001 * (i+1);
    tab[i].d = 0.001 * (i+1);
    
    tab[i].v = 0.1;
    tab[i].w = 0.1 * (i+1) * i;
  }
}

inline void print(int wybor, int N)
{
  FILE *fout;
  char filename[40];
  
  sprintf(filename, "test_%d_%d.in", wybor, N);
  fout = fopen(filename, "w");
  
  if (fout == NULL)
  {
    printf("Cholera, coś poszło źle.\n");
    return;
  }
  
  fprintf(fout, "%d\n", N);
  for (int i = 0; i < N; i++)
  {
    fprintf(fout, "%.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n", tab[i].z, tab[i].t, tab[i].r, tab[i].p, tab[i].e, tab[i].d, tab[i].v, tab[i].w); 
  }
  
  fclose(fout);
}

inline void random(int N)
{
  for (register int i = N-1; i >= 0; i--)
    swap(tab[i], tab[rand() % (i+1)]);
}

int main(void)
{
  int N;
  int wybor;
  
  srand((unsigned)time(NULL));
  
  while (true)
  {
    printf("Generator dźwigarów\n");
    printf("1 - dźwigary zero\n");
    printf("2 - pełen random\n");
    printf("3 - kontrprzykład\n");
    printf("0 - wyjście\n");
    
    printf("Twój wybór: ");
    scanf("%d", &wybor);

    if (wybor == 0)
      return 0;
    if (wybor == 1)
      printf("\nGeneruje dźwigary, które można wykonać w taki sposób, aby nie zapłacić żadnej kary.\n");
    if (wybor == 2)
      printf("\nGeneruje w pełni losowy zestaw dźwigarów (czasy są tak dobierane, aby okna nie były zbyt duże)\n");
    if (wybor == 3)
      printf("\nGeneruje zestaw danych, który jest kontrprzykładem do naszych ustawień początkowych\n");
    
    printf("Podaj ilość dźwigarów: ");
    scanf("%d", &N);
    
    if (wybor == 1)
      zero(N);
    if (wybor == 2)
      fullrandom(N);
    if (wybor == 3)
      counterexample(N);
    
    random(N);
    print(wybor, N);
  }
  return 0;
}
