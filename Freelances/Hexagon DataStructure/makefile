# Hexagon Priority Queue Simulation Makefile

SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(LIB_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/hexagon_sim.exe

CXX = g++
CXXFLAGS = -I$(INC_DIR) -Wall -O2

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LIB_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/*.o $(TARGET)

.PHONY: all clean
