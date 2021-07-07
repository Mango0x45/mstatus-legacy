target	= mstatus
cfiles	= $(wildcard src/*.c) $(wildcard src/modules/*.c)
hfiles	= $(wildcard src/*.h)
ofiles	= $(cfiles:.c=.o)

BIN	= bin/
CC	= cc
CFLAGS	= -Ofast -pipe -march=native -mtune=native -I src/ -pedantic -Wall -Wextra \
	  -Wmissing-prototypes -Wstrict-prototypes -Wunused-result
LIBS	= -lX11
PREFIX	= /usr/local

all: $(BIN)$(target)

$(BIN)$(target): $(ofiles) $(hfiles)
	@mkdir -p $(BIN)
	$(CC) $(LIBS) -o $@ $(ofiles)

src/%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean format install uninstall
clean:
	rm -rf $(BIN) src/*.o src/modules/*.o

format:
	clang-format -i -style=file $(cfiles) $(hfiles)

install: all
	cp $(BIN)$(target) $(PREFIX)/bin/$(target)

uninstall:
	rm -f $(PREFIX)/bin/$(target)
