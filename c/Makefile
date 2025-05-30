# Compiler and flags
# ===========================================
# OPTIONAL: Top performance compilation tips
# -------------------------------------------
# If you want maximum optimization for your own machine, 
# uncomment the following flags:
#
# CFLAGS += -O3 -march=native -flto
#
# -O3          : High-level optimizations
# -march=native: Target current machine's CPU features (AVX, AVX2, etc.)
# -flto        : Link Time Optimization (LTO) for better binary optimization
#
# Warning: -march=native makes binaries machine-specific (not portable).
# ===========================================

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -MMD -MP

# Source files
SRC = ${wildcard src/array/*.c} \
      $(wildcard src/hardware/*.c) \
      $(wildcard src/runtime/*.c) \

# Test files (main() lives here)
TEST_SRC = $(wildcard test/hardware/*.c) 
# TEST_SRC = $(wildcard test/array/*.c)

# Objects
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Target binary
TARGET = bin/test_static_array

# Default rule
all: $(TARGET)
	./$(TARGET)   

# How to link the final executable
$(TARGET): $(OBJ) $(TEST_OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(TEST_OBJ) -lm

# How to compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf src/**/*.o src/**/*.d test/**/*.o test/**/*.d bin/

-include $(OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)
