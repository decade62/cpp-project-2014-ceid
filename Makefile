sim: robot.o point.o sim.o
	g++ -Wall -o sim sim.o point.o robot.o -lcurses
	
robot.o: robot.cpp robot.h
	g++ -Wall -c robot.cpp
	
point.o: point.cpp point.h
	g++ -Wall -c point.cpp
	
sim.o: sim.cpp sim.h
	g++ -Wall -c sim.cpp
	
		
clean:
	rm -f *.o sim
