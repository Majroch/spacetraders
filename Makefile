CXX = g++
CXXFLAGS_IMPORTANT = -Wall -lcurl -ljsoncpp
RM = rm -rf
PREFIX = /usr/bin
PROGRAM_NAME = spacetraders
LIBS = util.o user.o

all: $(LIBS)
	$(CXX) $(CXXFLAGS_IMPORTANT) spacetraders.cpp $(LIBS) -o spacetraders $(CXXFLAGS) $(CXXLIBS)

util.o:
	$(CXX) $(CXXFLAGS_IMPORTANT) -c ./libs/util.cpp -o util.o

user.o:
	$(CXX) $(CXXFLAGS_IMPORTANT) -c ./classes/user.cpp -o user.o

clean:
	$(RM) $(LIBS) $(PROGRAM_NAME)
