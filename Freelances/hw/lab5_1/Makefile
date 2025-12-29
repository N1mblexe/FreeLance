# Makefile for C++ Programming Questions

# ANSI Color Codes (matching Color.h)
COLOR_RESET       = \033[0m
COLOR_BLACK       = \033[30m
COLOR_RED         = \033[31m
COLOR_GREEN       = \033[32m
COLOR_YELLOW      = \033[33m
COLOR_BLUE        = \033[34m
COLOR_MAGENTA     = \033[35m
COLOR_CYAN        = \033[36m
COLOR_WHITE       = \033[37m
COLOR_BRIGHT_RED  = \033[91m
COLOR_BRIGHT_GREEN= \033[92m
COLOR_BRIGHT_YELLOW= \033[93m
COLOR_BRIGHT_BLUE = \033[94m
COLOR_BRIGHT_CYAN = \033[96m
COLOR_BOLD        = \033[1m
COLOR_DIM         = \033[2m

# Semantic colors
COLOR_SUCCESS     = $(COLOR_BRIGHT_GREEN)
COLOR_ERROR       = $(COLOR_BRIGHT_RED)
COLOR_WARNING     = $(COLOR_YELLOW)
COLOR_INFO        = $(COLOR_CYAN)
COLOR_HEADER      = $(COLOR_BOLD)$(COLOR_BLUE)

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -Iinclude

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Dependencies
JSON_URL = https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp

# Target executable name
TARGET = $(BINDIR)/program

# Files/folders
COMPRESS_FILES = ./src/ ./include/ ./examples/

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Header files (include .h, .hpp, and .tpp)
HEADERS = $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*.tpp)

# Default target
all: deps $(BINDIR) $(OBJDIR) $(TARGET)

# Download dependencies
deps:
	@if [ ! -f include/json.hpp ]; then \
		echo -e "$(COLOR_YELLOW)Downloading nlohmann/json library...$(COLOR_RESET)"; \
		curl -L $(JSON_URL) -o include/json.hpp; \
		echo -e "$(COLOR_CYAN)Dependencies downloaded successfully!$(COLOR_RESET)"; \
	fi

# Create directories
$(BINDIR):
	@echo -e "$(COLOR_INFO)Creating directory: $(BINDIR)$(COLOR_RESET)"
	@mkdir -p $(BINDIR)

$(OBJDIR):
	@echo -e "$(COLOR_INFO)Creating directory: $(OBJDIR)$(COLOR_RESET)"
	@mkdir -p $(OBJDIR)

# Build the executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	@echo -e "$(COLOR_SUCCESS)Linking executable: $(TARGET)$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo -e "$(COLOR_BOLD)$(COLOR_GREEN)✓ Build successful!$(COLOR_RESET)"

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@echo -e "$(COLOR_INFO)Compiling: $(COLOR_RESET)$<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo -e "$(COLOR_WARNING)Cleaning build files...$(COLOR_RESET)"
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo -e "$(COLOR_SUCCESS)Clean complete!$(COLOR_RESET)"

# Run the program
# Usage: make run question=1 (or 2, 3, 4, all)
run: $(TARGET)
	@echo -e "$(COLOR_HEADER)Running program...$(COLOR_RESET)"
ifdef question
	@./$(TARGET) $(question)
else
	@./$(TARGET)
endif

# Debug build with additional flags
debug: CXXFLAGS += -DDEBUG -O0
debug: clean $(TARGET)

# Run the debug build
# Usage: make run-debug question=1 (or 2, 3, 4, all)
run-debug: debug
	@echo -e "$(COLOR_HEADER)Running debug build...$(COLOR_RESET)"
ifdef question
	@./$(TARGET) $(question)
else
	@./$(TARGET)
endif

# Launch GDB debugger
# Usage: make gdb question=1 (or 2, 3, 4, all)
gdb: debug
	@echo -e "$(COLOR_HEADER)Starting GDB debugger...$(COLOR_RESET)"
ifdef question
	@gdb --args ./$(TARGET) $(question)
else
	@gdb ./$(TARGET)
endif

# Run with Valgrind memory checker
# Usage: make valgrind question=1 (or 2, 3, 4, all)
valgrind: debug
	@echo -e "$(COLOR_HEADER)Running with Valgrind...$(COLOR_RESET)"
ifdef question
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) $(question)
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)
endif

# Compression and decompression
# Usage: make compress M=1 N=2
# Creates labM_N.tar.gz with src/ and include/ folders

compress:
ifndef M
	@echo -e "$(COLOR_ERROR)Error: M not specified$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Usage: make compress M=1 N=2$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Example: make compress M=1 N=2 creates lab1_2.tar.gz$(COLOR_RESET)"
	@exit 1
endif
ifndef N
	@echo -e "$(COLOR_ERROR)Error: N not specified$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Usage: make compress M=1 N=2$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Example: make compress M=1 N=2 creates lab1_2.tar.gz$(COLOR_RESET)"
	@exit 1
endif
	@echo -e "$(COLOR_INFO)Compressing $(COMPRESS_FILES)...$(COLOR_RESET)"
	@tar -czf lab$(M)_$(N).tar.gz $(COMPRESS_FILES)
	@echo -e "$(COLOR_SUCCESS)✓ Created archive: lab$(M)_$(N).tar.gz$(COLOR_RESET)"
	@ls -lh lab$(M)_$(N).tar.gz | awk '{print "  Size: " $$5}'

# Decompression
# Usage: make uncompress ARCHIVE=lab1_2.tar.gz
# Extracts to labM_N/ folder and moves Makefile there
uncompress:
ifndef ARCHIVE
	@echo -e "$(COLOR_ERROR)Error: ARCHIVE not specified$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Usage: make uncompress ARCHIVE=lab1_2.tar.gz$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Extracts to folder named after archive (e.g., lab1_2/)$(COLOR_RESET)"
	@exit 1
endif
	@echo -e "$(COLOR_INFO)Extracting archive to $(basename $(basename $(ARCHIVE)))/...$(COLOR_RESET)"
	@mkdir -p $(basename $(basename $(ARCHIVE)))
	@tar -xzf $(ARCHIVE) -C $(basename $(basename $(ARCHIVE)))
	@echo -e "$(COLOR_INFO)Moving Makefile into extracted directory...$(COLOR_RESET)"
	@mv Makefile $(basename $(basename $(ARCHIVE)))/Makefile
	@echo -e "$(COLOR_SUCCESS)✓ Extracted to: $(basename $(basename $(ARCHIVE)))/$(COLOR_RESET)"
	@echo -e "$(COLOR_SUCCESS)✓ Makefile moved to: $(basename $(basename $(ARCHIVE)))/Makefile$(COLOR_RESET)"
	@echo -e "$(COLOR_INFO)Contents:$(COLOR_RESET)"
	@ls -lh $(basename $(basename $(ARCHIVE)))
	@echo ""
	@echo -e "$(COLOR_BOLD)$(COLOR_CYAN)Now run: cd $(basename $(basename $(ARCHIVE)))/$(COLOR_RESET)"

# Show help
help:
	@echo -e "\n$(COLOR_BOLD)$(COLOR_CYAN)╔══════════════════════════════════════════════════════════════════════════╗$(COLOR_RESET)"
	@echo -e "$(COLOR_BOLD)$(COLOR_CYAN)║$(COLOR_RESET)           $(COLOR_BOLD)CSE 211 Graph Lab - Makefile Help$(COLOR_RESET)                   $(COLOR_BOLD)$(COLOR_CYAN)║$(COLOR_RESET)"
	@echo -e "$(COLOR_BOLD)$(COLOR_CYAN)╚══════════════════════════════════════════════════════════════════════════╝$(COLOR_RESET)\n"
	@echo -e "$(COLOR_BOLD)$(COLOR_BLUE)BUILD TARGETS$(COLOR_RESET)"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make" "Build the program"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make deps" "Download dependencies (nlohmann/json)"
	@printf "  $(COLOR_YELLOW)%-30s$(COLOR_RESET) %s\n" "make clean" "Clean build files"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make debug" "Build with debug flags (-DDEBUG -O0)"
	@echo ""
	@echo -e "$(COLOR_BOLD)$(COLOR_BLUE)RUN TARGETS$(COLOR_RESET)"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run" "Run all 20 question demos"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run question=1" "Q1: Mutual Friends Finder"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run question=2" "Q2: Celebrity Detection"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run question=3" "Q3: Triangle Counter"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run question=..." "Q4-Q20: See documentation"
	@printf "  $(COLOR_GREEN)%-30s$(COLOR_RESET) %s\n" "make run question=all" "Run all 20 demos"
	@echo ""
	@echo -e "$(COLOR_BOLD)$(COLOR_BLUE)DEBUG TARGETS$(COLOR_RESET)"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make run-debug" "Run debug build (with DEBUG prints)"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make run-debug question=1" "Run question 1 in debug mode"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make gdb" "Launch GDB interactive debugger"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make gdb question=1" "Debug question 1 with GDB"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make valgrind" "Run Valgrind memory checker"
	@printf "  $(COLOR_CYAN)%-30s$(COLOR_RESET) %s\n" "make valgrind question=1" "Check question 1 with Valgrind"
	@echo ""
	@echo -e "$(COLOR_BOLD)$(COLOR_BLUE)COMPRESSION TARGETS$(COLOR_RESET)"
	@printf "  $(COLOR_MAGENTA)%-30s$(COLOR_RESET) %s\n" "make compress M=1 N=2" "Create lab1_2.tar.gz archive"
	@printf "    $(COLOR_DIM)%-28s$(COLOR_RESET) %s\n" "" "→ Compresses src/ and include/ folders"
	@printf "  $(COLOR_MAGENTA)%-30s$(COLOR_RESET) %s\n" "make uncompress ARCHIVE=..." "Extract archive to folder"
	@printf "    $(COLOR_DIM)%-28s$(COLOR_RESET) %s\n" "" "→ Extracts and moves Makefile inside"
	@echo ""
	@echo -e "$(COLOR_DIM)Examples:$(COLOR_RESET)"
	@echo -e "  $(COLOR_DIM)make && make run question=1$(COLOR_RESET)"
	@echo -e "  $(COLOR_DIM)make gdb question=2$(COLOR_RESET)"
	@echo -e "  $(COLOR_DIM)make compress M=1 N=3$(COLOR_RESET)"
	@echo ""

# Declare phony targets
.PHONY: all clean run debug run-debug gdb valgrind help compress uncompress deps
