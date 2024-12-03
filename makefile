CC = gcc
LD = gcc
CFLAGS = -Wall -O2
LDFLAGS = -g
all : printrandom
printrandom : mtwister.o mt.o linear.o main.o
	$(CC) $(CFLAGS) mtwister.o mt.o linear.o main.o -o printrandom $(LDFLAGS) -rdynamic
main.o : main.c
	$(CC) $(CFLAGS) -c main.c
mtwister.o : mtwister.c 
	$(CC) $(CFLAGS) -c mtwister.c 
mt.o : mt.c random_source.h
	$(CC) $(CFLAGS) -c mt.c
linear.o : linear.c random_source.h
	$(CC) $(CFLAGS) -c linear.c

clean :
	rm -f *.o
	

