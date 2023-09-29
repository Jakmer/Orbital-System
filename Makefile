# Compiler and flags
CC = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = main.cpp GravitySource.cpp Particle.cpp

# Header files
HEADERS = Parameters.h GravitySource.h Particle.h

# Output executable
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

clean:
	rm -f $(TARGET)
