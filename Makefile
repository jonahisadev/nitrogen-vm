CC = g++
LDFLAGS =
CFLAGS = -I include -g -c -std=c++11 -I native -ldl
SRC = $(wildcard *.cpp src/*.cpp)
HEAD = $(wildcard include/Nitrogen/*.h)
OBJ = $(SRC:.cpp=.o)
C_OBJ = $(C_SRC:.c=.o)
EXEC = nvmc

all: $(OBJ) $(EXEC) $(HEAD) $(C_OBJ)
	
release: CFLAGS += -O3
release: all

linux: LDFLAGS += -ldl
linux: CFLAGS += -DLINUX
linux: release

$(EXEC): $(OBJ) $(C_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.nc src/*.o $(EXEC) .symdat