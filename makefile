CC     = gcc
OBJS   = main.o \
         filosofo.o \
         mesa.o \
         semaphore.o

LIBS   = -lpthread
CFLAGS = 

all: filosofos

clean:
	rm -f $(OBJS)

filosofos: $(OBJS)
	$(CC) -Wall -s -o filosofos $(OBJS) $(LIBS)

main.o: main.c filosofo.h
	$(CC) -Wall -s -c main.c -o main.o $(CFLAGS)

filosofo.o: filosofo.c filosofo.h
	$(CC) -Wall -s -c filosofo.c -o filosofo.o $(CFLAGS)

mesa.o: mesa.c mesa.h
	$(CC) -Wall -s -c mesa.c -o mesa.o $(CFLAGS)


semaphore.o: semaphore.c semaphore.h
	$(CC) -Wall -s -c semaphore.c -o semaphore.o $(CFLAGS)

