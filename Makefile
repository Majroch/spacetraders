CXX = g++
CXXFLAGS_IMPORTANT = -Wall -lcurl
RM = rm -rf
PREFIX = /usr/bin
PROGRAM_NAME = spacetraders
LIBS = util.o

all: $(LIBS)
	$(CXX) $(CXXFLAGS_IMPORTANT) spacetraders.cpp $(LIBS) -o spacetraders $(CXXFLAGS) $(CXXLIBS)

util.o:
	$(CXX) $(CXXFLAGS_IMPORTANT) -c ./libs/util.cpp -o util.o
    
clean:
	$(RM) $(LIBS) $(PROGRAM_NAME)
