CFLAGS = -std=c++11

main: parse.o TextCalculator.o
	g++ parse.o TextCalculator.o -o main ${CFLAGS}

parse.o: parse.cpp TextCalculator.h
	g++ -c parse.cpp ${CFLAGS}

TextCalculator.o: TextCalculator.cpp TextCalculator.h
	g++ -c TextCalculator.cpp ${CFLAGS}

clean:
	rm *.o
