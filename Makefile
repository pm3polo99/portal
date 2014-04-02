INC    = ./include
CFLAGS = -I $(INC)
LIB    = ./lib
LIBFNT = $(LIB)/libggfonts.so
LFLAGS = $(LIBFNT) -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
EFLAGS = -Wall -Wextra

all: log timing xwin lab1

log: $(INC)/log.c
	gcc $(CFLAGS) $(EFLAGS) -g -c -o $(LIB)/log.o $(INC)/log.c

timing: $(INC)/timing.c
	gcc $(CFLAGS) $(EFLAGS) -g -c -o $(LIB)/timing.o $(INC)/timing.c

xwin: $(INC)/xwin.c
	gcc $(CFLAGS) $(EFLAGS) -g -c -o $(LIB)/xwin.o $(INC)/xwin.c

lab1: lab1.c $(LIB)/log.o $(LIB)/xwin.o $(LIB)/timing.o
	gcc $(CFLAGS) $(EFLAGS) $(LFLAGS) -g lab1.c $(LIB)/log.o $(LIB)/xwin.o $(LIB)/timing.o

clean:
	rm -f lab1 *.o core

