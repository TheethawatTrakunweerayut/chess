CC := g++

SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGET := main

SFML_INCLUDE_PATH := /opt/homebrew/Cellar/sfml/2.5.1_2/include
SFML_LIB_PATH := /opt/homebrew/Cellar/sfml/2.5.1_2/lib
SOURCES := $(SRCDIR)/*.cpp
OBJECTS := *.o

all: compile link clean

compile:
	$(CC) -c $(SOURCES) -I$(INCDIR) -I $(SFML_INCLUDE_PATH) -std=c++17 -Wall -Wextra
link:
	$(CC) $(OBJECTS) -o $(TARGET) -L $(SFML_LIB_PATH) -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm $(OBJECTS)

