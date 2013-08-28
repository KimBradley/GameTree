compile:
	g++ -Wall -g GameNode.h t3solver.cpp -o Solver
run:
	./Solver

clean:
	rm Solver

debug:
	valgrind --track-origins=yes ./Solver
all:
	make clean
	make compile
	make run