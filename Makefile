SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))

INCLUDE_PATH := include/

CC_FLAGS := -std=c++11 -I $(INCLUDE_PATH)
LD_FLAGS :=

UniversalSceneryWall : $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

PHONY: clean
clean:
	-rm obj/*
	-rm UniversalSceneryWall
	-rm output/*

