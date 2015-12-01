CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++11

# rule for building .o from .cpp using dependencies
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

GAME_SRC=\
	src/vector.cpp src/vector.h\
	src/object.cpp src/object.h\
	src/component.cpp src/component.h\
	src/aicomponent.cpp src/aicomponent.h\
	src/aiworld.cpp src/aiworld.h\

GAME_CPP= $(filter %.cpp,$(GAME_SRC))
GAME_OBJ= $(GAME_CPP:.cpp=.o)

game: $(GAME_OBJ) $(GAME_SRC) $(GAME_CPP:.cpp=.d)
	$(CXX) $(CXXFLAGS) -o game $(GAME_OBJ)

clean:
	-find -name "*.o" -exec rm -f {} \;
	-find -name "*.d" -exec rm -f {} \;
	-rm -f game
