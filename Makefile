INC    = /usr/include
LOCINC = ./include
CFLAGS = -I $(INC) -I $(LOCINC) -g -O2
LIB    = ./lib
LIBFNT = $(LIB)/libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
EFLAGS = -Wall -Wextra

all: log timing xwin objects lab1

objects: $(LOCINC)/objects.cpp
	g++ $(LOCINC)/objects.cpp $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/objects.o

log: $(LOCINC)/log.c
	g++ $(LOCINC)/log.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/log.o

timing: $(LOCINC)/timing.c
	g++ $(LOCINC)/timing.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/timing.o

xwin: $(LOCINC)/xwin.c
	g++ $(LOCINC)/xwin.c $(CFLAGS) $(EFLAGS) $(LFLAGS) -c -o $(LIB)/xwin.o

lab1: lab1.cpp $(LIB)/log.o $(LIB)/xwin.o $(LIB)/timing.o $(LIB)/objects.o $(LIBFNT)
	g++ $(LIB)/*.o lab1.cpp $(LIBFNT) $(CFLAGS) $(EFLAGS) $(LFLAGS)

clean:
	rm -f a.out *.o *.gch core *.log $(LIB)/*.o $(LOCINC)/*.o $(LOCINC)/*.gch

