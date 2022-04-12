.ONESHELL: 

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES=$(call rwildcard, src, *.cpp)
HEADERS=$(call rwildcard, src, *.hpp)
FLAGS=-g -lstdc++ -std=gnu++2a -fconcepts -fopenmp

all: build read-abz5.txt


build: $(SOURCES) $(HEADERS)
	gcc $(SOURCES) $(FLAGS) -o bin/solver

read-abz5.txt:
	cd ./bin
	./solver abz5.txt
