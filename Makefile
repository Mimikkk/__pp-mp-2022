.ONESHELL: 

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
MP_SOURCES=$(call rwildcard, src, *.cpp)
MP_HEADERS=$(call rwildcard, src, *.hpp)
MP_FLAGS=-g -lstdc++ -lm -std=gnu++2b -fopenmp

mp: mp-build mp-run

mp-build: $(MP_SOURCES) $(MP_HEADERS)
	gcc $(MP_SOURCES) $(MP_FLAGS) -o bin/solver-mp

mp-run:
	cd ./bin
	./solver-mp $(instance)

mp-run-abz5:
	mp-run instance=abz5.txt

all: cuda

clean: 
	cd ./bin
	rm solver-mp
	rm solver-cuda	

CUDA_FILES=$(call rwildcard, src, *.cu)
CUDA_SOURCES=$(call rwildcard, src, *.cpp)
CUDA_HEADERS=$(call rwildcard, src, *.hpp)
CUDA_FLAGS=-g -lstdc++ -lm -std=c++17 -arch=sm_70 -D cuda 

cuda: cuda-build cuda-run

cuda-build: $(CUDA_SOURCES) $(CUDA_HEADERS) $(CUDA_FILES)
	/usr/local/cuda-11.7/bin/nvcc $(CUDA_FILES) $(CUDA_SOURCES) $(CUDA_FLAGS) -D cuda -o ./bin/solver-cuda

cuda-run:
	cd ./bin
	./solver-cuda $(instance)

cuda-run-abz5:
	cuda-run instance=abz5.txt
