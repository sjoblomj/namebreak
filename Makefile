CC = g++
CFLAGS = -O3 -pedantic -Wall -Wextra
LDFLAGS = -lcurl
SOURCES = namebreak.cpp portrait_fast.cpp portrait_slow.cpp general.cpp constants.cpp network.cpp utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = namebreak

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY=clean

clean:
	rm *.o

# To make the launcher:
launcher:
ifndef PASS
	$(error Password not provided)
endif
	$(CC) -o $@ $@.cpp -DPASS="\"$(PASS)\""

