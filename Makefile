rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SOURCES=$(call rwildcard, ., *.cpp)
HEADERS=$(call rwildcard, ., *.hpp)
FLAGS=-g -std=gnu++2a -fconcepts -fopenmp

all: build run


build: $(SOURCES) $(HEADERS)
	gcc $(SOURCES) $(FLAGS) -o bin/application

run:
	bash bin/application
