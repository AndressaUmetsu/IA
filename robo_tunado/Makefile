CC=g++
CFLAGS=-c -Wall --std=c++11
CFLAGSL=-lpthread
LDFLAGS=

SOURCES=main.cpp a_star.cpp map.cpp

OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=magic

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	    $(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(CFLAGSL)

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@ $(CFLAGSL)
