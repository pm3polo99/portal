INC    = /usr/include
LOCINC = ./include
CFLAGS = -I $(INC) -I $(LOCINC) -g -O2
LIB    = ./lib
LIBFNT = $(LIB)/libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
EFLAGS = -Wall -Wextra

all: log timing xwin shapes lab1

log: $(LOCINC)/log.c
	gcc $(LOCINC)/log.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/log.o

timing: $(LOCINC)/timing.c
	gcc $(LOCINC)/timing.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/timing.o

xwin: $(LOCINC)/xwin.c
	gcc $(LOCINC)/xwin.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/xwin.o

shapes: $(LOCINC)/shapes.c
	gcc $(LOCINC)/shapes.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/shapes.o

lab1: lab1.c $(LIB)/log.o $(LIB)/xwin.o $(LIB)/timing.o $(LIB)/shapes.o
	gcc $(LIB)/*.o lab1.c $(CFLAGS) $(EFLAGS) $(LFLAGS) $(LIBFNT)

clean:
	rm -f a.out *.o core *.log $(LIB)/*.o

