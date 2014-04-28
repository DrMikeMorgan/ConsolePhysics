CXX = g++
CXXFLAGS = -fpermissive
LDFLAGS = -lncurses

OBJ =  main.o graphics.o physics.o

all: thing

physics.o: physics.cpp
	$(CXX) -c $< $(CXXFLAGS)
graphics.o: graphics.cpp physics.o
	$(CXX) -c $< $(CXXFLAGS)
main.o: main.cpp graphics.o
	$(CXX) -c $< $(CXXFLAGS)
thing: main.o
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) 

clean: 
	rm -rf *o thing
