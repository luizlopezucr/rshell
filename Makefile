CXX = g++
BIN = bin
OUT_PATH = ../bin/rshell
SRC_PATH = src
FILES = main.cpp
CXXFLAGS = -Wall -Werror -ansi -pedantic

all:
		cd $(SRC_PATH) ; $(CXX) $(CXXFLAGS) $(FILES) -o $(OUT_PATH)

rshell:
		cd $(SRC_PATH) ; $(CXX) $(CXXFLAGS) $(FILES) -o $(OUT_PATH)

clean:
		rm -rf $(OUT_PATH)
