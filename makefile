CXX=g++
CXXFLAGS=-g -Wall -Wextra -Wshadow -std=c++11 -Iextern/glad/include -Iextern -L.

# rule for building .o from .cpp using dependencies
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

SDL_CFLAGS=`pkg-config --cflags sdl2`
SDL_LDFLAGS=`pkg-config --libs sdl2`
CXXFLAGS += $(SDL_CFLAGS)

default: game

libglad.a:
	gcc -Iextern/glad/include -g -Wall -Wextra -c -o extern/glad/src/glad.o extern/glad/src/glad.c
	ar -rcs libglad.a extern/glad/src/glad.o

GAME_SRC=\
	src/main.cpp\
	src/componentcontainer.h\
	src/vector.cpp src/vector.h\
	src/object.cpp src/object.h\
	src/component.cpp src/component.h\
	src/aicomponent.cpp src/aicomponent.h\
	src/aiworld.cpp src/aiworld.h\
	src/render.cpp src/render.h\
	src/rendercomponent.cpp src/rendercomponent.h\
	src/drawable.cpp src/drawable.h\

GAME_CPP= $(filter %.cpp,$(GAME_SRC))
GAME_OBJ= $(GAME_CPP:.cpp=.o)

game: $(GAME_OBJ) $(GAME_SRC) $(GAME_CPP:.cpp=.d) libglad.a
	$(CXX) $(CXXFLAGS) -o game $(GAME_OBJ) $(SDL_LDFLAGS) -lglad -ldl

clean:
	-find -name "*.o" -exec rm -f {} \;
	-find -name "*.d" -exec rm -f {} \;
	-rm -f game libglad.a
