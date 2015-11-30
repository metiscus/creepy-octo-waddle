CXX=gcc
CXXFLAGS=-g -Wall -Wextra -std=c++11

default:
	$(CXX) $(CXXFLAGS) -c src/vector.cpp
	$(CXX) $(CXXFLAGS) -c src/object.cpp
	$(CXX) $(CXXFLAGS) -c src/component.cpp
clean:
	-rm -f *.o
