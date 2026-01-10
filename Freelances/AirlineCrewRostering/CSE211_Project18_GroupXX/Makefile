
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Wextra -Werror -O2 -MMD -MP

BUILD_DIR := build
SRC := $(shell find src -name '*.cpp')
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

.PHONY: all clean test

all: roster

roster: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

test-pq:
	mkdir -p $(BUILD_DIR)/tests
	$(CXX) $(CXXFLAGS) -Iinclude tests/test_priority_queue.cpp src/data_structures/PriorityQueue.cpp src/data_structures/LinkedList.cpp src/models/Crew.cpp src/models/Pairing.cpp src/models/Flight.cpp -o $(BUILD_DIR)/tests/test_priority_queue
	$(BUILD_DIR)/tests/test_priority_queue


-include $(DEPS)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: all
	@echo "Built roster binary (no test runner configured)"

clean:
	rm -f roster
	rm -rf $(BUILD_DIR)

