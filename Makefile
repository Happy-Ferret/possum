PREFIX?=/usr
CFLAGS?=-Os -pedantic -Wall -g

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include -L$(PREFIX)/lib -lX11 -o possum possum.c

clean:
	rm -f possum

