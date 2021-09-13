# make clean && make && ./bin/pow

CC=clang
CFLAGS=-fPIE -Wall -std=c89
LDFLAGS=-pthread -lSDL2 #-fsanitize=address
OUT=bin/pow

CHDR=\
	src/cell.h\
	src/chunk.h\
	src/render.h

CSRC=\
	src/cell.c\
	src/chunk.c\
	src/render.c\
	src/main.c

COBJ=$(CSRC:.c=.o)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT): $(COBJ) $(CHDR)
	mkdir -p bin
	$(CC) $(COBJ) $(LDFLAGS) -o $(OUT)

clean:
	rm -rf $(COBJ) $(OUT)