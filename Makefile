CC=gcc
PREFIX?=/usr
CFLAGS?=-std=c99 -Os -pedantic -Wall -g

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include -L$(PREFIX)/lib -lX11 -o possum possum.c core.c keys.c

test: all
	$(shell ./test.sh)

clean:
	rm -f possum

