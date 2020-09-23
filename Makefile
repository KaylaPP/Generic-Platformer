CXX=g++
CFLAGS=-c -g -pthread -pedantic -std=c++17 -Wall
LDFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs
EXECUTABLE=./Generic-Platformer.out
SRCDIR=./src
BINDIR=./bin

SOURCES=$(wildcard ${SRCDIR}/*.cpp)

OBJECTS=$(SOURCES:${SRCDIR}/%.cpp=$(BINDIR)/%.o)

all : $(EXECUTABLE)

$(EXECUTABLE) : ${OBJECTS}
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean : 
	rm -r $(BINDIR)/*.o $(EXECUTABLE)

run : all
	$(EXECUTABLE)
