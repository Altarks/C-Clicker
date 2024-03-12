#The compiler
CC:=gcc
#The flags passed to the compiler
CFLAGS:=-g -Ofast -Wall -Wextra -fsanitize=address -fsanitize=leak -std=gnu11
#The flags passed to the linker
LDFLAGS:=-lm -lX11 
#Path to the lib
VPATH:=gfx


main: main.o gfx.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

gfx.o: gfx.h

clean:
	rm -f *.o main save.txt
