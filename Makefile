# Output executable name
OUTPUT := possum

# Target to build (debug or release)
TARGET := debug

# Libraries to use
LIBS   := x11

# Compiler options
CC                := clang
override CFLAGS   += -std=c99 -pedantic -Wall -g -D_BSD_SOURCE -MMD $(shell pkg-config --cflags-only-other $(LIBS))
override INCLUDES += -Iinclude/ $(shell pkg-config --cflags-only-I $(LIBS))
override WARNINGS += -Wall -Wextra
override LDFLAGS  += $(shell pkg-config --libs $(LIBS))

# Target-specific flags
ifeq ($(TARGET),debug)
	override CFLAGS += -ggdb -O0 -DDEBUG
endif
ifneq ($(TARGET),release)
	override CFLAGS += -DDEVELOPMENT
endif

# Find all sources
SOURCES := $(shell find src/ -name '*.c')
OBJECTS := $(SOURCES:%.c=%.o)
DFILES  := $(SOURCES:%.c=%.d)

all: headers $(OUTPUT)
release: all

headers:
	$(shell ./generate_headers.sh)

$(OUTPUT): $(OBJECTS)
	@echo -e " [\033[32;1mLD\033[0m] $@"
	@$(CC) $(LDFLAGS) $^ -o $@

# Dependency files from -MMD
-include $(DFILES)

%.o: %.c
	@echo -e " [\033[34;1mCC\033[0m] $@"
	@$(CC) $(CFLAGS) $(INCLUDES) $(WARNINGS) -c $< -o $@

clean:
	@echo -e " [\033[31;1mRM\033[0m] $(OBJECTS)"
	@rm -f $(OBJECTS)
	@echo -e " [\033[31;1mRM\033[0m] $(DFILES)"
	@rm -f $(DFILES)
	@echo -e " [\033[31;1mRM\033[0m] $(OUTPUT)"
	@rm -f $(OUTPUT)
	@echo -e " [\033[31;1mRM\033[0m] $(shell find include/ -name '_*.h')"
	@rm -f $(shell find include/ -name '_*.h')

flags:
	@echo "CFLAGS:   $(CFLAGS)"
	@echo "INCLUDES: $(INCLUDES)"
	@echo "WARNINGS: $(WARNINGS)"
	@echo "LDFLAGS:  $(LDFLAGS)"

test: all
	./test.sh

debug: all
	./test.sh -v

.PHONY: all clean flags test debug headers

#CC=clang
#PREFIX?=/usr
#CFLAGS?=-std=c99 -Os -pedantic -Wall -g
#INCLUDES?=-I$(PREFIX)/include
#LIBS?=-L$(PREFIX)/lib -lX11
#SOURCES=$(

#compile:
#	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o possum possum.c core.c keys.c

#compile_debug:
#	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o possum possum.c core.c keys.c

#test: all
#	./test.sh

#debug: all
#	./test.sh -v

#clean:
#	rm -f possum

