CC=gcc
PREFIX?=/usr
CFLAGS?=-Os -ansi -pedantic -Wall -g

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include -L$(PREFIX)/lib -lX11 -o possum possum.c core.c keys.c

clean:
	rm -f possum

