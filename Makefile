CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

volimage: VolImage.o driver.o
	$(CC) $(CCFLAGS) VolImage.o driver.o -o volimage $(LIBS)

VolImage.o: VolImage.cpp VolImage.h
	$(CC) $(CCFLAGS) VolImage.cpp -c

driver.o: driver.cpp
	$(CC) $(CCFLAGS) driver.cpp -c

clean:
	rm -f *.o
	rm -f volimage
