.ONESHELL: 

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES=$(call rwildcard, src, *.cpp)
HEADERS=$(call rwildcard, src, *.hpp)
FLAGS=-g -lstdc++ -std=gnu++2b -fopenmp

all: build read-la01.txt

build: $(SOURCES) $(HEADERS)
	gcc-11 $(SOURCES) $(FLAGS) -o bin/solver

read-la01.txt:
	cd ./bin
	./solver la01.txt
