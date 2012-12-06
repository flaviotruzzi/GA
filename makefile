CC      = g++ -pg -O3
CFLAGS  = 
LDFLAGS = 

all: GA

GA: main.o util.o
	$(CC) -o GA main.o util.o

main.o: main.cpp
	$(CC) -c $(CFLAGS) $<

util.o: util.cpp util.h
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm -vf *.o
	rm GA

cleanest: clean
	rm GA