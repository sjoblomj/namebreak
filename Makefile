ifndef VALIDATE
CFLAGS = -O3 -pedantic -Wall -Wextra
else
# To compile in Validation mode: make VALIDATE=1471
$(info Will compile in validation mode.)
CFLAGS = -O3 -pedantic -Wall -Wextra -DVALIDATE=$(VALIDATE)
endif


CC = g++
LDFLAGS = -lcurl
SOURCES = namebreak.cpp portrait_upper.cpp portrait_medium.cpp lowrange.cpp constants.cpp utils.cpp network.cpp
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

# To make the launcher: make launcher PASS=password
launcher:
ifndef PASS
	$(error Password not provided)
endif
	$(CC) -o $@ $@.cpp -DPASS="\"$(PASS)\""
