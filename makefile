CXX=g++
LD=g++
CXXFLAGS=-g -Wall -Wextra -Wshadow -std=c++11 -Iextern/glad/include -Iextern -L. -DBOOST_ALL_DYN_LINK
LDFLAGS=-pthread -lboost_system -lboost_filesystem -lboost_log

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM -MD -MT "$*.o" $(CXXFLAGS) $*.cpp -o $*.d

SDL_CFLAGS=$(shell pkg-config --cflags sdl2)
SDL_LDFLAGS=$(shell pkg-config --libs sdl2)
CXXFLAGS += $(SDL_CFLAGS)
LDFLAGS += $(SDL_LDFLAGS)

default: game

libglad.a:
	gcc -Iextern/glad/include -g -Wall -Wextra -c -o extern/glad/src/glad.o extern/glad/src/glad.c
	ar -rcs libglad.a extern/glad/src/glad.o

GAME_SRC=\
	src/global.cpp\
	src/main.cpp\
	src/vector.cpp\
	src/object.cpp\
	src/component.cpp\
	src/aicomponent.cpp\
	src/aiworld.cpp\
	src/render.cpp\
	src/rendercomponent.cpp\
	src/drawable.cpp\
	src/log.cpp\
	src/physicscomponent.cpp\
	src/resourcemanager.cpp\
	src/render/camera.cpp\
	src/render/program.cpp\
	src/render/sampler.cpp\
	src/render/shader.cpp\
	src/render/texture.cpp\
	src/render/texturedata.cpp\
	src/render/uniform.cpp\
	src/render/vbo.cpp\
	src/map/layer.cpp\
	src/map/map.cpp\
	src/map/tileset.cpp\
	

GAME_CPP= $(filter %.cpp,$(GAME_SRC))
GAME_OBJ= $(GAME_CPP:.cpp=.o)

-include $(GAME_OBJ:.o=.d)

src/global.h.gch: src/global.h
	$(CXX) $(CXXFLAGS) -c src/global.h -o src/global.h.gch

game: src/global.h.gch $(GAME_OBJ) $(GAME_SRC) libglad.a
	$(LD) $(CXXFLAGS) -o game $(GAME_OBJ) $(LDFLAGS) -lglad -ldl

clean:
	-rm src/global.h.gch
	-find -name "*.o" -exec rm -f {} \;
	-find -name "*.d" -exec rm -f {} \;
	-rm -f game libglad.a
