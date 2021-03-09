CXX = g++
CXXFLAGS_IMPORTANT = -Wall -static -static-libgcc -pthread
RM = rm -rf
PREFIX = /usr/bin
PROGRAM_NAME = spacetraders
PROGRAM_BUILD_DIR = build

all: #build-folder
	$(CXX) $(CXXFLAGS_IMPORTANT) spacetraders.cpp -o spacetraders $(CXXFLAGS) $(CXXLIBS)
    
build-folder:
	mkdir -p $(PROGRAM_BUILD_DIR)

clean:
	$(RM) $(PROGRAM_NAME) $(PROGRAM_BUILD_DIR)
