GCC = gcc
CFLAGS = -g -Wall -Wshadow

pa06: pa06.o answer06.o
	$(GCC) $(CFLAGS) pa06.o answer06.o -o pa06

pa06.o: pa06.c pa06.h
	$(GCC) $(CFLAGS) -c pa06.c #create pa06.o

answer06.o: answer06.c pa06.h
	$(GCC) $(CFLAGS) -c answer06.c #create answer06.o

