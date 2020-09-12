CC     = gcc
OBJS   = main.o \
         filosofo.o \
         mesa.o

LIBS   = -L"$(MINGW_PATH)\lib" -lpthread
CFLAGS = -I"$(MINGW_PATH)\include"

all: clean-before build clean-after

clean-before:
	rm -f $(OBJS)

clean-after:
	rm -f $(OBJS)

build: $(OBJS)
	$(CC) -Wall -s -o Filosofos_Comiloes.exe $(OBJS) $(LIBS)

main.o: main.c filosofo.h
	$(CC) -Wall -s -c main.c -o main.o $(CFLAGS)

filosofo.o: filosofo.c filosofo.h
	$(CC) -Wall -s -c filosofo.c -o filosofo.o $(CFLAGS)

mesa.o: mesa.c mesa.h
	$(CC) -Wall -s -c mesa.c -o mesa.o $(CFLAGS)

