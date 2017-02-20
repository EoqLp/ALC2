CC=gcc
LDIR=../
CFLAGS=-L$(LDIR) -I$(LDIR)
LDFLAGS="-Wl,-rpath,../"
LIBS=-lmatrizlib -lm

main: main.c
	$(CC) $(LDFLAGS) main.c -o main $(CFLAGS) $(LIBS) 
