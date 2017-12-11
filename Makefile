CC = g++
LDFLAGS =
CFLAGS = -I include -g -c -std=c++11 -I native
SRC = $(wildcard *.cpp src/*.cpp)
HEAD = $(wildcard include/Nitrogen/*.h)
OBJ = $(SRC:.cpp=.o)
C_OBJ = $(C_SRC:.c=.o)
EXEC = nvmc

all: $(OBJ) $(EXEC) $(HEAD) $(C_OBJ)
	
release: CFLAGS += -O3
release: all

$(EXEC): $(OBJ) $(C_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.nc src/*.o $(EXEC) .symdat