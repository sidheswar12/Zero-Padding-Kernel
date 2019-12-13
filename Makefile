CXX :=g++ -std=c++11 -pthread
SRCS :=src/main.cpp src/pixelsum.cpp src/readimage.cpp
INC :=include/pixelsum.h include/readimage.h
OBJ :=build
all:
	rm -rf $(OBJ)
	mkdir build
	$(CXX) $(SRCS) $(INC) -o $(OBJ)/pixsum

