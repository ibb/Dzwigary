main: randUtils.o Population.o Individual.o GirderSchedule.o Environment.o
	g++ randUtils.o Population.o Individual.o GirderSchedule.o Environment.o -o main main.cpp

randUtils.o:
	g++ -c -o randUtils.o randUtils.cpp

GirderSchedule.o:
	g++ -c -o GirderSchedule.o GirderSchedule.cpp

Environment.o: GirderSchedule.o
	g++ -c -o Environment.o Environment.cpp

Individual.o: Environment.o
	g++ -c -o Individual.o Individual.cpp

Population.o: Individual.o
	g++ -c -o Population.o Population.cpp

clean:
	rm *.o main