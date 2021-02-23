CC=g++
CFLAGS= -std=c++17 -fopenmp
OBJFILES = parallelPrimeTwins.o

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o
	$(CC) -o parallelPrimeTwins parallelPrimeTwins.cpp $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG -Wall
DEBUG: ALL

doc: 
	doxygen Doxyfile
#this is customary and just deletes all .o files
CLEAN:
	rm *.o

	# sequencialPrime
	# parallelPrime
	#-pthread