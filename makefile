CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

# Edit the following SOURCES variable to include all of the .cpp files to compile
SOURCES = main.cpp OS_Sim.cpp ReadyQueue.cpp RAM.cpp LRUCache.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = OS_Sim

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
