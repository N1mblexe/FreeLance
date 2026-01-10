
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -O2 -MMD -MP

SRC := $(shell find src -name '*.cpp')
OBJ := $(patsubst %.cpp,%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

.PHONY: all clean test

all: roster

roster: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: all
	@echo "Built roster binary (no test runner configured)"

clean:
	rm -f roster $(OBJ) $(DEPS)

